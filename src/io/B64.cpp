// B64.cpp: implementation of the B64 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Exceptions.h"
#include "CriticalSection.h"
#include "memory_stream.h"
#include "Blob.h"
#include "IDataProcessor.h"

#include "B64.h"

#include "Tokenizer.h"
#include "Date.h"
#include "StringUtil.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace stream
{

/// namespace io
namespace io
{

static char	Base64Digits[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char B64::B64Decoder::m_DecodeTable[256];
bool B64::B64Decoder::m_initDecodingTable = false;

B64::B64(EProcessType type,size_t bufferLength)
{
	if(bufferLength <= 0)
	{
		throw new exceptions::StreamException(-1,std::string("Invalid buffer length(") + util::StringUtil::toString((long)bufferLength) + "). Must be a positive value.");
	}
	switch(type)
	{
	case OPEN_FOR_ENCODING:
		m_processor = std::auto_ptr<IDataProcessor>(new B64Encoder(bufferLength));
		break;
	case OPEN_FOR_DECODING:
		m_processor = std::auto_ptr<IDataProcessor>(new B64Decoder(bufferLength));
		break;
	};

	m_finished = false;

}

B64::~B64()
{

}




Blob<unsigned char> B64::Update(unsigned char* buffer,unsigned long size)
{
	return m_processor->Update(buffer,size);
}

Blob<unsigned char> B64::Finish()
{
	m_finished = true;
	return m_processor->Finish();
}
size_t B64::available()
{
	return m_processor->available();
}


/////////// class B64Encoder ////////////////
// 3b -> 4b
B64::B64Encoder::B64Encoder(size_t bufferLength):m_bufferLength(bufferLength)
{

	m_state = 0;
	InitBuffer();
	memset(m_tempBucket,0,4);

}

void B64::B64Encoder::InitBuffer()
{
	m_buffer = Blob<unsigned char>();
	m_buffer.resize(m_bufferLength);
	m_buffer.setLength(0);
	
}


Blob<unsigned char> B64::B64Encoder::Update(unsigned char* buffer,unsigned long size)
{
	InitBuffer();
	unsigned long i = 0;

	while(i < size)
	{
		switch(m_state++)
		{
		case 0:
			m_tempBucket[0] = buffer[i] >> 2;
			
			m_tempBucket[1] = (buffer[i] & 0x03) << 4;
			break;
		case 1:
			m_tempBucket[1] |= buffer[i] >> 4;

			m_tempBucket[2] = (buffer[i] & 0x0F) << 2;
			break;
		case 2:
			m_tempBucket[2] |= buffer[i] >> 6;
		
			m_tempBucket[3] = buffer[i] & 0x03F;
			DumpData();
			memset(m_tempBucket,0,4);
			m_state = 0;
			break;
			
		};
		i++;
	}



	return m_buffer;
}

void B64::B64Encoder::DumpData()
{
	if(m_buffer.capacity() < (m_buffer.length() + 4))
	{
		m_buffer.resize(m_buffer.capacity() * 2);
	}

	unsigned long i = m_buffer.length();

	for(int t = 0 ; t < m_state + 1 ; t++)
	{
		m_buffer[i + t] = Base64Digits[m_tempBucket[t]];
	}
	m_buffer.setLength(i + m_state + 1);


}

Blob<unsigned char> B64::B64Encoder::Finish()
{
	InitBuffer();
	m_buffer[0] = '\0';

	int rest = m_state;
	if(m_state != 0)
		DumpData();
		
	switch(rest)
	{
	case 1:
		m_buffer[2] = '=';
		m_buffer.setLength(3);
	case 2:
		m_buffer[3] = '=';
		m_buffer.setLength(4);
	};
	

	return m_buffer;
}

size_t B64::B64Encoder::available()
{
	if(m_state == 0)
		return 0;

	return m_state;

}

/////////// class B64Decoder ////////////////
// 4b -> 3b
B64::B64Decoder::B64Decoder(size_t bufferLength):m_bufferLength(bufferLength)
{
	InitBuffer();
	m_state = 0;
	memset(m_tempBucket,0,3);

	if(!m_initDecodingTable)
		InitDecodingTable();
}

void B64::B64Decoder::InitBuffer()
{
	m_buffer = Blob<unsigned char>();
	m_buffer.resize(m_bufferLength);
	m_buffer.setLength(0);
	
}

Blob<unsigned char> B64::B64Decoder::Update(unsigned char* buffer,unsigned long size)
{
	int i = 0;
	InitBuffer();

	do
	{
		while((_IsBadMimeChar(buffer[i])&&(i < size)))
		{
			i++;
		}

		if(i < size)
		{
			
			switch(m_state++)
			{
			case 0:
				m_tempBucket[0] = m_DecodeTable[buffer[i]] << 2;
				break;
			case 1:
				m_tempBucket[0] |= m_DecodeTable[buffer[i]] >> 4;
				m_tempBucket[1] = m_DecodeTable[buffer[i]] << 4;
				break;
			case 2:
				m_tempBucket[1] |= m_DecodeTable[buffer[i]] >> 2;
				m_tempBucket[2] = m_DecodeTable[buffer[i]] << 6;
				break;
			case 3:
				m_tempBucket[2] |= m_DecodeTable[buffer[i]];
				DumpData();
				memset(m_tempBucket,0,3);
				break;

			};
			

			m_state %= 4;
		}
	}while(i++ < size);

	return m_buffer;
}

Blob<unsigned char> B64::B64Decoder::Finish()
{
	InitBuffer();
	if(m_state != 0)
		DumpData();	
	return m_buffer;
}

bool B64::B64Decoder::_IsBadMimeChar(char nData)
{
	
	if((nData >= 65)&&(nData <= 90))
		return false;

	if((nData >= 97)&&(nData <= 122))
		return false;

	if((nData >= 48)&&(nData <= 57))
		return false;

	if((nData == '+')||(nData == '/'))
		return false;


	return true;

}

void B64::B64Decoder::DumpData()
{

	if(m_buffer.capacity() < (m_buffer.length() + 4))
	{
		m_buffer.resize(m_buffer.capacity() * 2);
	}

	unsigned long i = m_buffer.length();

	for(int t = 0 ; t < m_state; t++)
	{
		m_buffer[i + t] = m_tempBucket[t];
	}
	m_buffer.setLength(i + m_state - 1);	
}

void B64::B64Decoder::InitDecodingTable()
{

	int	i;

	for(i = 0; i < 256; i++)
		m_DecodeTable[i] = -2;

	for(i = 0; i < 64; i++)
	{
		m_DecodeTable[Base64Digits[i]]			= i;
		m_DecodeTable[Base64Digits[i]|0x80]	= i;
	}

	m_DecodeTable['=']				= -1;
	m_DecodeTable['='|0x80]		= -1;

	m_initDecodingTable = true;
}

size_t B64::B64Decoder::available()
{
	if(m_state == 0)
		return 0;

	return m_state;

}

bool B64::finished()
{
	return m_finished;
}

} // io

} // namespace stream