// B64InputStream.cpp: implementation of the B64InputStream class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Exceptions.h"
#include "CriticalSection.h"
#include "memory_stream.h"
#include "Blob.h"
#include "IInputStream.h"
#include "IDataProcessor.h"
#include "B64.h"

#include "B64InputStream.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace stream
{

/// namespace io
namespace io
{

B64InputStream::B64InputStream(EProcessType process, std::auto_ptr<IInputStream> input):m_processType(process),m_input(input)
{
	m_b64 = std::auto_ptr<B64>(new B64(process));

}

B64InputStream::~B64InputStream()
{

}

size_t B64InputStream::calculateSize(size_t size)
{
	switch(m_processType)
	{
	case OPEN_FOR_ENCODING:
		return ((size * 4) / 3) + ((size * 4) % 3);
	case OPEN_FOR_DECODING:
		return (size * 3) / 4;
	}

	return 0;
}

size_t B64InputStream::calculateInverseSize(size_t size)
{
	switch(m_processType)
	{
	case OPEN_FOR_ENCODING:
		return (size * 3) / 4;
	case OPEN_FOR_DECODING:		
		return ((size * 4) / 3) + ((size * 4) % 3);
	}

	return 0;
}

///Returns the number of bytes that can be read (or skipped over) from this input stream without blocking by the next caller of a method for this input stream. 
int B64InputStream::available()
{
	size_t size = m_input->available();
	return calculateSize(size);
}
///Closes this input stream and releases any system resources associated with the stream. 
void B64InputStream::close()
{
	m_input->close();
}
///Marks the current position in this input stream. 
void B64InputStream::mark(int readlimit)
{
	m_input->mark(readlimit);
}
///Tests if this input stream supports the mark and reset methods. 
bool B64InputStream::markSupported()
{
	return m_input->markSupported();
}
///Reads the next byte of data from the input stream. 
int B64InputStream::read()
{
	int b;
	read((unsigned char*)&b,0,1);
	return b;
}
///Reads some number of bytes from the input stream and stores them into the buffer array b. 
int B64InputStream::read(unsigned char* b,long length)
{
	return read(b,0,length);
}
///Reads up to len bytes of data from the input stream into an array of bytes. 
int B64InputStream::read(unsigned char* b, int off, int len)
{
	size_t size = calculateSize(len);

	util::auto_array_ptr<unsigned char> buffer(size*2);

	int readed = m_input->read(buffer.get(),size);
	Blob<unsigned char> blob;
	
	if(readed > 0)
	{
		blob = m_b64->Update(buffer.get(),readed);
	}
	
	if(!m_b64->finished())
	{
		Blob<unsigned char> blob2;
		blob2 = m_b64->Finish();

		blob.resize(blob.length() + 4);
		// Concatenamos el final.
		memcpy(blob.get() + blob.length(),blob2.get(),blob2.length());
		blob.setLength(blob.length() + blob2.length());
	}
	

	memcpy(b+off,blob.get(),blob.length());

	return blob.length();
}
///Repositions this stream to the position at the time the mark method was last called on this input stream. 
void B64InputStream::reset()
{
	m_input->reset();
}
///Skips over and discards n bytes of data from this input stream. 
long B64InputStream::skip(long n)
{
	return m_input->skip(n);
}

} // namespace io

} // namespace stream