#ifndef __PARSEADOR2_H
#define __PARSEADOR2_H
#pragma warning(disable: 4786)	// stl warning

/// namespace stream
namespace stream
{

/// namespace util
namespace util
{

/** This class can be used to parse command line parameters with an OOP style.
	Usage:
	Once created Parseador2 it must be called the methods SetDefaultEntry, SetEmptyEntry, SetValueEntry and SetErrorEntry
	to indicate the objects that require the command line parameters.
	<br>
	Parseador2 parser;<br>
	<br>
	parser.SetDefaultEntry(filesObj);<br>
	parser.SetEmptyEntry(dataObj);<br>
	parser.SetValueEntry(valObj);<br>
	parser.SetErrorEntry(helpObj);<br>
	<br>
	Each of this objects must implement the interface Entry2.<br>
	<br>
	<br>
	A default entry represents the files or other parameters without a '-', '--' or '/'<br>
	Example: copy file1 file2<br>
	<br>
	An empty entry represents a flag in the command line.<br>
	Example: ls -l<br>
	A value entry represents a pair of parameters.<br>
	Example: netstat -p TCP<br>
	The error entry is the object that retrives any error in the process of parse parameters.<br>
	<br>
	@see Entry2
*/


class Parseador2
{
public:
	Parseador2(){m_defaultEntry = 0;}
	/**
		Entry that handle the default parameters. Only one can be specified.
	*/
	void SetDefaultEntry(Entry2* e);
	/**
		Entry that handle the empty parameters. Can be called how many times as necesary.
		@param para name of the parameter that this Entry2 expect.
		@e Entry2
	*/
	void SetEmptyEntry(std::string para,Entry2* e);
	/**
		Entry that handle the values parameters. Can be called how many times as necesary.
		@param para name of the parameter that this Entry2 expect.
		@e Entry2
	*/
	void SetValueEntry(std::string para,Entry2* e);
	/**
		Entry that handle the errors of the Parseador2. Only one can be specified.
	*/
	void SetErrorEntry(Entry2* e);

	
	/**
		Inits the parse process.
		@param argn number of arguments passed to the application.
		@param argv array of string with the arguments passed to the application.
	*/
	bool ParseParams(int argn,char* argv[]);
private:
	Entry2* m_defaultEntry;
	Entry2* m_errorEntry;
	std::map<std::string,Entry2*> m_mapaValueEntry;
	std::map<std::string,Entry2*> m_mapaEmptyEntry;

	/**
		Deletes the '-', '--', '/' of the parameter.
	*/
	bool PonBienParametro(std::string& param);// Devuelve true si el parámetro no  es un valor.
};

} // namespace util

} // namespace stream




#endif __PARSEADOR2_H