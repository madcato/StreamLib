// console.h: interface for the console class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONSOLE_H__EBF25166_E9E2_4154_81F1_7F2E6FC3BFCD__INCLUDED_)
#define AFX_CONSOLE_H__EBF25166_E9E2_4154_81F1_7F2E6FC3BFCD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace stream
{

/// namespace io
namespace io
{

/**
	Console input/output.
	Use the global variable <b>console</b>.
	Example:
	<code>
		string line;
		console >> line;
		char c;
		console >> c;
	</code>
*/
class Console  
{
public:
	Console();
	virtual ~Console();

	Console& operator<<(const char*);
	Console& operator<<(int);
	Console& operator<<(const std::string&);
	Console& operator<<(float data);

	Console& operator>>(std::string& line);
	Console& operator>>(char& character);

};

extern Console console;
extern const std::string endln;

} // namespace io

} // namespace stream

#endif // !defined(AFX_CONSOLE_H__EBF25166_E9E2_4154_81F1_7F2E6FC3BFCD__INCLUDED_)
