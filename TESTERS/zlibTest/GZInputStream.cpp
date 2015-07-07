// GZInputStream.cpp: implementation of the GZInputStream class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <string>
#include "IInputStream.h"
#include "gz_exceptions.h"
#include "GZInputStream.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace Stream
{


GZInputStream::GZInputStream(const std::string& fileName)
{
	m_file = gzopen(fileName.c_str(),"rb");

	if(!m_file)
	{
		throw Exceptions::GZException(m_file);
	}
}

GZInputStream::~GZInputStream()
{

}



//Returns the number of bytes that can be read (or skipped over) from this input stream without blocking by the next caller of a method for this input stream. 
int GZInputStream::available()
{
	gzseek(m_file, 0, SEEK_END);
	long max_length = gztell(m_file);
	gzseek(m_file, 0, SEEK_SET);
	return max_length;
}
//Closes this input stream and releases any system resources associated with the stream. 
void GZInputStream::close()
{
	gzclose(m_file);
}
//Marks the current position in this input stream. 
void GZInputStream::mark(int readlimit)
{
}
//Tests if this input stream supports the mark and reset methods. 
bool GZInputStream::markSupported()
{
	return false;
}
//Reads the next byte of data from the input stream. 
int GZInputStream::read()
{
	int buff;
	read((unsigned char*)&buff,1);

	return buff;
}
//Reads some number of bytes from the input stream and stores them into the buffer array b. 
int GZInputStream::read(unsigned char* b,long length)
{
	return read(b,0,length);
}
//Reads up to len bytes of data from the input stream into an array of bytes. 
int GZInputStream::read(unsigned char* b, int off, int len)
{
	return gzread(m_file,b+off,len);
}
//Repositions this stream to the position at the time the mark bytes was last called on this input stream. 
void GZInputStream::reset()
{
}
//Skips over and discards n bytes of data from this input stream. 
long GZInputStream::skip(long n)
{
	return 0;
}
}