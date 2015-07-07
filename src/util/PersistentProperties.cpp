// PersistentProperties.cpp: implementation of the PersistentProperties class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "IInputStream.h"
#include "IOutputStream.h"
#include "Exceptions.h"
#include "PropertyBag.h"
#include "Properties.h"

#include "PersistentProperties.h"

#include "Exceptions.h"
#include "BufferedReader.h"
#include "PrintWriter.h"
#include "Tokenizer.h"
#include "Date.h"
#include "StringUtil.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace stream
{

using namespace io;
/// namespace util
namespace util
{

PersistentProperties::PersistentProperties()
{

}

PersistentProperties::~PersistentProperties()
{

}

void PersistentProperties::load(std::auto_ptr<IInputStream> inStream)
{
	BufferedReader reader(inStream.get());

	while(reader.available())
	{
		sstring line = reader.readLine();
	
		line.trim();

		if((line[0] != '#')&&(line != ""))
		{
			
			size_t pos = line.find("=");
			if(pos != std::string::npos)
			{
				setProperty(((sstring)line.substr(0,pos)).trim(),((sstring)line.substr(pos + 1)).trim());
			}			
		}
	}
}

void PersistentProperties::save(std::auto_ptr<IOutputStream> outStream)
{
	PrintWriter printer(outStream.get());

	std::map<std::string,std::string>::iterator it = m_properties.begin();

	while(it != m_properties.end())
	{
		std::string line = it->first + " = " + it->second;
		printer.println(line);
		it++;
	}
}

} // namespace util

} // namespace stream