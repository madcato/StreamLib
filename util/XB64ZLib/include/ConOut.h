// ConOut.h: interface for the ConOut class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONOUT_H__0743B5F0_2E22_4862_B7F1_1A85C38EA28D__INCLUDED_)
#define AFX_CONOUT_H__0743B5F0_2E22_4862_B7F1_1A85C38EA28D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace stream
{

/// namespace io
namespace io
{

/**
	Console output.
	Use the global variable <b>csout</b>.
	Example:
	<code>
		csout << "Hi world" << x << endln;
	</code>
*/
class ConOut  
{
public:
	ConOut();
	virtual ~ConOut();

	ConOut& operator<<(const char*);
	ConOut& operator<<(int);
	ConOut& operator<<(const std::string&);
};

extern ConOut csout;
extern const std::string endln;

} // namespace io

} // namespace stream

#endif // !defined(AFX_CONOUT_H__0743B5F0_2E22_4862_B7F1_1A85C38EA28D__INCLUDED_)
