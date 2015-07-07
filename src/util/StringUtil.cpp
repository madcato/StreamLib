// StringUtil.cpp: implementation of the StringUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

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

StringUtil::StringUtil()
{

}

StringUtil::~StringUtil()
{

}

std::vector<std::string> StringUtil::split(const std::string& str,const std::string& delimiter, Tokenizer::modes mode)
{

	std::vector<std::string> v;

	
	Tokenizer tok(str,delimiter,mode);

	while(tok.HasMoreTokens())
	{
		v.push_back(tok.NextToken());
	}

	return v;
}

std::vector<std::string> StringUtil::splitAndTrim(const std::string& str,const std::string& delimiter,const std::string& spaces)
{
	std::vector<std::string> v = split(str,delimiter);

	std::vector<std::string>::iterator it = v.begin();

	while(it != v.end())
	{
		*it = trim(*it,spaces);
		it++;
	}

	return v;
}

std::string StringUtil::lTrim(const std::string& str,const std::string& spaces)
{
	std::string::size_type st = str.find_first_not_of(spaces);
	
	if(st == std::string::npos)
	{
		return "";
	}
	std::string ret;
	
	ret.assign(str,st,str.length() - st);

	return ret;
}

std::string StringUtil::rTrim(const std::string& str,const std::string& spaces)
{
	std::string::size_type st = str.find_last_not_of(spaces);
	
	if(st == std::string::npos)
	{
		return "";
	}
	std::string ret;
	
	ret.assign(str,0,st + 1);

	return ret;
}

std::string StringUtil::trim(const std::string& str,const std::string& spaces)
{
	return lTrim(rTrim(str,spaces),spaces);
}


int StringUtil::intValue(const std::string& cad)
{
	unsigned long value = 0;
	if(sscanf(cad.c_str(),"%i",&value) != 1)
	{
		throw new exceptions::UtilStreamException(-1,"int StringUtil::intValue(std::string& cad): Bad integer value string");
	}
	return value;
}

unsigned long StringUtil::unsignedLongValue(const std::string& cad)
{
	unsigned long value = 0;
	if(sscanf(cad.c_str(),"%u",&value) != 1)
	{
		throw new exceptions::UtilStreamException(-1,"unsigned long StringUtil::longValue(std::string& cad): Bad unsigned long value string");
	}
	return value;
}

long StringUtil::longValue(const std::string& cad)
{
	long value = 0;
	if(sscanf(cad.c_str(),"%d",&value) != 1)
	{
		throw new exceptions::UtilStreamException(-1,"unsigned long StringUtil::longValue(std::string& cad): Bad unsigned long value string");
	}
	return value;
}

bool StringUtil::boolValue(const std::string& cad)
{
	char paso[5];

	memcpy(paso,cad.c_str(),4);
	paso[4] = '\0';
	::strupr(paso);
	if(strcmp(paso,"TRUE") == 0)
	{
		return true;
	}
	else
	if(strcmp(paso,"FALSE") == 0)
	{
		return false;
	}
	else
	{
		throw new exceptions::UtilStreamException(-1,"bool StringUtil::boolValue(std::string& cad): Bad boolean string");
	}

	return false;
}

float StringUtil::floatValue(const std::string& cad)
{
	float value = 0;
	if(sscanf(cad.c_str(),"%e",&value) != 1)
	{
		throw new exceptions::UtilStreamException(-1,"float StringUtil::floatValue(std::string& cad): Bad float value string");
	}
	return value;
}

Date StringUtil::dateValue(const std::string& cad)
{
	Date value;
	/*float value = 0;
	if(sscanf(cad.c_str(),"%e",&value) != 1)
	{
		throw new exceptions::UtilStreamException(-1,"float StringUtil::floatValue(std::string& cad): Bad float value string");
	}*/
	return value;
}

std::string StringUtil::toString(int value)
{
	char paso[50];
	sprintf(paso,"%i",value);
	return paso;
}

std::string StringUtil::toString(unsigned long value)
{
	char paso[50];
	sprintf(paso,"%u",value);
	return paso;
}

std::string StringUtil::toString(bool value)
{
	if(value)
		return "true";
	else
		return "false";
}

std::string StringUtil::toString(float value)
{
	char paso[50];
	sprintf(paso,"%e",value);
	return paso;
}

std::string StringUtil::toString(const Date& value)
{
	/*char paso[50];
	sprintf(paso,"%e",value);
	return paso;*/
	return "";
}


std::string StringUtil::strlwr(const std::string &str)
{
	std::string lwrstr;
	lwrstr = str;
	for (int i=str.size() - 1; i>=0; i--)
	{
		if ( (str[i] >= 'A') && (str[i] <= 'Z') )
		{
			lwrstr[i] = str[i] - 'A' + 'a';
			continue;
		}

		switch(str[i])
		{
		case 'Á':
			{
				lwrstr[i] = 'á';
				continue;
			}
		case 'Í':
			{
				lwrstr[i] = 'í';
				continue;
			}
		case 'É':
			{
				lwrstr[i] = 'é';
				continue;
			}
		case 'Ñ':
			{
				lwrstr[i] = 'ñ';
				continue;
			}
		case 'Ó':
			{
				lwrstr[i] = 'ó';
				continue;
			}
		case 'Ú':
			{
				lwrstr[i] = 'ú';
				continue;
			}
		}
		
	}

	return (lwrstr);
}

std::string StringUtil::strupr(const std::string &str)
{
	std::string uprstr;
	uprstr = str;
	for(int i=str.size() - 1; i>=0; i--)
	{
		if((str[i] >= 'a') && (str[i] <= 'z'))
		{
			uprstr[i] = str[i] - 'a' + 'A';
			continue;
		}

		switch(str[i])
		{
		case 'á':
			{
				uprstr[i] = 'Á';
				continue;
			}
		case 'í':
			{
				uprstr[i] = 'Í';
				continue;
			}
		case 'é':
			{
				uprstr[i] = 'É';
				continue;
			}
		case 'ñ':
			{
				uprstr[i] = 'Ñ';
				continue;
			}
		case 'ó':
			{
				uprstr[i] = 'Ó';
				continue;
			}
		case 'ú':
			{
				uprstr[i] = 'Ú';
				continue;
			}
		}	
	}

	return (uprstr);
}



std::string StringUtil::getXMLData2(std::string xml,std::string xml_uppercase, std::list<std::string> listnodes)
{
	if(listnodes.empty())
		return xml;

	long elements = 0;
	std::string node = *(listnodes.begin());
	listnodes.pop_front();

	std::vector<std::string> vec = StringUtil::split(node,"=");

	if(vec.size() == 1)
	{
		elements = 1;
	}
	else
	{
		elements = StringUtil::longValue(vec[1]) + 1;
	}

	node = vec[0];

	std::string node_ini = "<" + node;
	std::string node_fin = "</" + node;

	while(elements > 1)
	{
		elements--;


		std::string::size_type pos_fin = xml_uppercase.find(node_fin);
		if(pos_fin == std::string::npos)
		{
			throw new exceptions::XMLException(-1,"Bad tag format1: " + node);
		}

		std::string::size_type pos_fin_mayor = xml_uppercase.find(">",pos_fin);
		if(pos_fin_mayor == std::string::npos)
		{
			throw new exceptions::XMLException(-1,"Bad tag format2: " + node);
		}

		xml = xml.substr(pos_fin_mayor + 1);
		xml_uppercase = xml_uppercase.substr(pos_fin_mayor + 1);
	}

	std::string::size_type pos_ini = xml_uppercase.find(node_ini);
	std::string::size_type pos_fin = xml_uppercase.find(node_fin);

	if((pos_ini == std::string::npos)||(pos_fin == std::string::npos))
	{
		throw new exceptions::XMLException(-1,"Bad tag name: " + node);
	}

	std::string::size_type pos_ini_mayor = xml_uppercase.find(">",pos_ini);
	
	if(pos_ini_mayor == std::string::npos)
	{
		throw new exceptions::XMLException(-1,"Bad tag format3: " + node);
	}

	xml = xml.substr(pos_ini_mayor + 1,pos_fin - pos_ini_mayor - 1);
	xml_uppercase = xml_uppercase.substr(pos_ini_mayor + 1,pos_fin - pos_ini_mayor - 1);

	return getXMLData2(xml,xml_uppercase,listnodes);
}

// nodes has format /NODE1[=pos1][/NODE2[=pos2]]/... means pos1th NODE1 sub pos2th NODE2 sub etc. 
std::string StringUtil::getXMLData(std::string xml, std::string nodes)
{
	Tokenizer tok(nodes,"/",Tokenizer::WITHOUT_BLANCKS);
	std::list<std::string> listnodes;

	while(tok.HasMoreTokens())
	{
		listnodes.push_back(strupr(tok.NextToken()));
	}

	return getXMLData2(xml,strupr(xml),listnodes);
}

std::string StringUtil::replace(const std::string& str, const std::string& oldString, const std::string& newString)
{

	if(oldString == "")
	{
		return str;
	}
	std::string finalStr;

	finalStr = str;

	size_t pos = finalStr.find(oldString,0);

	while(pos != std::string::npos)
	{

		finalStr.replace(pos,oldString.length(),newString);

		pos = finalStr.find(oldString,pos + newString.length());		
	}


	return finalStr;
}



sstring::~sstring(){}

sstring::sstring()
{}

sstring::sstring(size_type l,char c):std::basic_string<char, std::char_traits<char>, std::allocator<char> >(l,c)
{}

sstring::sstring(const std::string& cp)
{
	((std::string*)this)->operator=(cp.c_str());
}

sstring::sstring(const std::wstring& cp)
{
	*this = "";
	for(int i = 0 ; i < cp.length() ; i++)
		*this += cp[i];
}

sstring::sstring(const char* cp)
{
	if(cp == 0)
	{
		*this = "{NULL}";
	}
	else
	{
		((std::string*)this)->operator=(cp);
	}
}

sstring::sstring(int value)
{
	*this = (sstring)StringUtil::toString(value);
}

sstring::sstring(unsigned long value)
{
	*this = StringUtil::toString(value);
}

sstring::sstring(bool value)
{
	*this = StringUtil::toString(value);
}

sstring::sstring(float value)
{
	*this = StringUtil::toString(value);
}

sstring::operator int() const
{
	return StringUtil::intValue(*this);
}

sstring::operator unsigned long() const
{
	return StringUtil::unsignedLongValue(*this);
}

sstring::operator long() const
{
	return StringUtil::longValue(*this);
}

sstring::operator bool() const
{
	return StringUtil::boolValue(*this);
}

sstring::operator float() const
{
	return StringUtil::floatValue(*this);
}

sstring::operator std::string() const
{
	return std::string(this->c_str());
}

sstring::operator std::wstring() const
{
	std::wstring str = L"";

	for(int i = 0 ; i < length() ; i++)
		str += (*this)[i];

	return str;
}

sstring& sstring::operator=(const sstring& cp)
{
	((std::string*)this)->operator=(cp);
	return *this;
}

sstring& sstring::operator=(const char* cp)
{
	((std::string*)this)->operator=(cp);
	return *this;
}

bool sstring::operator^=(const sstring& str) const
{
	std::string s1,s2;
	s1 = StringUtil::strupr(*this);
	s2 = StringUtil::strupr(str);
	return s1==s2;
}

sstring sstring::toLower() const
{
	return StringUtil::strlwr(*this);
}

sstring sstring::toUpper() const
{
	return StringUtil::strupr(*this);
}

std::vector<std::string> sstring::split(const std::string& delimiter) const
{
	return StringUtil::split(*this,delimiter);
}

std::vector<std::string> sstring::splitAndTrim(const std::string& delimiter,const std::string& spaces) const
{
	return StringUtil::splitAndTrim(*this,delimiter,spaces);
}

sstring sstring::lTrim(const std::string& spaces) const
{
	return StringUtil::lTrim(*this,spaces);
}

sstring sstring::rTrim(const std::string& spaces) const
{
	return StringUtil::rTrim(*this,spaces);
}

sstring sstring::trim(const std::string& spaces) const
{
	return StringUtil::trim(*this,spaces);
}

sstring sstring::replace(const std::string& oldString, const std::string& newString)
{
	return StringUtil::replace(*this,oldString,newString);
}

bool sstring::startsWith(const std::string& prefix) const
{
	size_t position = this->find(prefix);

	if(position == 0)
		return true;

	return false;
}

bool sstring::endsWith(const std::string& sufix) const
{
	size_t position = this->rfind(sufix);

	if(position == (this->length() - sufix.length()))
		return true;

	return false;
}

} // namespace util

} // namespace stream