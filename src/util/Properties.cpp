// Properties.cpp: implementation of the Properties class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"


#include "Exceptions.h"
#include "PropertyBag.h"

#include "Properties.h"

#include "IInputStream.h"
#include "IOutputStream.h"
#include "BufferedReader.h"
#include "PrintWriter.h"
#include "Tokenizer.h"
#include "Date.h"
#include "stringUtil.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace stream
{

/// namespace util
namespace util
{

Properties::Properties()
{

}

Properties::~Properties()
{
	m_properties.clear();
}

Properties& Properties::add(const Properties& param)
{
	std::vector<std::string> keyVector = param.propertyNames();

	std::vector<std::string>::iterator it = keyVector.begin();

	while(it != keyVector.end())
	{
		setProperty(*it,param.getProperty(*it));
		it++;
	}

	return *this;
}

std::string Properties::getProperty(const std::string& key,const std::string& defaultValue) const
{
	std::map<std::string,std::string>::const_iterator it = m_properties.find(key);
	
	if(it == m_properties.end())
	{
		return defaultValue;
	}

	return it->second;
}

void Properties::setProperty(const std::string& key,const std::string& value)
{
	m_properties[key] = value;
}

std::vector<std::string> Properties::propertyNames() const
{
	std::vector<std::string> keyVector;

	std::map<std::string,std::string>::const_iterator it = m_properties.begin();


	while(it != m_properties.end())
	{
		keyVector.push_back(it->first);
		it++;
	}

	return keyVector;
}

void Properties::removeProperty(const std::string& param)
{
	std::map<std::string,std::string>::iterator it = m_properties.find(param);
	
	if(it != m_properties.end())
	{
		m_properties.erase(it);
	}
}

std::map<std::string,std::string> Properties::getMap()
{
	return m_properties;
}

void Properties::setMap(const std::map<std::string,std::string>& values)
{
	m_properties = values;
}

} // namespace util

} // namespace stream