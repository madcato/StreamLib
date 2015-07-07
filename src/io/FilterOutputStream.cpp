// FilterOutputStream.cpp: implementation of the FilterOutputStream class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "IOutputStream.h"
#include "Exceptions.h"
#include "CriticalSection.h"
#include "memory_stream.h"
#include "Blob.h"
#include "IDataProcessor.h"

#include "FilterOutputStream.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/// namespace stream
namespace stream
{
/// namespace io
namespace io
{

FilterOutputStream::FilterOutputStream(std::auto_ptr<IDataProcessor> processor,io::IOutputStream* output)
{
	m_processor = processor;

	m_output = output;
}

FilterOutputStream::~FilterOutputStream()
{

}

void FilterOutputStream::close()
{
	io::Blob<unsigned char> outBuffer = m_processor->Finish();

	m_output->write(outBuffer.get(),outBuffer.length());

	m_output->close();
}

void FilterOutputStream::flush()
{
	m_output->flush();
}

void FilterOutputStream::write(unsigned char* b,long length)
{
	write(b,0,length);
}

void FilterOutputStream::write(unsigned char* b, int off, int len)
{
	io::Blob<unsigned char> outBuffer = m_processor->Update(b+off,len);

	m_output->write(outBuffer.get(),outBuffer.length());
}

void FilterOutputStream::write(int b)
{
	write((unsigned char*)&b,0,1);
}

} // namespace io

} // namespace stream
