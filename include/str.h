// str.h: interface for the str class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STR_H__DB3B71AA_9987_4387_822C_5D4470FCF001__INCLUDED_)
#define AFX_STR_H__DB3B71AA_9987_4387_822C_5D4470FCF001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace stream
{

/// namespace util
namespace util
{

/**
	String class
*/
class str  
{
public:
	str();
	str(const str& cpy);
	virtual ~str();

	str operator+(const str& cpy) const;
	bool operator==(const str& cpy) const;
	str& operator+=(const str& cpy);

	str& operator=(const str& cpy);

	const char* c_str() const;
	
	long length() const;

	char& operator[](int i);
	char operator[](int i) const;



private:
	char* m_data;
	long m_dataLength;
};

} // namespace util

} // namespace stream

#endif // !defined(AFX_STR_H__DB3B71AA_9987_4387_822C_5D4470FCF001__INCLUDED_)
