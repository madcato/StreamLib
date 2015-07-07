// BLOBOutputStream.cpp: implementation of the BLOBOutputStream class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Exceptions.h"
#include "memory_stream.h"
#include "BLOB.h"
#include "IOutputStream.h"

#include "BLOBOutputStream.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace stream
{

/// namespace io
namespace io
{

BLOBOutputStream::BLOBOutputStream(std::auto_ptr<Blob<char> >& blob):m_blob(blob)
{

}

BLOBOutputStream::BLOBOutputStream(util::ref_count_ptr<Blob<char> >& blob):m_blob(blob)
{

}

BLOBOutputStream::~BLOBOutputStream()
{

}

//Closes this output stream and releases any system resources associated with this stream. 
void BLOBOutputStream::close()
{
}
//Flushes this output stream and forces any buffered output bytes to be written out. 
void BLOBOutputStream::flush()
{
}
//Writes b.length bytes from the specified byte array to this output stream. 
void BLOBOutputStream::write(unsigned char* b,long length)
{
	write(b,0,length);
}
//Writes len bytes from the specified byte array starting at offset off to this output stream. 
void BLOBOutputStream::write(unsigned char* b, int off, int len)
{
	m_blob->attach((char*)(b+off),len);
	/*// First. Check if the blob has the capactiy to hold the new data.
	long availableLength = m_blob->capacity() - m_blob->length();

	if(availableLength < len)
	{
		long newCapacity = m_blob->capacity() * 2;
		long newAvailableLength = newCapacity - m_blob->length();
		if(newAvailableLength < len)
		{
			newCapacity += len;
		}

		m_blob->resize(newCapacity);
	}

	memcpy(m_blob->get()+m_blob->length(),b+off,len);
	m_blob->setLength(m_blob->length()+len);*/
}
//Writes the specified byte to this output stream. 
void BLOBOutputStream::write(int b)
{
	write((unsigned char*)&b,1);
}

} // namespace io

} // namespace stream
