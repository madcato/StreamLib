// CryptException.h: interface for the CryptException class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRYPTEXCEPTION_H__339662F9_7AB5_401B_A7A1_9C91BBC97557__INCLUDED_)
#define AFX_CRYPTEXCEPTION_H__339662F9_7AB5_401B_A7A1_9C91BBC97557__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{

/// namespace exceptions
namespace exceptions
{

class CryptException : public exceptions::Win32ErrorException
{
public:
	CryptException(const std::string& file,long line);
	virtual ~CryptException();

};

} /// namespace exceptions

} /// namespace stream

#endif // !defined(AFX_CRYPTEXCEPTION_H__339662F9_7AB5_401B_A7A1_9C91BBC97557__INCLUDED_)
