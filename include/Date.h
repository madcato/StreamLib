// Date.h: interface for the Date class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATE_H__4708B02F_A506_435F_BF9C_86E199D59B93__INCLUDED_)
#define AFX_DATE_H__4708B02F_A506_435F_BF9C_86E199D59B93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


namespace stream
{

/// namespace util
namespace util
{

/**
	This class representa a date.
*/
class Date  
{
public:
	Date();
	virtual ~Date();

	int day; // 1-31
	int month; // 1-12
	int year; // 0-XXXXXX

};

} // namespace util

} // namespace stream

#endif // !defined(AFX_DATE_H__4708B02F_A506_435F_BF9C_86E199D59B93__INCLUDED_)
