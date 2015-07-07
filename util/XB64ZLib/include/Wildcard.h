// Wildcard.h: interface for the Wildcard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WILDCARD_H__F2E4AD41_76BE_4189_8A2F_107AD54DD6D9__INCLUDED_)
#define AFX_WILDCARD_H__F2E4AD41_76BE_4189_8A2F_107AD54DD6D9__INCLUDED_

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
	Wildcard searcher.
	It compares strings with wilcards.
*/
class Wildcard  
{
public:
	Wildcard();
	virtual ~Wildcard();

	/**
		Compare a string with wildcard.
		@param toSearchText String to compare.
		@param expresionText Wildcard to compare.
		@return <b>true</b> if the string is equal to the wildcard.
	*/
	static bool check(const std::string& toSearchText, 
			const std::string& expresionText);


private:
	static bool check_internal(const std::string& toSearchText, 
									const std::string& expresionText,
									long toSearchPosition,
									long expresionPosition);


};

} // namespace util

} // namespace stream

#endif // !defined(AFX_WILDCARD_H__F2E4AD41_76BE_4189_8A2F_107AD54DD6D9__INCLUDED_)
