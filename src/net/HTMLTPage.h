// HTMLTPage.h: interface for the HTMLTPage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTMLTPAGE_H__21DC39E3_AA94_4B8F_81CA_B725EC1B3B28__INCLUDED_)
#define AFX_HTMLTPAGE_H__21DC39E3_AA94_4B8F_81CA_B725EC1B3B28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{

	
	/// namespace exceptions
	namespace exceptions
	{
	class HTMLTPageException : public StreamException
	{
	public:
		HTMLTPageException(long result, const std::string& message):StreamException(result,message){}
		virtual ~HTMLTPageException()
		{
			
		}
	};
	} // namespace exceptions

/// namespace net
namespace net
{

/**
	Class that manage the HTML tamplates.

	An HTMl tamplate is a HTML regular page that includes some special variables.
	Those variables has the followin format: <code>%%VARIABLE_NAME%%</code>
	Programmer can set the value of this variables in the page code by calling
	the method '@see setValue'.

	Also an HTML template can include sequences.
	A sequence has the following format: 
	<code>
	%%SEQUENCE_ID%%
		<option value="%%1%%">%%2%%</option>
	%%SEQUENCE_ID%%
	</code>
	By calling method '@see setSequence' the characters between %%SEQUENCE_ID%% are repeated
	a number of times equal to the number of rows passed to in method. Then each column of each row 
	is placed in its corresponing location: first columnn to %1%, second column to %2%, etc.

	The third way to manage HTML tamplates is whith flags.
	The format of flags is similar to the sequences but has no columns:
	<code>
	%%FLAG_ID%%
		<img src="..."></img>
	%%FLAG_ID%%
	</code>
	By calling method '@see setFlag' programers can set or unset this flag.
	Setting the flag means that the characters between the flag identificator are
	palced in the output page. But setting the flag to false, those character are eliminated.
*/
class HTMLTPage  
{
public:
	HTMLTPage(const std::string& page);
	virtual ~HTMLTPage();

	/**
		Sets a value in the HTML template.
		@param id Value identificator.
		@param value Value to set.
	*/
	void setValue(const std::string& id,const std::string& value);
	
	/**
		Sets the values in the HTML template.
		Searches the value names in the HTML template and repalce it with 
		the value.
		@param values Values to set.
	*/
	void setValues(const std::map<std::string,std::string>& values);

	/**
		Sets a sequence in the HTML template.
		@param id Sequence identificator.
		@param sequenceTable A table(vector of string vectors) with the data to set.
	*/
	void setSequence(const std::string& id,const std::vector<std::vector<std::string> > sequenceTable);

	/**
		Sets or unsets a flag.
		@param id Flag identificator.
		@param flag If true, charaters are set, If false, they are not placed.
	*/
	void setFlag(const std::string& id,bool flag);

	/**
		Return the output of the procces of replacing the identificators
	*/
	std::string getPage();

private:
	std::string m_page;
};

} // namespace net

} // namespace stream

#endif // !defined(AFX_HTMLTPAGE_H__21DC39E3_AA94_4B8F_81CA_B725EC1B3B28__INCLUDED_)
