// CodeBar.h: interface for the CodeBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CODEBAR_H__2D6D5D20_E244_4606_987E_3FFCB25635A1__INCLUDED_)
#define AFX_CODEBAR_H__2D6D5D20_E244_4606_987E_3FFCB25635A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CodeBar  
{
public:
	enum BarType{ TypeA = 103, TypeB = 104, TypeC = 105};
	CodeBar();
	virtual ~CodeBar();

	std::vector<std::string> generate(const std::string& text, BarType type);

	

private:
	static void init();
	static bool m_initialized;
	static std::map<char,int> m_caseA;
	static std::map<char,int> m_caseB;
	static std::map<std::string,int> m_caseC;
	static std::vector<std::string> m_patterns;
	static std::string QuietZone;
	static const int StopChar;

};


#endif // !defined(AFX_CODEBAR_H__2D6D5D20_E244_4606_987E_3FFCB25635A1__INCLUDED_)
