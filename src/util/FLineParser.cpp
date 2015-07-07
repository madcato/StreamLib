// FLineParser.cpp: implementation of the FLineParser class.
//
//////////////////////////////////////////////////////////////////////
#include "Stdafx.h"

#include "FLineParser.h"

#include "Exceptions.h"
#include "memory_stream.h"
#include "Tokenizer.h"
#include "Date.h"
#include "StringUtil.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/// namespace stream
namespace stream
{

/// namespace util
namespace util
{

FLineParser::FLineParser(const std::string& format)
{

	Tokenizer tok1(format,",");

	FToken ft;

	// Trocea el siguiente formato "code1:name1:type1(size1),code2:name2:type2(size2),..."

	while(tok1.HasMoreTokens())
	{
		std::string element = tok1.NextToken();

		Tokenizer tok2(element,":");

		ft.m_code = tok2.NextToken();
		ft.m_name = tok2.NextToken();
		Tokenizer tok3(tok2.NextToken(),"()");
		ft.m_type = tok3.NextToken();
		ft.m_size = (ulong)(sstring(tok3.NextToken()));

		m_formatVec.push_back(ft);

	}

}

FLineParser::~FLineParser()
{

}

std::vector<FLineParser::FToken> FLineParser::parse(const std::string& line)
{
	std::vector<FToken> result;

	std::vector<FToken>::iterator it;
	int pos = 0;
	for(it = m_formatVec.begin(); it != m_formatVec.end() ; it++)
	{
		FToken current = *it;

		current.m_value = line.substr(pos,current.m_size);
		pos += current.m_size;
		
		result.push_back(current);
	}
	
	return result;
}

} // namespace util

} // namespace stream
