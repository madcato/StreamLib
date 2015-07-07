// GZIPInputStream.cpp: implementation of the GZIPInputStream class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "IInputStream.h"
#include "Exceptions.h"
#include "CriticalSection.h"
#include "memory_stream.h"
#include "Blob.h"
#include "IDataProcessor.h"
#include "GZIP.h"
#include "FilterInputStream.h"

#include "GZIPInputStream.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


///////  Nunc scio tenebris lux

/// namespace stream
namespace stream
{
/// namespace zip
namespace zip
{

GZIPInputStream::GZIPInputStream(EProcessTypeZip processType,io::IInputStream* input)
{
	m_filter = std::auto_ptr<io::FilterInputStream>(new io::FilterInputStream(std::auto_ptr<io::IDataProcessor>(new GZIP(processType)),input));
}

GZIPInputStream::~GZIPInputStream()
{

}

int GZIPInputStream::available()
{
	return m_filter->available();
}

void GZIPInputStream::close()
{
	m_filter->close();
}

void GZIPInputStream::mark(int readlimit)
{
	m_filter->mark(readlimit);
}

bool GZIPInputStream::markSupported()
{
	return m_filter->markSupported();
}

int GZIPInputStream::read()
{
	return m_filter->read();
}

int GZIPInputStream::read(unsigned char* b,long length)
{
	return m_filter->read(b,length);
}

int GZIPInputStream::read(unsigned char* b, int off, int len)
{
	return m_filter->read(b,off,len);
}

void GZIPInputStream::reset()
{
	m_filter->reset();
}

long GZIPInputStream::skip(long n)
{
	return m_filter->skip(n);
}

} // namespace zip

} // namespace stream
