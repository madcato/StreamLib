// HTMLTPage.cpp: implementation of the HTMLTPage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Exceptions.h"
#include "memory_stream.h"
#include "Blob.h"

#include "HTMLTPage.h"

#include "ReplaceVariables.h"
#include "Tokenizer.h"
#include "Date.h"
#include "StringUtil.h"
#include "FileUtil.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/// namespace stream
namespace stream
{

/// namespace exceptions
namespace net
{

HTMLTPage::HTMLTPage(const std::string& page)
{
	m_page = page;
}

HTMLTPage::~HTMLTPage()
{

}

void HTMLTPage::setValue(const std::string& id,const std::string& value)
{
	util::ReplaceVariables replacer(m_page);

	replacer.setVariable(id,value);

	m_page = replacer.getData();
}

void HTMLTPage::setValues(const std::map<std::string,std::string>& values)
{
	std::map<std::string,std::string>::const_iterator it;
	
	for(it = values.begin() ; it != values.end() ; it++)
	{
		setValue(it->first,it->second);
	}
}

void HTMLTPage::setSequence(const std::string& id,const std::vector<std::vector<std::string> > sequenceVector)
{

	std::string variable = "%%" + id + "%%";
	size_t ini_position = m_page.find(variable);

	if(ini_position == std::string::npos)
	{
		throw new exceptions::HTMLTPageException(-1,std::string("Sequence '" + id + "' not found(initial position)"));
	}

	std::string str_template = m_page.substr(ini_position + variable.length());

	size_t end_position = m_page.rfind(variable);

	if(end_position == std::string::npos)
	{
		throw new exceptions::HTMLTPageException(-2,std::string("Sequence '" + id + "' not found(end position)"));
	}

	str_template = str_template.substr(0,str_template.rfind(variable));

	end_position += variable.length();

	std::string new_html = "";

	for(int row = 0 ; row < sequenceVector.size() ; row++)
	{
		util::ReplaceVariables replacer(str_template);

		for(int column = 0 ; column < sequenceVector[row].size() ; column++)
		{
			replacer.setVariable(util::StringUtil::toString(column),sequenceVector[row][column]);
		}
		
		new_html += replacer.getData();
	}

	std::string header_html = m_page.substr(0,ini_position);
	std::string tail_html = m_page.substr(end_position);

	m_page = header_html + new_html + tail_html;


}

void HTMLTPage::setFlag(const std::string& id,bool flag)
{

	std::string variable = "%%" + id + "%%";
	size_t ini_position = m_page.find(variable);

	if(ini_position == std::string::npos)
	{
		throw new exceptions::HTMLTPageException(-3,std::string("Flag '" + id + "' not found(initial position)"));
	}

	std::string str_template = m_page.substr(ini_position + variable.length());

	size_t end_position = m_page.rfind(variable);

	if(end_position == std::string::npos)
	{
		throw new exceptions::HTMLTPageException(-4,std::string("Flag '" + id + "' not found(end position)"));
	}

	str_template = str_template.substr(0,str_template.rfind(variable));

	end_position += variable.length();

	std::string new_html = str_template;

	
	std::string header_html = m_page.substr(0,ini_position);
	std::string tail_html = m_page.substr(end_position);

	if(flag)
	{
		m_page = header_html + new_html + tail_html;
	}
	else
	{
		m_page = header_html + tail_html;
	}


}

std::string HTMLTPage::getPage()
{
	return m_page;
}

} // namespace net

} // namespace stream
