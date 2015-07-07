// GZIP.cpp: implementation of the GZIP class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Exceptions.h"
#include "CriticalSection.h"
#include "memory_stream.h"
#include "Blob.h"
#include "IDataProcessor.h"

#include "GZIP.h"

#include "gz_exceptions.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace stream
{
namespace zip
{


	class GZIPCompressor : public io::IDataProcessor
	{
	public:
		GZIPCompressor(size_t bufferLength = 4096);
		virtual ~GZIPCompressor();


		virtual io::Blob<unsigned char> Update(unsigned char* buffer,unsigned long size);
		virtual io::Blob<unsigned char> Finish();
		virtual size_t available();

	private:
		z_stream m_z_stream;

		long m_length;
	};

	class GZIPUncompressor : public io::IDataProcessor
	{
	public:
		GZIPUncompressor(size_t bufferLength = 4096);
		virtual ~GZIPUncompressor();

		virtual io::Blob<unsigned char> Update(unsigned char* buffer,unsigned long size);
		virtual io::Blob<unsigned char> Finish();
		virtual size_t available();

	private:
		z_stream m_z_stream;

		long m_length;
	};




GZIP::GZIP(EProcessTypeZip type,size_t bufferLength)
{

	switch(type)
	{
	case OPEN_FOR_COMPRESS:
		m_processor = std::auto_ptr<io::IDataProcessor>(new GZIPCompressor(bufferLength));
		break;
	case OPEN_FOR_UNCOMPRESS:
		m_processor = std::auto_ptr<io::IDataProcessor>(new GZIPUncompressor(bufferLength));
		break;
	}

}

GZIP::~GZIP()
{

}

io::Blob<unsigned char> GZIP::Update(unsigned char* buffer,unsigned long size)
{
	return m_processor->Update(buffer,size);
}

io::Blob<unsigned char> GZIP::Finish()
{
	return m_processor->Finish();
}

size_t GZIP::available()
{
	return m_processor->available();
}



GZIPCompressor::GZIPCompressor(size_t bufferLength)
{
	m_length = bufferLength;

	memset(&m_z_stream,0,sizeof(m_z_stream));
	if(deflateInit(&m_z_stream,Z_DEFAULT_COMPRESSION) != Z_OK)
	{
		throw new exceptions::GZException(m_z_stream.msg);
	}
}

GZIPCompressor::~GZIPCompressor()
{

}

io::Blob<unsigned char> GZIPCompressor::Update(unsigned char* buffer,unsigned long size)
{
	m_z_stream.next_in = buffer;
	m_z_stream.avail_in = size;
	m_z_stream.total_in = 0;
	

	io::Blob<unsigned char> outBuffer;
	outBuffer.resize(size);
	m_z_stream.next_out = outBuffer.get();
	m_z_stream.avail_out = outBuffer.capacity();
	m_z_stream.total_out = 0;

	if(deflate(&m_z_stream,Z_NO_FLUSH) != Z_OK )
	{
		throw new exceptions::GZException(m_z_stream.msg);
	}

	outBuffer.setLength(m_z_stream.total_out);

	return outBuffer;
}

io::Blob<unsigned char> GZIPCompressor::Finish()
{
	io::Blob<unsigned char> outBuffer;
	outBuffer.resize(m_length);
	m_z_stream.next_out = outBuffer.get();
	m_z_stream.avail_out = outBuffer.capacity();
	m_z_stream.total_out = 0;

	if(deflate(&m_z_stream, Z_FINISH) != Z_STREAM_END)
	{
		throw new exceptions::GZException(m_z_stream.msg);
	}

	outBuffer.setLength(m_z_stream.total_out);

	deflateEnd(&m_z_stream);

	return outBuffer;
}

size_t GZIPCompressor::available()
{
	return -1;
}




GZIPUncompressor::GZIPUncompressor(size_t bufferLength)
{
	m_length = bufferLength;

	memset(&m_z_stream,0,sizeof(m_z_stream));
	if(inflateInit(&m_z_stream) != Z_OK)
	{
		throw new exceptions::GZException(m_z_stream.msg);
	}
}

GZIPUncompressor::~GZIPUncompressor()
{

}

io::Blob<unsigned char> GZIPUncompressor::Update(unsigned char* buffer,unsigned long size)
{
	m_z_stream.next_in = buffer;
	m_z_stream.avail_in = size;
	m_z_stream.total_in = 0;
	

	io::Blob<unsigned char> outBuffer;
	outBuffer.resize(size * 10);
	m_z_stream.next_out = outBuffer.get();
	m_z_stream.avail_out = outBuffer.capacity();
	m_z_stream.total_out = 0;

	int result = inflate(&m_z_stream,0);;
	if((result != Z_OK)&&(result !=	Z_STREAM_END))
	{
		throw new exceptions::GZException(m_z_stream.msg);
	}

	outBuffer.setLength(m_z_stream.total_out);

	return outBuffer;
}

io::Blob<unsigned char> GZIPUncompressor::Finish()
{
	io::Blob<unsigned char> outBuffer;
	outBuffer.resize(m_length);
	m_z_stream.next_out = outBuffer.get();
	m_z_stream.avail_out = outBuffer.capacity();
	m_z_stream.total_out = 0;

	if(inflate(&m_z_stream, Z_FINISH) != Z_STREAM_END)
	{
		throw new exceptions::GZException(m_z_stream.msg);
	}

	outBuffer.setLength(m_z_stream.total_out);

	deflateEnd(&m_z_stream);

	return outBuffer;
}

size_t GZIPUncompressor::available()
{
	return -1;
}

} // namespace zip

} // namespace stream