// GZIPOutputStream.cpp: implementation of the GZIPOutputStream class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "IOutputStream.h"
#include "Exceptions.h"
#include "CriticalSection.h"
#include "memory_stream.h"
#include "Blob.h"
#include "IDataProcessor.h"
#include "GZIP.h"
#include "FilterOutputStream.h"

#include "GZIPOutputStream.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/// namespace stream
namespace stream
{
/// namespace zip
namespace zip
{

GZIPOutputStream::GZIPOutputStream(EProcessTypeZip processType,io::IOutputStream* output)
{

	m_filter = std::auto_ptr<io::FilterOutputStream>(new io::FilterOutputStream(std::auto_ptr<io::IDataProcessor>(new GZIP(processType)),output));
	
}

GZIPOutputStream::~GZIPOutputStream()
{

}

void GZIPOutputStream::close()
{
	m_filter->close();
}

void GZIPOutputStream::flush()
{
	m_filter->flush();
}

void GZIPOutputStream::write(unsigned char* b,long length)
{
	m_filter->write(b,0,length);
}

void GZIPOutputStream::write(unsigned char* b, int off, int len)
{
	m_filter->write(b,off,len);
	
}

void GZIPOutputStream::write(int b)
{
	m_filter->write(b);	
}

} // namespace zip

} // namespace stream
