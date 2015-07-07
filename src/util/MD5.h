// MD5.h: interface for the MD5 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MD5_H__65D3AF89_2655_499E_A5DA_A972E7A3943F__INCLUDED_)
#define AFX_MD5_H__65D3AF89_2655_499E_A5DA_A972E7A3943F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{
/// namespace util
namespace util
{

/**
	MD5 utility class. DON'T USE IT.
*/
class MD5  
{
public:
	MD5();
	virtual ~MD5();

	/**
		Code the buffer to hexadecimal.
		@param buffer. Data.
		@param length. Data length.
		@return The encoded value.
	*/
	static std::string calculateToHex(char* buffer,int length);

	struct md5Hash{ long a,b,c,d;};
	union uMD5
	{
		struct md5Hash md5;
		char buffer[16];
	};


	static uMD5 calculateToMD5(char* sInp,int length);

};

} // namespace util

} //namespace stream

#endif // !defined(AFX_MD5_H__65D3AF89_2655_499E_A5DA_A972E7A3943F__INCLUDED_)
