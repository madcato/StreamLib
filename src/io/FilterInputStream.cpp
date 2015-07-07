// FilterInputStream.cpp: implementation of the FilterInputStream class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "IInputStream.h"
#include "Exceptions.h"
#include "CriticalSection.h"
#include "memory_stream.h"
#include "Blob.h"
#include "IDataProcessor.h"

#include "FilterInputStream.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


///////  Nunc scio tenebris lux

/// namespace stream
namespace stream
{
/// namespace io
namespace io
{

FilterInputStream::FilterInputStream(std::auto_ptr<IDataProcessor> processor,io::IInputStream* input)
{
	m_processor = processor;


	m_input = input;
}

FilterInputStream::~FilterInputStream()
{

}

int FilterInputStream::available()
{
	return m_input->available() + m_cache.length();
}

void FilterInputStream::close()
{
	m_input->close();
}

void FilterInputStream::mark(int readlimit)
{
}

bool FilterInputStream::markSupported()
{
	return false;
}

int FilterInputStream::read()
{
	int c = 0;
	read((unsigned char*)&c,0,1);

	return c;
}

int FilterInputStream::read(unsigned char* b,long length)
{
	return read(b,0,length);
}

int FilterInputStream::read(unsigned char* b, int off, int len)
{
	if(len <= m_cache.length())
	{
		memcpy(b+off,m_cache.get(), len);

		m_cache = m_cache.cut(len,m_cache.length() - len);

		return len;
	}


	do
	{
		io::Blob<unsigned char> temporal;
		temporal.resize(len);
		

		int readed = m_input->read(temporal.get()+temporal.length(),len - temporal.length());
		temporal.setLength(readed);

		if((readed == 0)||(readed == -1))
		{
			temporal = m_processor->Finish();
			
			m_cache.attach(temporal.get(),temporal.length());

			memcpy(b+off,m_cache.get(), m_cache.length());
		
			int toReturn = m_cache.length();

			m_cache = m_cache.cut(0,0);

			return toReturn;
		}		

		temporal = m_processor->Update(temporal.get(),temporal.length());

		m_cache.attach(temporal.get(),temporal.length());

		if(len <= m_cache.length())
		{
			memcpy(b+off,m_cache.get(), len);

			m_cache = m_cache.cut(len,m_cache.length() - len);

			return len;
		}

	}while(true);

	
	return -1;
}

void FilterInputStream::reset()
{
}

long FilterInputStream::skip(long n)
{
	return 0;
}

} // namespace io

} // namespace stream
