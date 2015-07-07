// FileInputStream.cpp: implementation of the FileInputStream class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "IInputStream.h"
#include "Exceptions.h"
#include "FileInputStream.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace stream
{
/// namespace io
namespace io
{

FileInputStream::FileInputStream(const char* filename,long ini_position, long end_position)throw(exceptions::FileStreamException*)
{
	init(std::string(filename));
}

FileInputStream::FileInputStream(const std::string& filename,long ini_position, long end_position)throw(exceptions::FileStreamException*)
{
	init(filename);
}

void FileInputStream::init(const std::string& filename)
{
	m_file = CreateFile(filename.c_str()
		, FILE_READ_DATA // DWORD dwDesiredAccess,
		, FILE_SHARE_READ | FILE_SHARE_WRITE //DWORD dwShareMode,
		, 0 // LPSECURITY_ATTRIBUTES lpSecurityAttributes,
		, OPEN_EXISTING // DWORD dwCreationDisposition,
		, FILE_ATTRIBUTE_ARCHIVE // DWORD dwFlagsAndAttributes,
		, 0 // HANDLE hTemplateFile
		);
	
	
	if(m_file == INVALID_HANDLE_VALUE)
	{
		m_file = 0;
		throw new exceptions::FileStreamException(-1,(std::string("Can't open file ") + filename + " for read").c_str());
	}
	
	m_available = GetFileSize(m_file,0);
}

FileInputStream::~FileInputStream()
{
	if(m_file != 0)
	{
		CloseHandle(m_file);
		m_file = 0;
	}
}

//Returns the number of bytes that can be read (or skipped over) from this input stream without blocking by the next caller of a method for this input stream. 
int FileInputStream::available()
{
	return m_available;
}
//Closes this input stream and releases any system resources associated with the stream. 
void FileInputStream::close()
{
	if(m_file != 0)
	{
		CloseHandle(m_file);
		m_file = 0;
	}
}
//Marks the current position in this input stream. 
void FileInputStream::mark(int readlimit)
{
	
}
//Tests if this input stream supports the mark and reset methods. 
bool FileInputStream::markSupported()
{
	return false;
}
//Reads the next byte of data from the input stream. 
int FileInputStream::read()
{
	char data[4];
	DWORD readed = 0;
	
	m_available--;
	
	if(!ReadFile(
		m_file //HANDLE hFile,
		, data // LPVOID lpBuffer,
		, 1 // DWORD nNumberOfBytesToRead,
		, &readed // LPDWORD lpNumberOfBytesRead,
		, 0 // LPOVERLAPPED lpOverlapped
		))
	{
		return -1;
	}
	
	return data[0];
}
//Reads some number of bytes from the input stream and stores them into the buffer array b. 
int FileInputStream::read(unsigned char* b,long length)
{	
	return read(b,0,length);
}
//Reads up to len bytes of data from the input stream into an array of bytes. 
int FileInputStream::read(unsigned char* b, int off, int len)
{
	DWORD readed = 0;
	
	if(!ReadFile(
		m_file //HANDLE hFile,
		, b+off // LPVOID lpBuffer,
		, len // DWORD nNumberOfBytesToRead,
		, &readed // LPDWORD lpNumberOfBytesRead,
		, 0 // LPOVERLAPPED lpOverlapped
		))
	{
		
	}
	
	m_available -= readed;
	return readed;
}
//Repositions this stream to the position at the time the mark bytes was last called on this input stream. 
void FileInputStream::reset()
{
}
//Skips over and discards n bytes of data from this input stream. 
long FileInputStream::skip(long n)
{
	return 0;
}

} // namespace io

}