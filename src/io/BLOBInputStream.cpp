// BLOBInputStream.cpp: implementation of the BLOBInputStream class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Exceptions.h"
#include "memory_stream.h"
#include "BLOB.h"
#include "IInputStream.h"

#include "BLOBInputStream.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace stream
{

namespace io
{

BLOBInputStream::BLOBInputStream(std::auto_ptr<Blob<char> >& blob):m_blob(blob)
{
	m_actualPos = 0;
}

BLOBInputStream::BLOBInputStream(util::ref_count_ptr<Blob<char> >& blob):m_blob(blob)
{
	m_actualPos = 0;
}

BLOBInputStream::~BLOBInputStream()
{

}

//Returns the number of bytes that can be read (or skipped over) from this input stream without blocking by the next caller of a method for this input stream. 
int BLOBInputStream::available()
{
	return m_blob->length() - m_actualPos;
}
//Closes this input stream and releases any system resources associated with the stream. 
void BLOBInputStream::close()
{
	m_actualPos = m_blob->length();
}
//Marks the current position in this input stream. 
void BLOBInputStream::mark(int readlimit)
{
}
//Tests if this input stream supports the mark and reset methods. 
bool BLOBInputStream::markSupported()
{
	return false;
}
//Reads the next byte of data from the input stream. 
int BLOBInputStream::read()
{
	if(m_blob->length() <= m_actualPos)
		throw exceptions::BLOBException(-1,"Can't read, overflow");
	
	return m_blob->get()[m_actualPos++];
}
//Reads some number of bytes from the input stream and stores them into the buffer array b. 
int BLOBInputStream::read(unsigned char* b,long length)
{
	return read(b,0,length);
}
//Reads up to len bytes of data from the input stream into an array of bytes. 
int BLOBInputStream::read(unsigned char* b, int off, int len)
{
	long availableLen = m_blob->length() - m_actualPos;
	long toRead = availableLen > len ? len : availableLen;
	memcpy(b+off,m_blob->get(),toRead);
	m_actualPos += toRead;
	return toRead;
}
//Repositions this stream to the position at the time the mark bytes was last called on this input stream. 
void BLOBInputStream::reset()
{
}
//Skips over and discards n bytes of data from this input stream. 
long BLOBInputStream::skip(long n)
{
	return 0;
}

} // namespace io
} // namespace Stream