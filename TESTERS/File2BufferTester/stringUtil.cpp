// stringUtil.cpp: implementation of the stringUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Exceptions.h"
#include "stringUtil.h"

#include "Tokenizer.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace Stream
{

stringUtil::stringUtil()
{

}

stringUtil::~stringUtil()
{

}

std::vector<std::string> stringUtil::Split(const std::string& str,const std::string& delimiter)
{

	std::vector<std::string> v;

	
	Stream::Tokenizer tok(str,delimiter,Tokenizer::WITHOUT_BLANCKS);

	while(tok.HasMoreTokens())
	{
		v.push_back(tok.NextToken());
	}

	return v;
}

std::vector<std::string> stringUtil::SplitAndTrim(const std::string& str,const std::string& delimiter,const std::string& spaces)
{
	std::vector<std::string> v = Split(str,delimiter);

	std::vector<std::string>::iterator it = v.begin();

	while(it != v.end())
	{
		*it = Trim(*it,spaces);
		it++;
	}

	return v;
}

std::string stringUtil::LTrim(const std::string& str,const std::string& spaces)
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

std::string stringUtil::RTrim(const std::string& str,const std::string& spaces)
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

std::string stringUtil::Trim(const std::string& str,const std::string& spaces)
{
	return LTrim(RTrim(str,spaces),spaces);
}


int stringUtil::intValue(const std::string& cad)
{
	unsigned long value = 0;
	if(sscanf(cad.c_str(),"%i",&value) != 1)
	{
		throw new Exceptions::UtilStreamException(-1,"int stringUtil::intValue(std::string& cad): Bad integer value string");
	}
	return value;
}

unsigned long stringUtil::longValue(const std::string& cad)
{
	unsigned long value = 0;
	if(sscanf(cad.c_str(),"%u",&value) != 1)
	{
		throw new Exceptions::UtilStreamException(-1,"unsigned long stringUtil::longValue(std::string& cad): Bad unsigned long value string");
	}
	return value;
}

bool stringUtil::boolValue(const std::string& cad)
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
		throw new Exceptions::UtilStreamException(-1,"bool stringUtil::boolValue(std::string& cad): Bad boolean string");
	}

	return false;
}

float stringUtil::floatValue(const std::string& cad)
{
	float value = 0;
	if(sscanf(cad.c_str(),"%e",&value) != 1)
	{
		throw new Exceptions::UtilStreamException(-1,"float stringUtil::floatValue(std::string& cad): Bad float value string");
	}
	return value;
}

std::string stringUtil::toString(int value)
{
	char paso[50];
	sprintf(paso,"%i",value);
	return paso;
}

std::string stringUtil::toString(unsigned long value)
{
	char paso[50];
	sprintf(paso,"%u",value);
	return paso;
}

std::string stringUtil::toString(bool value)
{
	if(value)
		return "true";
	else
		return "false";
}

std::string stringUtil::toString(float value)
{
	char paso[50];
	sprintf(paso,"%e",value);
	return paso;
}

std::string stringUtil::strlwr(const std::string &str)
{
	std::string lwrstr;
	lwrstr = str;
	for (int i=str.size() - 1; i>=0; i--)
	{
		if ( (str[i] >= 'A') && (str[i] <= 'Z') )
		{
			lwrstr[i] = str[i] - 'A' + 'a';
		}
		
	}

	return (lwrstr);
}

std::string stringUtil::strupr(const std::string &str)
{
	std::string uprstr;
	uprstr = str;
	for(int i=str.size() - 1; i>=0; i--)
	{
		if((str[i] >= 'a') && (str[i] <= 'z'))
		{
			uprstr[i] = str[i] - 'a' + 'A';
		}
		
	}

	return (uprstr);
}



std::string stringUtil::GetXMLData2(std::string xml,std::string xml_uppercase, std::list<std::string> listnodes)
{
	if(listnodes.empty())
		return xml;

	long elements = 0;
	std::string node = *(listnodes.begin());  listnodes.pop_front();

	std::vector<std::string> vec = Stream::stringUtil::Split(node,":");

	if(vec.size() == 1)
	{
		elements = 1;
	}
	else
	{
		elements = Stream::stringUtil::longValue(vec[1]) + 1;
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
			throw new Exceptions::XMLException(-1,"Bad tag id: " + node);
		}

		std::string::size_type pos_fin_mayor = xml_uppercase.find(">",pos_fin);
		if(pos_fin_mayor == std::string::npos)
		{
			throw new Exceptions::XMLException(-1,"Bad tag id" + node);
		}

		xml = xml.substr(pos_fin_mayor + 1);
		xml_uppercase = xml_uppercase.substr(pos_fin_mayor + 1);
	}

	std::string::size_type pos_ini = xml_uppercase.find(node_ini);  std::string::size_type pos_fin = xml_uppercase.find(node_fin);

	if((pos_ini == std::string::npos)||(pos_fin == std::string::npos))
	{
		throw new Exceptions::XMLException(-1,"Bad tag id" + node);
	}

	std::string::size_type pos_ini_mayor = xml_uppercase.find(">",pos_ini);  if(pos_ini_mayor == std::string::npos)
	{
		throw new Exceptions::XMLException(-1,"Bad tag id" + node);
	}

	xml = xml.substr(pos_ini_mayor + 1,pos_fin - pos_ini_mayor - 1);  xml_uppercase = xml_uppercase.substr(pos_ini_mayor + 1,pos_fin - pos_ini_mayor - 1);

	return GetXMLData2(xml,xml_uppercase,listnodes);
}

// nodes has format /NODE1:pos1/NODE2:pos2/... means pos1th NODE1 sub pos2th NODE2 sub etc. 
std::string stringUtil::GetXMLData(std::string xml, std::string nodes)
{
	Stream::Tokenizer tok(nodes,"/",Stream::Tokenizer::WITHOUT_BLANCKS);
	std::list<std::string> listnodes;

	while(tok.HasMoreTokens())
	{
		listnodes.push_back(strupr(tok.NextToken()));
	}

	return GetXMLData2(xml,strupr(xml),listnodes);
}


} // namespace Stream