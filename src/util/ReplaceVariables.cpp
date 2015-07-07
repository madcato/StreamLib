// ReplaceVariables.cpp: implementation of the ReplaceVariables class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "ReplaceVariables.h"

#include "Exceptions.h"
#include "Tokenizer.h"
#include "Date.h"
#include "StringUtil.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace stream
{

/// namespace util
namespace util
{

ReplaceVariables::ReplaceVariables(std::string data)
{
	m_originalData = data;
	init();
}

ReplaceVariables::~ReplaceVariables()
{

}

void ReplaceVariables::init()
{
	m_data = m_originalData;
}

void ReplaceVariables::setVariable(std::string varName,std::string text)
{
	std::string variable = "%%" + varName + "%%";

	m_data = StringUtil::replace(m_data,variable,text);
	
}


std::string ReplaceVariables::getData()
{
	return m_data;
}

} // namespace util

} // namespace stream