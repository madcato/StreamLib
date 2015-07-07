// W3CLog1.cpp: implementation of the W3CLog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Exceptions.h"
#include "ILog.h"
#include "PropertyBag.h"
#include "Properties.h"

#include "CW3CLog.h"

#include "CriticalSection.h"
#include "memory_stream.h"
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

std::auto_ptr<W3CLog> W3CLog::m_instance(0);

W3CLog::W3CLog()
{

}

W3CLog::~W3CLog()
{

}



void W3CLog::traceOn(std::auto_ptr<ILog> log, const std::string& appInfo, const std::string& format)
{
	m_format = ((sstring)format).split(" ");

	m_log = log;
	
	m_log->trace("");
	char date[100],time[100];
	_strtime(time);
	_strdate(date);

	std::string buffer;
	buffer = "#Software: " + appInfo;  //TRACER_FORMAT("%s %s\r\n","#Software:",id_cliente);
	m_log->trace(buffer);
	
	buffer = "#Version: 1.0";
	m_log->trace(buffer);
	
	buffer = "#Date: " + std::string(date) + std::string(" ") + time;
	m_log->trace(buffer);

	buffer = "#Fields: " + format;
	m_log->trace(buffer);

	buffer = "#Start-Date: " + std::string(date) + std::string(" ") + time;
	m_log->trace(buffer);

	



}

void W3CLog::trace(const Properties& prop)
{
	
	std::string buffer = "";

	std::vector<std::string>::iterator it = m_format.begin();

	while(it != m_format.end())
	{
		if(buffer != "")
		{
			buffer += " ";
		}

		if(*it == "date")
		{
			char date[100];
			_strdate(date);
			buffer += date;			
			it++;
			continue;
		}
		
		if(*it == "time")
		{
			char time[100];
			_strtime(time);
			buffer += time;			
			it++;
			continue;
		}
		if(sstring(*it).endsWith("-s"))
		{
			buffer += "\"";
		}
		buffer += prop.getProperty(*it);
		if(sstring(*it).endsWith("-s"))
		{
			buffer += "\"";
		}
		

		it++;
	}
	m_log->trace(buffer);
	
}

void W3CLog::traceOff()
{
	char date[100],time[100];
	_strtime(time);
	_strdate(date);

	std::string buffer;
	
	buffer = "#End-Date: " + std::string(date) + std::string(" ") + time;
	m_log->trace(buffer);

	m_log->traceOff();
}

W3CLog* W3CLog::getInstance()
{
	if(m_instance.get() == 0)
	{
		m_instance = std::auto_ptr<W3CLog>(new W3CLog());
	}

	return m_instance.get();
}

} // namespace util

} // namespace stream