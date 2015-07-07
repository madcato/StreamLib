// PacketSorter.cpp: implementation of the PacketSorter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "IInputStream.h"

#include "PacketSorter.h"

#include "BufferedReader.h"
#include "FLineParser.h"
#include "Exceptions.h"
#include "Tokenizer.h"
#include "Date.h"
#include "StringUtil.h"
#include "Wildcard.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/// namespace stream
namespace stream
{

/// namespace util
namespace util
{

PacketSorter::PacketSorter(io::IInputStreamPtr configurationStream)
{
	init(configurationStream);
}

PacketSorter::~PacketSorter()
{

}

void PacketSorter::init(io::IInputStreamPtr configurationStream)
{
	io::BufferedReader reader(configurationStream.get());
	
	// code1:name1:type1(size1)
	FLineParser lineParser("L1:id:string(10),L2:size:long(4),L3:pattern:string(300)");

	while(reader.available())
	{
		std::string line = reader.readLine();
		
		
		std::vector<FLineParser::FToken> format;

		format = lineParser.parse(line);

		LinePattern formato;

		formato.m_id = sstring(format[0].m_value).trim();
		formato.m_size = (long)(sstring(format[1].m_value)).trim();
		formato.m_pattern = sstring(format[2].m_value).trim();

		m_vectorPatterns.push_back(formato);

	}
	
}

std::string PacketSorter::sort(const std::string& line)
{
	std::vector<LinePattern>::iterator it;

	for(it = m_vectorPatterns.begin();it != m_vectorPatterns.end();it++)
	{
		if(Wildcard::check(line,it->m_pattern))
		{
			if((it->m_size == -1)||(line.size() == it->m_size))
				return it->m_id;
		}
	}

	return "";

}

} // namespace util

} // namespace stream
