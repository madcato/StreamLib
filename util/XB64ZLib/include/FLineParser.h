// FLineParser.h: interface for the FLineParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FLINEPARSER_H__42DB8102_AE0B_492D_AF54_B8C756341DFA__INCLUDED_)
#define AFX_FLINEPARSER_H__42DB8102_AE0B_492D_AF54_B8C756341DFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{

/// namespace util
namespace util
{

class FLineParser  
{
public:
	FLineParser(const std::string& format);
	virtual ~FLineParser();

	


	class FToken
	{
	public:
		std::string m_code;
		std::string m_name;
		std::string m_type;
		ulong m_size;
		std::string m_value;
	};

	std::vector<FToken> parse(const std::string& line);

private:
	std::vector<FToken> m_formatVec;

};

} // namespace util

} // namespace stream

#endif // !defined(AFX_FLINEPARSER_H__42DB8102_AE0B_492D_AF54_B8C756341DFA__INCLUDED_)
