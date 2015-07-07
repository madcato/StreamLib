// BufferedReader.cpp: implementation of the BufferedReader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"


#include "IInputStream.h"
#include "BufferedReader.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace stream
{

/// namespace io
namespace io
{

BufferedReader::BufferedReader(IInputStream* input)
{
	m_input = input;
	m_bufferIni = 0;
	m_bufferFin = 0;
	m_buffer[0] = -1;
	
}

BufferedReader::~BufferedReader()
{

}


//Returns the number of bytes that can be read (or skipped over) from this input stream without blocking by the next caller of a method for this input stream. 
int BufferedReader::available()
{
	return m_input->available() + (m_bufferFin - m_bufferIni);
}
//Closes this input stream and releases any system resources associated with the stream. 
void BufferedReader::close()
{
	m_input->close();
}
//Marks the current position in this input stream. 
void BufferedReader::mark(int readlimit)
{
	m_input->mark(readlimit);
}
//Tests if this input stream supports the mark and reset methods. 
bool BufferedReader::markSupported()
{
	return m_input->markSupported();
}
//Reads the next byte of data from the input stream. 
int BufferedReader::read()
{
	if(((m_bufferIni == 0)&&(m_bufferFin == 0))||(m_bufferIni == m_bufferFin))
	{
		m_bufferIni = 0;
		m_bufferFin = 0;
		m_buffer[0] = -1;
		m_bufferFin = m_input->read(m_buffer,4096);
		if(m_bufferFin <= 0)
			return -1; // no se ha podido leer más
	}

	return m_buffer[m_bufferIni++];
}
//Reads some number of bytes from the input stream and stores them into the buffer array b. 
int BufferedReader::read(unsigned char* b,long length)
{
	return this->read(b,0,length);
}
//Reads up to len bytes of data from the input stream into an array of bytes. 
int BufferedReader::read(unsigned char* b, int off, int len)
{
	if(((m_bufferIni == 0)&&(m_bufferFin == 0))||(m_bufferIni == m_bufferFin))
	{
		m_bufferIni = 0;
		m_bufferFin = 0;
		m_buffer[0] = -1;
		m_bufferFin = m_input->read(m_buffer,4096);
		if(m_bufferFin <= 0)
			return 0; // no se ha podido leer más
	}

	long size_available = m_bufferFin - m_bufferIni;
	long readed = 0;
	if(size_available >= len)
	{
		memcpy(b+off,m_buffer+m_bufferIni,len);
		m_bufferIni += len;

		readed += len;
	}

	if(size_available < len)
	{
		memcpy(b+off,m_buffer+m_bufferIni,size_available);
		m_bufferIni += size_available;
		readed += size_available;

		readed += m_input->read(b+off+size_available,len - size_available);
	}

	return readed;
}
//Reads a line of text.
std::string BufferedReader::readLine()
{
	std::string buff;
	buff = "";
	char c = read();
	while((c != 0x0A)&&(c != -1))
	{
		if(c != 0x0D)
		{
			buff += c;
		}
		c = read();
	}

	return buff;
}
//Repositions this stream to the position at the time the mark method was last called on this input stream. 
void BufferedReader::reset()
{
	m_input->reset();
}
//Skips over and discards n bytes of data from this input stream. 
long BufferedReader::skip(long n)
{
	return m_input->skip(n);
}

} // namespace io

} //namespace stream
