// Log.cpp: implementation of the Log class.
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

#include "Tokenizer.h"
#include "Date.h"
#include "stringUtil.h"
#include "LogFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace stream
{
/// namespace util
namespace util
{
	using namespace stream::net;
Log::Log()
{
	m_started = false;	
}

Log::~Log()
{
	traceOff();
}


	

void Log::traceOn(const std::string& fileName, const eOpenType& openType)
{
	m_threadControl.lock();

	if(!m_started)
	{
		m_output = LogFactory::getLog1(fileName);
			
		if(m_output.get())
		{

			m_output->traceOn(fileName,openType);

			m_started = true;	
		}
	}
	m_threadControl.unlock();
}

void Log::traceOff()
{
	m_threadControl.lock();
	if((m_started)&&(m_output.get()))
	{
		m_started = false;	
		m_output->traceOff();
	}
	m_threadControl.unlock();
}

void Log::trace(const std::string& logLine)
{
	m_threadControl.lock();
	
	if((m_started)&&(m_output.get()))
	{
		m_output->trace(logLine);
	}

	m_threadControl.unlock();
}

} // namespace util

} // namespace stream