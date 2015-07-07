// PrintWriter.cpp: implementation of the PrintWriter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "ioutputstream.h"
#include "PrintWriter.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace stream
{

/// namespace io
namespace io
{

PrintWriter::PrintWriter(IOutputStream* output, std::string endline)
{
	m_output = output;
	
	m_enlinelen = endline.length();
	m_endline = new unsigned char[m_enlinelen];
	memcpy(m_endline,endline.c_str(),m_enlinelen);
}

PrintWriter::~PrintWriter()
{
	delete[] m_endline;
}

//Closes this output stream and releases any system resources associated with this stream. 
void PrintWriter::close()
{
	m_output->close();
}
//Flushes this output stream and forces any buffered output bytes to be written out. 
void PrintWriter::flush()
{
	m_output->flush();
}
//Writes b.length bytes from the specified byte array to this output stream. 
void PrintWriter::write(unsigned char* b,long length)
{
	m_output->write(b,length);
}
//Writes len bytes from the specified byte array starting at offset off to this output stream. 
void PrintWriter::write(unsigned char* b, int off, int len)
{
	m_output->write(b,off,len);
}
//Writes the specified byte to this output stream. 
void PrintWriter::write(int b)
{
	m_output->write(b);
}
//Writes a line.
void PrintWriter::println(std::string cad)
{

	try
	{
		m_output->write((unsigned char*)cad.c_str(),cad.length());

		m_output->write(m_endline,m_enlinelen);

	}
	catch(...)
	{

		throw;
	}


	
}

} // namespace io

} // namespace stream
