// CommandProcessor.cpp: implementation of the CCommandProcessor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "IOutputStream.h"	// Added by ClassView
#include "IInputStream.h"
#include "Exceptions.h"
#include "Socket.h"


#include "CommandProcessor.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace stream
{

/// namespace util
namespace util
{

CCommandProcessor::CCommandProcessor()
{	
	m_pipe = 0;	
	m_pipe = _popen( "cmd.exe", "wrt" );
   
}

CCommandProcessor::~CCommandProcessor()
{
	
}

io::IInputStream* CCommandProcessor::getInputStream()
{
	if(m_pipe)
	{
		m_in = new Internal_InputStream(this);
		return m_in;
	}

	return 0;
}

io::IOutputStream* CCommandProcessor::getOutputStream()
{
	if(m_pipe)
	{
		m_out = new Internal_OutputStream(this);
		return m_out;
	}

	return 0;
}


void CCommandProcessor::close()
{
	if(m_pipe)
	{
		_pclose(m_pipe);
		m_pipe = 0;
	}
}



CCommandProcessor::Internal_OutputStream::Internal_OutputStream(CCommandProcessor* parent)
{
	m_parent = parent;
}

void CCommandProcessor::Internal_OutputStream::close()
{
	m_parent->close();
}

void CCommandProcessor::Internal_OutputStream::flush()
{
}

void CCommandProcessor::Internal_OutputStream::write(unsigned char* b,long length)throw(exceptions::SocketStreamException*)
{
	fwrite(b,1,length,m_parent->m_pipe);
}

void CCommandProcessor::Internal_OutputStream::write(unsigned char* b, int off, int len)throw(exceptions::SocketStreamException*)
{
	fwrite(b+off,1,len,m_parent->m_pipe);
}

void CCommandProcessor::Internal_OutputStream::write(int b)throw(exceptions::SocketStreamException*)
{
	fwrite(&b,1,1,m_parent->m_pipe);
}



CCommandProcessor::Internal_InputStream::Internal_InputStream(CCommandProcessor* parent)
{
	m_parent = parent;
}


int CCommandProcessor::Internal_InputStream::available()
{
	return !feof(m_parent->m_pipe);
}

void CCommandProcessor::Internal_InputStream::close()
{
	m_parent->close();
}

void CCommandProcessor::Internal_InputStream::mark(int readlimit)
{
}

bool CCommandProcessor::Internal_InputStream::markSupported()
{
	return false;
}

int CCommandProcessor::Internal_InputStream::read()throw(exceptions::SocketStreamException*)
{
	char paso;
	if(feof(m_parent->m_pipe))
		throw new exceptions::StreamException(456,"command processor closed");

	int r = fread( &paso, 1, 1, m_parent->m_pipe);

	return paso;
}

int CCommandProcessor::Internal_InputStream::read(unsigned char* b,long length)throw(exceptions::SocketStreamException*)
{
	if(feof(m_parent->m_pipe))
		throw new exceptions::StreamException(456,"command processor closed");

	int r = fread( b, 1, length, m_parent->m_pipe);
	
	return r;
}

int CCommandProcessor::Internal_InputStream::read(unsigned char* b, int off, int len)throw(exceptions::SocketStreamException*)
{
	if(feof(m_parent->m_pipe))
		throw new exceptions::StreamException(456,"command processor closed");

	int r = fread( b+off, 1, len, m_parent->m_pipe);
	
	return r;;
}

void CCommandProcessor::Internal_InputStream::reset()
{
}

long CCommandProcessor::Internal_InputStream::skip(long n)throw(exceptions::SocketStreamException*)
{
	
	return -1;
}

} // namespace util

}