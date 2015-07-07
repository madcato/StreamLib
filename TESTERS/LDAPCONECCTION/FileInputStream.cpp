// FileInputStream.cpp: implementation of the CFileInputStream class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "IInputStream.h"
#include "Exceptions.h"
#include "FileInputStream.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace Stream
{
CFileInputStream::CFileInputStream(const char* filename)throw(Exceptions::FileStreamException*)
{
	m_file = fopen(filename,"rb");
	if(!m_file)
		throw Exceptions::FileStreamException(-1,(std::string("Can't open file ") + filename + " for read").c_str());
}

CFileInputStream::~CFileInputStream()
{
	if(m_file != 0)
	{
		fclose(m_file);
		m_file = 0;
	}
}

//Returns the number of bytes that can be read (or skipped over) from this input stream without blocking by the next caller of a method for this input stream. 
int CFileInputStream::available()
{
	long currentPos;

	currentPos = ftell(m_file);
	
	fseek(m_file,0L,SEEK_END);
    long fin = ftell(m_file);
	fseek(m_file,currentPos,SEEK_SET);
	return fin - currentPos;
}
//Closes this input stream and releases any system resources associated with the stream. 
void CFileInputStream::close()
{
	if(m_file != 0)
	{
		fclose(m_file);
		m_file = 0;
	}
}
//Marks the current position in this input stream. 
void CFileInputStream::mark(int readlimit)
{
}
//Tests if this input stream supports the mark and reset methods. 
bool CFileInputStream::markSupported()
{
	return false;
}
//Reads the next byte of data from the input stream. 
int CFileInputStream::read()
{
	if(feof(m_file))
		return -1;

	return fgetc(m_file);
}
//Reads some number of bytes from the input stream and stores them into the buffer array b. 
int CFileInputStream::read(unsigned char* b,long length)
{	
	if(feof(m_file))
		return -1;
	
	return fread( b, 1, length, m_file);	
}
//Reads up to len bytes of data from the input stream into an array of bytes. 
int CFileInputStream::read(unsigned char* b, int off, int len)
{
	if(feof(m_file))
		return -1;
	
	skip(off);

	if(feof(m_file))
		return -1;
	
	return fread( b, 1, len, m_file);
}
//Repositions this stream to the position at the time the mark bytes was last called on this input stream. 
void CFileInputStream::reset()
{
	fseek(m_file,0,SEEK_SET);
}
//Skips over and discards n bytes of data from this input stream. 
long CFileInputStream::skip(long n)
{
	fseek(m_file,n,SEEK_CUR);
	return n;
}
}