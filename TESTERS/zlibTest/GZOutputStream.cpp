// GZOutputStream.cpp: implementation of the GZOutputStream class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <string>
#include "IOutputStream.h"
#include "gz_exceptions.h"
#include "GZOutputStream.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace Stream
{


GZOutputStream::GZOutputStream(const std::string& fileName)
{
	m_file = gzopen(fileName.c_str(),"wb9");
}

GZOutputStream::~GZOutputStream()
{

}


//Closes this output stream and releases any system resources associated with this stream. 
void GZOutputStream::close()
{
	gzclose(m_file);
}
//Flushes this output stream and forces any buffered output bytes to be written out. 
void GZOutputStream::flush()
{
}
//Writes b.length bytes from the specified byte array to this output stream. 
void GZOutputStream::write(unsigned char* b,long length)
{
	write(b,0,length);
}
//Writes len bytes from the specified byte array starting at offset off to this output stream. 
void GZOutputStream::write(unsigned char* b, int off, int len)
{
	gzwrite(m_file,b+off,len);
}
//Writes the specified byte to this output stream. 
void GZOutputStream::write(int b)
{
	write((unsigned char*)&b,0,1);
}

}