// IOutputStream.cpp: implementation of the IOutputStream class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "IOutputStream.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace Stream
{
IOutputStream::IOutputStream()
{

}

IOutputStream::~IOutputStream()
{

}

//Closes this output stream and releases any system resources associated with this stream. 
void IOutputStream::close()
{
}
//Flushes this output stream and forces any buffered output bytes to be written out. 
void IOutputStream::flush()
{
}
//Writes b.length bytes from the specified byte array to this output stream. 
void IOutputStream::write(unsigned char* b,long length)
{
}
//Writes len bytes from the specified byte array starting at offset off to this output stream. 
void IOutputStream::write(unsigned char* b, int off, int len)
{
}
//Writes the specified byte to this output stream. 
void IOutputStream::write(int b)
{
}

} // namespace Stream