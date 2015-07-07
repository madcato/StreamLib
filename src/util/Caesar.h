// Caesar.h: interface for the CCaesar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAESAR_H__3AA7B1C0_98CF_44AD_A6A6_10D07439DA8D__INCLUDED_)
#define AFX_CAESAR_H__3AA7B1C0_98CF_44AD_A6A6_10D07439DA8D__INCLUDED_

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
	This class ofuscate data in a simple way: using a psudo-caesar cipher mehtod.
	It doesn´t realice any encryption only ofuscates data.
*/
class CCaesar  
{
public:
	CCaesar();
	virtual ~CCaesar();

	/**
		Ofuscate data.
		@param sttr string to be ofuscated.
		@return The ofuscated string
	*/
	static std::string Ofuscate(const std::string& sttr);
	/**
		Unofuscate data.
		@param sttr strign to be unofuscated.
		@param The string unofuscated.
	*/
	static std::string UnOfuscate(const std::string& sttr);

};

} // namespace util

} // namespace stream

#endif // !defined(AFX_CAESAR_H__3AA7B1C0_98CF_44AD_A6A6_10D07439DA8D__INCLUDED_)
