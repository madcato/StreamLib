// console.cpp: implementation of the console class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "console.h"

#include "Exceptions.h"
#include "Tokenizer.h"
#include "Date.h"
#include "StringUtil.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace stream
{

/// namespace io
namespace io
{

	Console console;
	const std::string endln = "\r\n";


Console::Console()
{
	AllocConsole();
}

Console::~Console()
{
	FreeConsole();
}

Console& Console::operator>>(std::string& line)
{

	ulong mode;
	GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE),&mode);

	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE),mode | ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);

	DWORD readed;
	char buffer[6000];
	int ret = ReadConsole(GetStdHandle(STD_INPUT_HANDLE),&buffer,6000,&readed,0);

	if((readed < 2)||(ret == 0))
		throw new exceptions::Win32ErrorException(__FILE__,__LINE__);

	buffer[readed - 2] = 0;
	line = buffer;

	// Dejamos la consola como estaba
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE),mode);

	return *this;
}

Console& Console::operator>>(char& character)
{
	
	ulong mode;
	ulong new_mode;
	GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE),&mode);

	new_mode = mode;
	new_mode &=  ~ENABLE_LINE_INPUT;
	new_mode &=  ~ENABLE_ECHO_INPUT;

	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE),new_mode);
	
	DWORD readed;
	int ret = ReadConsole(GetStdHandle(STD_INPUT_HANDLE),&character,1,&readed,0);

	if((readed != 1)||(ret == 0))
		throw new exceptions::Win32ErrorException(__FILE__,__LINE__);

	// Dejamos la consola como estaba
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE),mode);

	return *this;
}

Console& Console::operator<<(const char* data)
{
	DWORD written = 0;
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE),data,strlen(data),&written,0);

	return *this;
}

Console& Console::operator<<(int data)
{
	util::sstring str(data);
	*this << str.c_str();

	return *this;
}

Console& Console::operator<<(const std::string& str)
{

	*this << str.c_str();

	return *this;
}

Console& Console::operator<<(float data)
{
	util::sstring str(data);
	*this << str.c_str();

	return *this;
}


} // namespace io

} // namespace stream