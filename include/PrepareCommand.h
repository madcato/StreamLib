// PrepareCommand.h: interface for the PrepareCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PREPARECOMMAND_H__FF442B0B_9A8F_11D4_AD6A_00105AF120EC__INCLUDED_)
#define AFX_PREPARECOMMAND_H__FF442B0B_9A8F_11D4_AD6A_00105AF120EC__INCLUDED_

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
	This class is can help applications to prepare commands of execution.

	This class use commadn templates. Each command has zero or more '?' characters.
	With method 'set' the programer can set the value of this wilcard character.

	Example:<br>
<code><br>
	// We have a command like "copy ? ?", to execute a system command<br>
<br>
	PrepareCommand command;<br>
<br>
	command.setCommand("copy ? ?");<br>
<br>
	command.set(1,"C:\\example1.txt");<br>
	command.set(2,"C:\\example2.txt");<br>
<br>
	::system(command.getFinalCommand());<br>
</code>
*/
class PrepareCommand  
{
public:
	/**
		Constructor.
		@param key_caracter Key character that will be replaced.
	*/
	PrepareCommand(std::string key_caracter = "?");
	virtual ~PrepareCommand();

	/**
		Sets the command template.
		@coomand The command.
	*/
	void setCommand(std::string command);

	/**
		Set the value of the 'index'th position of a key character.
		@param index Position to replace.
		@param valor Value that will replace the key character.
	*/
	void set(int index, std::string valor);

	/**
		@return The final command with the key characters replaced.
	*/
	std::string getFinalCommand() const;
	
private:
	std::string m_command;	// texto con los valores ? para ser substituidos;
						// el valor \? no lo substituye, salvo al tomar el valor final de la cadena.
	std::vector<std::string> m_vValores;

	std::string m_key_carac;

};

} // namespace util

} // namespace stream

#endif // !defined(AFX_PREPARECOMMAND_H__FF442B0B_9A8F_11D4_AD6A_00105AF120EC__INCLUDED_)
