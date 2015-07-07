// ClassFactory.cpp: implementation of the ClassFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Exceptions.h"
#include "ClassFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/// namespace stream
namespace stream
{

/// namespace util
namespace util
{

std::map<const std::string,ClassFactory*>* ClassFactory::g_mapObjects = 0;
std::multimap<std::string,std::string>* ClassFactory::g_mapCategories = 0;

ClassFactory::ClassFactory()
{
	
}

ClassFactory::~ClassFactory()
{

}

ClassFactory::registerClass(const std::string& classId,ClassFactory* obj)
{
	if(g_mapObjects == 0)
	{
		g_mapObjects = new std::map<const std::string,ClassFactory*>;
	}

	(*g_mapObjects)[classId] = obj;

}

ClassFactory::registerClassCategory(const std::string& name, const std::string& category)
{
	if(g_mapCategories == 0)
	{
		g_mapCategories = new std::multimap<std::string,std::string>;
	}

	g_mapCategories->insert(std::pair<const std::string, const std::string>(category,name));
}

void* ClassFactory::createObject(const std::string& classId)
{
	if(g_mapObjects == 0)
	{
		throw new exceptions::ClassFactoryException(-1,"ClassFactory::createObject() -- No registered classes");
	}

	std::map<const std::string,ClassFactory*>::iterator it = g_mapObjects->find(classId);
	
	if(it == g_mapObjects->end())
	{
		throw new exceptions::ClassFactoryException(-2,"ClassFactory::createObject() -- No registered class: " + classId);
	}

	return it->second->newObject();
}

std::list<std::string> ClassFactory::getClassNames(const std::string& category)
{
	std::list<std::string> classes;

	std::multimap<std::string,std::string>::iterator it;
	std::multimap<std::string,std::string>::iterator it_end = g_mapCategories->upper_bound(category);
	
	for(it = g_mapCategories->lower_bound(category) ; it != it_end ; it++)
	{
		classes.push_back(it->second);
	}

	return classes;
}

} // namespace util

} // namespace std