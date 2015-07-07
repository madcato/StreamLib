// CryptException.cpp: implementation of the CryptException class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Exceptions.h"

#include "CryptException.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/// namespace stream
namespace stream
{

/// namespace exceptions
namespace exceptions
{

CryptException::CryptException(const std::string& file,long line):Win32ErrorException(file,line)
{

}

CryptException::~CryptException()
{

}

} /// namespace exceptions

} /// namespace stream
