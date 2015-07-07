// ConsoleInputStream.cpp: implementation of the CConsoleInputStream class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "IInputStream.h"
#include "ConsoleInputStream.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace stream
{

/// namespace io
namespace io
{

CConsoleInputStream::CConsoleInputStream()
{

}

CConsoleInputStream::~CConsoleInputStream()
{

}



int CConsoleInputStream::available()
{
	return 0;
}

void CConsoleInputStream::close()
{
}

void CConsoleInputStream::mark(int readlimit)
{
}

bool CConsoleInputStream::markSupported()
{
	return false;
}

int CConsoleInputStream::read()
{
	return 0;
}

int CConsoleInputStream::read(unsigned char* b,long length)
{
	return 0;
}

int CConsoleInputStream::read(unsigned char* b, int off, int len)
{
	return 0;
}

void CConsoleInputStream::reset()
{
}

long CConsoleInputStream::skip(long n)
{
	return 0;
}

} // namespace io

}