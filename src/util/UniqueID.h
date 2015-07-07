// UniqueID.h: interface for the UniqueID class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNIQUEID_H__6A12E708_C1E6_46B5_8F72_7939A7733A28__INCLUDED_)
#define AFX_UNIQUEID_H__6A12E708_C1E6_46B5_8F72_7939A7733A28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{

/// namespace util
namespace util
{

class UniqueID  
{
public:
public:

	char uid[100];
	UniqueID();


	int mult(char* cad);
	unsigned long do_hash(char* cad);
	static int basedata;

	int GenRandom();

	static std::string GenRandomGUID(const std::string& separator = std::string("-"));
};

} // namespace util

} // namespace stream
#endif // !defined(AFX_UNIQUEID_H__6A12E708_C1E6_46B5_8F72_7939A7733A28__INCLUDED_)
