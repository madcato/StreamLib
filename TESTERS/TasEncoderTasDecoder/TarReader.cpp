// TarReader.cpp: implementation of the TarReader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "IInputStream.h"

#include "TarHeader.h"
#include "TarHeaderFactory.h"
#include "TarReader.h"

#include "Exceptions.h"

#include "memory_stream.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace Stream
{

TarReader::TarReader(std::auto_ptr<IInputStream> input)
{
	m_input = input;
}

TarReader::~TarReader()
{

}

void TarReader::close()
{
	m_input->close();
}

bool TarReader::getNextItem(std::string& path,bool& directory,std::auto_ptr<IInputStream>& data)
{
	auto_array_ptr<unsigned char> buffer(new unsigned char[blockSize]);
	int readed = m_input->read(buffer.get(),blockSize);

	if(readed == 0)
	{
		return false;
	}

	TarHeader tarHeader;
	TarHeaderFactory::CreateTarHeaderFromBuffer(buffer.get(),tarHeader);

	path = tarHeader.name;

#ifdef WIN32
	TarHeaderFactory::replaceSlash(path);
#endif // WIN32

	if(path == "")
	{
		// The End
		return false;
	}

	if(tarHeader.typeflag == 'L') // "././@LongLink"
	{
		// Leemos los datos de esta entrada que serán el path de la siguiente.
		unsigned long size = 0;
		sscanf(tarHeader.size,"%011o",&size);

		std::auto_ptr<IInputStream>& pathNameStream = std::auto_ptr<IInputStream>(new TarReaderStream(size,m_input.get()));

		auto_array_ptr<unsigned char> pathNameData(new unsigned char[size+1]);

		int readed = pathNameStream->read(pathNameData.get(),size);
		
		pathNameStream->close();

		pathNameData[size] = '\0';

		path = (char*)pathNameData.get();

#ifdef WIN32
		TarHeaderFactory::replaceSlash(path);
#endif // WIN32


		readed = m_input->read(buffer.get(),blockSize);

		if(readed == 0)
		{
			return false;
		}


		TarHeaderFactory::CreateTarHeaderFromBuffer(buffer.get(),tarHeader);

	}

	if(tarHeader.typeflag == '5')
	{
		// Directory

		directory = true;
	}
	else
	{
		// File
		directory = false;

		unsigned long size = 0;
		sscanf(tarHeader.size,"%011o",&size);

		data = std::auto_ptr<IInputStream>(new TarReaderStream(size,m_input.get()));
	}


	return true;
}


TarReader::TarReaderStream::TarReaderStream(unsigned long size,IInputStream* input)
{
	m_size = size;
	m_input = input;
	m_readed = 0;
}

TarReader::TarReaderStream::~TarReaderStream()
{

}


//Returns the number of bytes that can be read (or skipped over) from this input stream without blocking by the next caller of a method for this input stream. 
int TarReader::TarReaderStream::available()
{
	return m_size - m_readed;
}
//Closes this input stream and releases any system resources associated with the stream. 
void TarReader::TarReaderStream::close()
{
	unsigned long numberOfZeros = blockSize - (m_size % blockSize);
	if(numberOfZeros < blockSize)
	{
		skip(numberOfZeros);
	}
}
//Marks the current position in this input stream. 
void TarReader::TarReaderStream::mark(int readlimit)
{
}
//Tests if this input stream supports the mark and reset methods. 
bool TarReader::TarReaderStream::markSupported()
{
	return false;
}
//Reads the next byte of data from the input stream. 
int TarReader::TarReaderStream::read()
{
	int c;
	read((unsigned char*)&c,1);
	return c;
}
//Reads some number of bytes from the input stream and stores them into the buffer array b. 
int TarReader::TarReaderStream::read(unsigned char* b,long length)
{
	
	return read(b,0,length);
}
//Reads up to len bytes of data from the input stream into an array of bytes. 
int TarReader::TarReaderStream::read(unsigned char* b, int off, int len)
{
	int toRead = (m_size-m_readed) < len ? (m_size-m_readed) : len;
	int readed = m_input->read(b,off,toRead);
	m_readed += readed;
	return readed;
}
//Repositions this stream to the position at the time the mark bytes was last called on this input stream. 
void TarReader::TarReaderStream::reset()
{
}
//Skips over and discards n bytes of data from this input stream. 
long TarReader::TarReaderStream::skip(long n)
{
	long skipped = m_input->skip(n);
	m_readed += skipped;
	return skipped;
}

} // namespace Stream