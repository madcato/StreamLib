// FileOutputStream.cpp: implementation of the CFileOutputStream class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "IOutputStream.h"
#include "IInputStream.h"
#include "Exceptions.h"
#include "FileInputStream.h"

#include "FileOutputStream.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace Stream
{
CFileOutputStream::CFileOutputStream(const char* filename)
{
	m_file = fopen(filename,"wb");
	if(!m_file)
		throw new Exceptions::FileStreamException(-2,(std::string("Can't open file ") + filename + " for write").c_str());
}

CFileOutputStream::~CFileOutputStream()
{
	if(m_file != NULL)
	{
		fclose(m_file);
		m_file = NULL;
	}
}

//Closes this output stream and releases any system resources associated with this stream. 
void CFileOutputStream::close()
{
	if(m_file != NULL)
	{
		fclose(m_file);
		m_file = NULL;
	}
}
//Flushes this output stream and forces any buffered output bytes to be written out. 
void CFileOutputStream::flush()
{
	fflush(m_file);
}
//Writes b.length bytes from the specified byte array to this output stream. 
void CFileOutputStream::write(unsigned char* b,long length)
{
	fwrite(b,1,length,m_file);
}
//Writes len bytes from the specified byte array starting at offset off to this output stream. 
void CFileOutputStream::write(unsigned char* b, int off, int len)
{
	fseek(m_file,off,SEEK_CUR);
	fwrite(b,1,len,m_file);
}
//Writes the specified byte to this output stream. 
void CFileOutputStream::write(int b)
{
	fputc(b,m_file);
}
}