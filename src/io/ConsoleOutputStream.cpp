// onsoleOutputStream.cpp: implementation of the ConsoleOutputStream class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Exceptions.h"
#include "IOutputStream.h"

#include "ConsoleOutputStream.h"

#include "CriticalSection.h"
#include "memory_stream.h"
#include <iostream>



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace stream
{
using namespace util;

/// namespace io
namespace io
{

ConsoleOutputStream::ConsoleOutputStream()
{

}

ConsoleOutputStream::~ConsoleOutputStream()
{

}

///Closes this output stream and releases any system resources associated with this stream. 
void ConsoleOutputStream::close()
{
}
///Flushes this output stream and forces any buffered output bytes to be written out. 
void ConsoleOutputStream::flush()
{
}
///Writes b.length bytes from the specified byte array to this output stream. 
void ConsoleOutputStream::write(unsigned char* b,long length)
{
	write(b,0,length);
}
///Writes len bytes from the specified byte array starting at offset off to this output stream. 
void ConsoleOutputStream::write(unsigned char* b, int off, int len)
{

	auto_array_ptr<char> blob(len,new char[len+1]);
	memcpy(blob.get(),b,len);
	blob[len] = '\0';

	std::cout << blob.get();
}
///Writes the specified byte to this output stream. 
void ConsoleOutputStream::write(int b)
{
	write((unsigned char*)&b,1);
}

/// Writes a line
void ConsoleOutputStream::println(const std::string& str)
{
	std::cout << str << std::endl;
}
/// Writes a line
void ConsoleOutputStream::println(char* str)
{
	std::cout << str << std::endl;
}

} // namespace io

} // namespace stream