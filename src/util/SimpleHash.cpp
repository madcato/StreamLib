// SimpleHash.cpp: implementation of the SimpleHash class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Exceptions.h"
#include "memory_stream.h"
#include "Blob.h"
#include "IDataProcessor.h"

#include "SimpleHash.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


namespace stream
{
namespace util
{


SimpleHash::SimpleHash()
{
	m_crc = 0;
}

SimpleHash::~SimpleHash()
{

}

io::Blob<unsigned char> SimpleHash::Update(unsigned char* buffer,unsigned long size)
{
	m_crc = crc32(m_crc,buffer,size);

	io::Blob<unsigned char> blob;

	// Empty blob.
	return blob;
}

io::Blob<unsigned char> SimpleHash::Finish()
{
	io::Blob<unsigned char> blob;

	blob.resize(sizeof(m_crc));
	blob.setData((uchar*)&m_crc,sizeof(m_crc));
	return blob;
}

size_t SimpleHash::available()
{
	return sizeof(m_crc);
}


} // namespace util

} // namespace stream