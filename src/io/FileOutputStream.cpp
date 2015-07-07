// FileOutputStream.cpp: implementation of the FileOutputStream class.
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

namespace stream
{
/// namespace io
namespace io
{

FileOutputStream::FileOutputStream(const char* filename)
{
	init(std::string(filename));
}

FileOutputStream::FileOutputStream(const std::string& filename)
{
	init(filename);
}

FileOutputStream::~FileOutputStream()
{
	if(m_file != 0)
	{
		CloseHandle(m_file);
		m_file = 0;
	}
}

void FileOutputStream::init(const std::string& filename)
{
	m_file = 0;
	m_file = CreateFile(filename.c_str()
		,FILE_WRITE_DATA
		,FILE_SHARE_READ
		,0
		,OPEN_ALWAYS
		,FILE_ATTRIBUTE_NORMAL
		,0);
	
	if(m_file == INVALID_HANDLE_VALUE)
	{
		m_file = 0;
		throw new exceptions::Win32ErrorException(__FILE__,__LINE__);
	}
}

//Closes this output stream and releases any system resources associated with this stream. 
void FileOutputStream::close()
{
	if(m_file != NULL)
	{
		CloseHandle(m_file);
		m_file = 0;
	}
}
//Flushes this output stream and forces any buffered output bytes to be written out. 
void FileOutputStream::flush()
{
	FlushFileBuffers(m_file);
}
//Writes b.length bytes from the specified byte array to this output stream. 
void FileOutputStream::write(unsigned char* b,long length)
{	
	DWORD written = 0;
	WriteFile(m_file,b,length,&written,0);
}
//Writes len bytes from the specified byte array starting at offset off to this output stream. 
void FileOutputStream::write(unsigned char* b, int off, int len)
{
	write(b+off,len);
}
//Writes the specified byte to this output stream. 
void FileOutputStream::write(int b)
{
	write((uchar*)&b,1);
}

} // namespace io

}