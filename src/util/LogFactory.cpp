// LogFactory.cpp: implementation of the LogFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Exceptions.h"
#include "CriticalSection.h"
#include "ILog.h"
#include "Log.h"
#include "IInputStream.h"
#include "IOutputStream.h"
#include "Socket.h"
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

LogFactory::LogFactory()
{

}

LogFactory::~LogFactory()
{

}


std::auto_ptr<ILogOutput> LogFactory::getLog1(const sstring& logName)
{
	sstring logName2 = logName;
	logName2.toUpper();
	
	size_t pos = 0;

	if((logName2 ^= "C:\\CON") || (logName2 ^= "CON"))
	{
#ifdef _DEBUG
		return std::auto_ptr<ILogOutput>(new ConsoleOutput);		
#endif // _DEBUG
	}
	else 
	{
		if((pos = logName2.find("SOCKET://")) != std::string::npos)
		{
#ifdef _DEBUG
			return std::auto_ptr<ILogOutput>(new SocketOutput);
#endif // _DEBUG
		}
		else
		{
			return std::auto_ptr<ILogOutput>(new FileOutput);
		}
	}

	return std::auto_ptr<ILogOutput>(new VoidOutput);
}


void LogFactory::FileOutput::traceOn(const std::string& fileName, const eOpenType& openType)
{
	

	int openFlag = 0;

	switch(openType)
	{
	case CONTINUE_LOG:
		openFlag = OPEN_ALWAYS;
		break;
	case CREATE_NEW_LOG:
		openFlag = CREATE_ALWAYS;
		break;
	default:
		openFlag = CREATE_ALWAYS;
		break;
	};
	
	
	m_fich = CreateFile(
				fileName.c_str(),                         // file name
				GENERIC_WRITE,                      // access mode
				FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE, // share mode
				NULL, // SD
				openFlag,                // how to create
				FILE_ATTRIBUTE_NORMAL, // | FILE_FLAG_WRITE_THROUGH,                 // file attributes
				NULL // handle to template file
				);

	//m_fich.open(filename,ios_base::app|ios_base::out);
	SetFilePointer(m_fich, 0, NULL, FILE_END);

}

void LogFactory::FileOutput::traceOff()
{
	FlushFileBuffers(m_fich);
	CloseHandle(m_fich);
}

void LogFactory::FileOutput::trace(const std::string& logLine)
{
	char buffer2[2000];
	_snprintf(buffer2,2000,"%s\r\n",logLine.c_str());
	DWORD wrote = 0;
	WriteFile(m_fich,buffer2,strlen(buffer2),&wrote,NULL);

}

#ifdef _DEBUG
void LogFactory::ConsoleOutput::traceOn(const std::string& fileName, const eOpenType& openType)
{
	
	std::vector<std::string> vec = ((sstring)fileName).split("|");
	AllocConsole();

	/*if(vec[1] != "")
	{
		SetConsoleTitle(vec[1].c_str());
	}

	SetConsoleOutputCP(1252); // Spanish: Spain
	
	if(vec[2] != "")
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),StringUtil::intValue(vec[2]));
	}*/
}

void LogFactory::ConsoleOutput::traceOff()
{
	FreeConsole();
}

void LogFactory::ConsoleOutput::trace(const std::string& logLine)
{
	std::string out = logLine + "\n";
	DWORD NumberOfCharsWritten = 0;
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE),
			out.c_str(),
			out.length(),
			&NumberOfCharsWritten,
			NULL);
}

void LogFactory::SocketOutput::traceOn(const std::string& fileName, const eOpenType& openType)
{

	std::vector<std::string> vec1 = ((sstring)fileName).split("//");

	if(vec1.size() < 2)
	{
		throw new exceptions::LogException(-1,"Invalid log socket format 1");
	}

	std::vector<std::string> vec2 = ((sstring)vec1[1]).split(":");

	if(vec2.size() == 2)
	{		
		m_socket = std::auto_ptr<net::Socket>(new net::Socket(vec2[0],vec2[1]));
	}
	else
	{
		throw new exceptions::LogException(-1,"Invalid log socket format 2");
	}

	m_output = m_socket->getOutputStream();
}

void LogFactory::SocketOutput::traceOff()
{
	m_socket->close();
}

void LogFactory::SocketOutput::trace(const std::string& logLine)
{
	std::string out = logLine + "\r\n";

	long size = out.length();
	
	m_output->write((unsigned char*)&size,sizeof(size));
	m_output->write((unsigned char*)out.c_str(),out.length());
}

#endif // _DEBUG

void LogFactory::VoidOutput::traceOn(const std::string& fileName, const eOpenType& openType)
{
}

void LogFactory::VoidOutput::traceOff()
{

}

void LogFactory::VoidOutput::trace(const std::string& logLine)
{
}



} // namespace util

} // namespace stream