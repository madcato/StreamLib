  // W3CLog1.cpp: implementation of the LiteLog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Exceptions.h"
#include "CriticalSection.h"
#include "ILog.h"
#include "IInputStream.h"
#include "IOutputStream.h"
#include "Socket.h"
#include "Log.h"

#include "LiteLog.h"

#include "System.h"
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

std::auto_ptr<LiteLog> LiteLog::m_instance(0);

LiteLog::LiteLog()
{
	m_log =  std::auto_ptr<ILog>(new Log());
	m_logLevel = LOG_ALL;
}

LiteLog::~LiteLog()
{
	traceOff();
}




void LiteLog::traceOn(const std::string& fileName, const std::string& appInfo,const long logLevel,const eOpenType& openType)
{

	m_logLevel = logLevel;
	//"SCRLdapBrowser v1.1.0"
	//"date time s-dns x-serialnumber x-nif x-certstatus x-error"
	m_log->traceOn(fileName,openType); //CONTINUE_LOG);

	char date[100],time[100];
	_strtime(time);
	_strdate(date);

	std::string buffer;
	buffer = "#Software: " + appInfo;  //TRACER_FORMAT("%s %s\r\n","#Software:",id_cliente);
	m_log->trace(buffer);
	
	buffer = "#Date: " + std::string(date) + std::string(" ") + time;
	m_log->trace(buffer);

	buffer = "#OS: " + System::getOperatingSystemId();
	m_log->trace(buffer);

	buffer = "#IE: " + System::getIEAgent() + " ;Version " + System::getIEVersion();
	m_log->trace(buffer);
}

void LiteLog::trace(const long severity,const std::string& logLine,bool setTime)
{
	if(severity & m_logLevel)
	{

		char date[100],time[100];
		_strtime(time);
		_strdate(date);

		std::string prepend = "";
		switch(severity)
		{
		case LOG_ERROR:
			prepend = "ERROR:";
			break;
		case LOG_TRACE:
			prepend = "TRACE:";
			break;
		case LOG_INFO:
			prepend = "INFO:";
			break;
		case LOG_WARNING:
			prepend = "WARNING:";
			break;
		case LOG_DB:
			prepend = "DB:";
			break;
		}

		std::string buffer;
		if(setTime)
			buffer = std::string(date) + std::string(" ") + time + " " + prepend + " " +logLine;
		else
			buffer = logLine;

		m_log->trace(buffer);
	}
}

void LiteLog::trace2(const long severity,const std::string& logLine)
{
	trace(severity,logLine,false);
}

void LiteLog::traceOff()
{
	char date[100],time[100];
	_strtime(time);
	_strdate(date);
	std::string buffer;
	buffer = "#End-Date: " + std::string(date) + std::string(" ") + time;
	m_log->trace(buffer);
	m_log->traceOff();
}

LiteLog* LiteLog::getInstance()
{
	if(m_instance.get() == 0)
	{
		m_instance = std::auto_ptr<LiteLog>(new LiteLog());
	}


	return m_instance.get();
}

long LiteLog::stringToId(const std::string& str)
{
	Tokenizer tok(str,"|");
	long value = 0;
	while(tok.HasMoreTokens())
	{
		bool negative = false;
		sstring mode = tok.NextToken();

		mode = mode.trim();
		mode = mode.toUpper();

		if(mode.startsWith("~"))
		{
			negative = true;
			mode = mode.replace("~","");
			mode = mode.trim();
		}

		long tempValue = 0;
		
		if(mode == "LOG_ALL")
		{
			tempValue = LOG_ALL;
		}
		if(mode == "LOG_NONE")
		{
			tempValue = LOG_NONE;
		}
		if(mode == "LOG_ERROR")
		{
			tempValue = LOG_ERROR;
		}
		if(mode == "LOG_WARNING")
		{
			tempValue = LOG_WARNING;
		}
		if(mode == "LOG_INFO")
		{
			tempValue = LOG_INFO;
		}
		if(mode == "LOG_TRACE")
		{
			tempValue = LOG_TRACE;
		}
		if(mode == "LOG_DB")
		{
			tempValue = LOG_DB;
		}
		
		if(tempValue == 0)
		{
			return LOG_NONE;
		}

		if(negative)
		{
			value = (value == 0)?0:~tempValue & value;
		}
		else
		{
			value = (value == 0)?tempValue:tempValue | value;
		}
	}

	if(value == 0)
	{
		return LOG_NONE;
	}

	return value;
}

} // namespace util

} // namespace stream