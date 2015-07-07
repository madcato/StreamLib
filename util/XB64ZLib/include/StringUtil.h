// StringUtil.h: interface for the StringUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_StringUtil_H__0CAF4058_86C1_46F6_BAFF_E9C7060E518B__INCLUDED_)
#define AFX_StringUtil_H__0CAF4058_86C1_46F6_BAFF_E9C7060E518B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream

namespace stream
{


/// namespace exceptions
namespace exceptions
{

	/**
	util exception.
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
} // namespace exceptions

/// namespace util
namespace util
{

/**
	Set of utility static functions related to string manipulation.
*/
class StringUtil  
{
public:
	StringUtil();
	virtual ~StringUtil();

	/**
		Cuts up the string using a delimiter and return a vector with n elements. Each element is a piece of the string.
		By default the empty values found are eliminated. To retrieve empty values, set param 'mode' the value Tokenizer::MODE_ZERO @see Tokenizer
	*/		
	static std::vector<std::string> split(const std::string& str,const std::string& delimiter,Tokenizer::modes mode = Tokenizer::WITHOUT_BLANCKS);
	/**
		Returns a string containing a copy of a specified string with no leading spaces or tabulators (LTrim).
	*/
	static std::string lTrim(const std::string& str,const std::string& spaces = " \t");
	/**
		Returns a string containing a copy of a specified string with no trailing spaces or tabulators (RTrim).
	*/
	static std::string rTrim(const std::string& str,const std::string& spaces = " \t");
	/**
		Returns a string containing a copy of a specified string with no leading or trailing spaces or tabulators (Trim).
	*/
	static std::string trim(const std::string& str,const std::string& spaces = " \t");

	/** 
		Splits the string and then trim every element of the vector.
	*/
	static std::vector<std::string> splitAndTrim(const std::string& str,const std::string& delimiter,const std::string& spaces = " \t");

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
	/** 
		@param nodes has format /NODE1[=pos1][/NODE2[=pos2]]* means pos1th NODE1 sub pos2th NODE2 sub etc. 
		@return the node data.
	*/
	static std::string getXMLData(std::string xml, std::string nodes) throw(exceptions::XMLException);

	/** 
		Returns a new string resulting from replacing all occurrences of oldString in str with newString.
		@param str cadena donde se van a buscar las ocurrencias de oldString
		@param oldString cadena que va a ser reemplazada
		@param newString cadena por la que se va a reemplazar.
		@return una nueva cadena con las cadenas 'oldString' reemplazadas por 'newString'.
	*/
	static std::string replace(const std::string& str, const std::string& oldString, const std::string& newString);

private:
	static std::string getXMLData2(std::string xml,std::string xml_uppercase, std::list<std::string> listnodes) throw(exceptions::XMLException);
};

/**
	This class extends std::string class to provide aditional functionality.
*/
class sstring : public std::string
{
public:

	virtual ~sstring();

	/**
		Default constructor
	*/
	sstring();

	/**
		Copy constructor
	*/
	sstring(const std::string& cpy);
	
	/**
		Cast constructor. Converts a wide-char string to a single-byte string.
	*/
	sstring(const std::wstring& cpy);

	/**
		Constructor. If cpy is null, then the value of this string is "{NULL}"
	*/
	sstring(const char* cpy);

	/** 
		Converts an int into a string.
	*/
	sstring(int);
	/** 
		Converts an unsigned long into a string.
	*/
	sstring(unsigned long);
	/** 
		Converts a bool into a string.
	*/
	sstring(bool);
	/** 
		Converts a float into a string.
	*/
	sstring(float);


	/** 
		Converts the string into an int.
	*/
	operator int() const;
	/** 
		Converts the string into an unsigned long
	*/
	operator unsigned long() const;
	/** 
		Converts the string into a bool.
	*/
	operator bool() const;
	/** 
		Converts the string into a float.
	*/
	operator float() const;

	/**
		@return A string copy.
	*/
	operator std::string() const;

	/**
		@return a wide-char string copy.
	*/
	operator std::wstring() const;

	/**
		Asignament operator.
	*/
	sstring& operator=(const sstring& cpy);
	
	/**
		Asignament operator.
	*/
	sstring& operator=(const char* cpy);

	/**
		Ignore case comparation.
	*/
	bool operator^=(const sstring& str) const;

	/**
		To lowercase
		@return A copy of the string with all lowercase characters.
	*/
	sstring toLower() const;
	/**
		To uppercase
		@return A copy of the string with all uppercase characters.
	*/
	sstring toUpper() const;

	/**
		Cuts up the string using a delimiter and return a vector with n elements. Each element is a piece of the string.
		By default the empty values found are eliminated.
	*/	
	std::vector<std::string> split(const std::string& delimiter) const;

	/**
		Cuts up the string using a delimiter then removes the spaces from each element and return a vector with those elements. Each element is a piece of the string.
		By default the empty values found are eliminated.
	*/
	std::vector<std::string> splitAndTrim(const std::string& delimiter,const std::string& spaces) const;

	/**
		Removes the spaces form the head of the string.
	*/
	sstring lTrim(const std::string& spaces = " \t") const;

	/**
		Removes the spaces form the tail of the string.
	*/
	sstring rTrim(const std::string& spaces = " \t") const;

	/**
		Removes the spaces form the tail and the head of the string.
	*/
	sstring trim(const std::string& spaces = " \t") const;

	/**
		Searchs for 'oldString' and replace all ocurrences with 'newString'
	*/
	sstring replace(const std::string& oldString, const std::string& newString);

	/**
		Tests if this string starts with the specified prefix. 
	*/
	bool startsWith(const std::string& prefix) const;

	/**
		Tests if this string ends with the specified sufix. 
	*/
	bool sstring::endsWith(const std::string& sufix) const;
};

/**
	sstring automatic pointer.
*/
typedef std::auto_ptr<sstring> sstringPtr;

} // namespace util

} // namespace stream
#endif // !defined(AFX_StringUtil_H__0CAF4058_86C1_46F6_BAFF_E9C7060E518B__INCLUDED_)
