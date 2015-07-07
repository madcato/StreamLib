// HexBin.cpp: implementation of the HexBin class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Exceptions.h"
#include "CriticalSection.h"
#include "memory_stream.h"
#include "Blob.h"
#include "IDataProcessor.h"
#include "B64.h"

#include "HexBin.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


namespace stream
{

/// namespace io
namespace io
{

HexBin::HexBin(EProcessType type, bool makeUpper)
{
	m_type = type;
	lastChar = -1;

	if(makeUpper)
	{
		m_format = "%02X";
	}
	else
	{
		m_format = "%02x";
	}
}

HexBin::~HexBin()
{

}

io::Blob<unsigned char> HexBin::Update(unsigned char* buffer,unsigned long size)
{
	io::Blob<unsigned char> blob;
	if(m_type == OPEN_FOR_ENCODING)
	{
		std::string ret = "";
		char cad[5];
		for(int i = 0 ; i < size ; i++)
		{
			sprintf(cad,m_format,buffer[i]);
			ret += cad;
		}

		blob.setData(ret);
	}
	else
	{
		int incre = 0;
		if(lastChar != -1)
		{
			char paso[10];
			paso[0] = lastChar;
			paso[1] = buffer[0];
			paso[2] = 0;
			
			int c;
			sscanf((char*)paso,"%02x",&c);

			blob.resize(1);
			blob[0] = c;
			blob.setLength(1);

			buffer++;
			size--;
			lastChar = -1;
			incre = 1;
		}


		if(size % 2)
		{
			lastChar = buffer[size - 1];
			size--;
		}

		blob.resize(size / 2);
		for(int i = 0 ; i < size ; i+=2)
		{
			int c;
			sscanf((char*)buffer+i,"%02x",&c);
			blob[incre + i/2] = c;
		}
	}
	

	return blob;

}

io::Blob<unsigned char> HexBin::Finish()
{
	if(lastChar != -1)
	{
		throw new exceptions::StreamException(-1,"Invalid input for decoding HexBin");
	}
	io::Blob<unsigned char> blob;
	return blob;
}

size_t HexBin::available()
{
	return 0;
}

} // io

} // namespace stream