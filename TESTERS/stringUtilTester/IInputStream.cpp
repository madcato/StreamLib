// IInputStream.cpp: implementation of the IInputStream class.
//
//////////////////////////////////////////////////////////////////////

#include "IInputStream.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace Stream
{
IInputStream::IInputStream()
{

}

IInputStream::~IInputStream()
{

}


//Returns the number of bytes that can be read (or skipped over) from this input stream without blocking by the next caller of a method for this input stream. 
int IInputStream::available()
{
	return 0;
}
//Closes this input stream and releases any system resources associated with the stream. 
void IInputStream::close()
{
}
//Marks the current position in this input stream. 
void IInputStream::mark(int readlimit)
{
}
//Tests if this input stream supports the mark and reset methods. 
bool IInputStream::markSupported()
{
	return false;
}
//Reads the next byte of data from the input stream. 
int IInputStream::read()
{
	return 0;
}
//Reads some number of bytes from the input stream and stores them into the buffer array b. 
int IInputStream::read(unsigned char* b,long length)
{
	return 0;
}
//Reads up to len bytes of data from the input stream into an array of bytes. 
int IInputStream::read(unsigned char* b, int off, int len)
{
	return 0;
}
//Repositions this stream to the position at the time the mark bytes was last called on this input stream. 
void IInputStream::reset()
{
}
//Skips over and discards n bytes of data from this input stream. 
long IInputStream::skip(long n)
{
	return 0;
}
}