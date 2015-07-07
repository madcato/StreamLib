// ReplazeVariables.h: interface for the CReplazeVariables class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPLAZEVARIABLES_H__6FB53FB9_B65F_43FD_AB63_DF73970E636E__INCLUDED_)
#define AFX_REPLAZEVARIABLES_H__6FB53FB9_B65F_43FD_AB63_DF73970E636E__INCLUDED_

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
	Use this class to add variables to a formated text.
	<br>
	Example of formated text:<br>
		This %%VAR1%% is an example for class %%VAR2%%.<br>
		<br>
		After calling methods:<br>
			setVariable("VAR1","text");<br>
			setVariable("VAR2","ReplaceVariables");<br>
		<br>
		The text will be as:<br>
			This text is an example for class ReplaceVariables.<br>
 */
class ReplaceVariables
{
public:
	/**
		Constructor
		@param data Formated text
	*/
	ReplaceVariables(std::string data);
	virtual ~ReplaceVariables();

	/**
		Resets the original data. This is useful to reuse the same ReplaceVariables object several times.
	*/
	void init();

	/**
		Replace variable.
		@param varName Variable name.
		@param text Text who will replace the variable.
	*/
	void setVariable(std::string varName,std::string text);



	/**
		@return the formated text modificated.
	*/
	std::string getData();
private:
	std::string m_data;
	std::string m_originalData;

};

} // namespace util

} // namespace stream
#endif // !defined(AFX_REPLAZEVARIABLES_H__6FB53FB9_B65F_43FD_AB63_DF73970E636E__INCLUDED_)
