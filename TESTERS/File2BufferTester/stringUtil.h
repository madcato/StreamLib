// stringUtil.h: interface for the stringUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRINGUTIL_H__0CAF4058_86C1_46F6_BAFF_E9C7060E518B__INCLUDED_)
#define AFX_STRINGUTIL_H__0CAF4058_86C1_46F6_BAFF_E9C7060E518B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
namespace Stream
{

/**
	Set of utility static functions related to string manipulation.
*/

namespace Exceptions
{

	/**
	Util exception.
	*/
	class UtilStreamException : public StreamException
	{
	public:
		UtilStreamException(int id_code,std::string desc = ""):StreamException(id_code,desc)
		{
		}
	};

	class XMLException : public UtilStreamException
	{
	public:
		XMLException(long id,const std::string& desc):UtilStreamException(id,desc){}
		virtual ~XMLException(){}
	};
} // namespace Exceptions
class stringUtil  
{
public:
	stringUtil();
	virtual ~stringUtil();

	/**
		Cuts up the string using a delimiter and return a vector with n elements. Each element is a piece of the string.
	*/		
	static std::vector<std::string> Split(const std::string& str,const std::string& delimiter);
	/**
		Returns a string containing a copy of a specified string with no leading spaces or tabulators (LTrim).
	*/
	static std::string LTrim(const std::string& str,const std::string& spaces = " \t");
	/**
		Returns a string containing a copy of a specified string with no trailing spaces or tabulators (RTrim).
	*/
	static std::string RTrim(const std::string& str,const std::string& spaces = " \t");
	/**
		Returns a string containing a copy of a specified string with no leading or trailing spaces or tabulators (Trim).
	*/
	static std::string Trim(const std::string& str,const std::string& spaces = " \t");

	/** 
		Splits the string and then trim every element of the vector.
	*/
	static std::vector<std::string> SplitAndTrim(const std::string& str,const std::string& delimiter,const std::string& spaces = " \t");

	/** 
		Converts the string into an int.
	*/
	static int intValue(const std::string& cad);
	/** 
		Converts the string into an unsigned long
	*/
	static unsigned long longValue(const std::string& cad);
	/** 
		Converts the string into a bool.
	*/
	static bool boolValue(const std::string& cad);
	/** 
		Converts the string into a float.
	*/
	static float floatValue(const std::string& cad);
	/** 
		Converts an int into a string.
	*/
	static std::string toString(int);
	/** 
		Converts an unsigned long into a string.
	*/
	static std::string toString(unsigned long);
	/** 
		Converts a bool into a string.
	*/
	static std::string toString(bool);
	/** 
		Converts a float into a string.
	*/
	static std::string toString(float);

	static std::string strlwr(const std::string &str);
	static std::string strupr(const std::string &str);
	static std::string GetXMLData(std::string xml, std::string nodes) throw(Exceptions::XMLException);

private:
	static std::string GetXMLData2(std::string xml,std::string xml_uppercase, std::list<std::string> listnodes) throw(Exceptions::XMLException);
};

} // namespace Stream
#endif // !defined(AFX_STRINGUTIL_H__0CAF4058_86C1_46F6_BAFF_E9C7060E518B__INCLUDED_)
