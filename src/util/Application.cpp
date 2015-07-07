        // Application.cpp: implementation of the Application class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Exceptions.h"
#include "CriticalSection.h"
#include "memory_stream.h"
#include "Blob.h"
#include "FileUtil.h"
#include "System.h"
#include "ResourceManager.h"
#include "IInputStream.h"
#include "GZInputStream.h"
#include "IOutputStream.h"
#include "TarWriter.h"
#include "Tar.h"
#include "ILog.h"
#include "Socket.h"
#include "ServerSocket.h"
#include "Log.h"
#include "LiteLog.h"
#include "PropertyBag.h"
#include "Properties.h"
#include "DynamicClass.h"
#include "Thread.h"

#include "Application.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/// namespace stream
namespace stream
{

/// namespace util
namespace util
{


Application::SocketThread Application::m_appSocketThread;

Application::Application()
{

}

Application::~Application()
{

}

void Application::prepareResources(int idResource,const std::string& resourcePath)
{
	io::Blob<unsigned char> blob = util::ResourceManager::loadBinary(idResource);

	std::string gzFileName = FileUtil::getDatedFileName(System::getTempPath(),"tar.gz");
	FileUtil::Buffer2File(blob,gzFileName);
	stream::zip::GZInputStream gzinput(gzFileName);


	util::FileUtil::createDirectory(resourcePath,false);

	util::Tar tar;
	tar.RunExtract(&gzinput,resourcePath);


	util::FileUtil::deleteFile(gzFileName);
}

void Application::initTempLog(const std::string& logFileName,const std::string& module,int logLevel)
{
	std::string path = stream::util::System::getTempPath() + logFileName;

	stream::util::LiteLog::getInstance()->traceOn(path,FileUtil::ExtractFileNameFromPath(module) + " v" + stream::util::System::getFileVersion(module.c_str()),logLevel,CREATE_NEW_LOG);
}

void Application::initLog(const std::string& logPath,const std::string& module,int logLevel)
{
	stream::util::LiteLog::getInstance()->traceOn(logPath,FileUtil::ExtractFileNameFromPath(module) + " v" + stream::util::System::getFileVersion(module.c_str()),logLevel,CREATE_NEW_LOG);
}

void trans_func( unsigned int exceptionCode, EXCEPTION_POINTERS* exceptionInfo)
{
	std::string msgText;
	DWORD errorId = 0;


	// save the exception id number
	errorId = exceptionInfo->ExceptionRecord->ExceptionCode;
	
	switch(errorId)
		{
		case EXCEPTION_ACCESS_VIOLATION:
			msgText = "Access violation:";
			if (exceptionInfo->ExceptionRecord->ExceptionInformation[0] == 0)
				msgText += " Attempt to read from an invalid address.";
			else
				msgText += " Attempt to write to an invalid address.";
			break;

		case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
			msgText = "Attempt to access an array element that is out "
					  "of bounds\nand the underlying hardware supports "
					  "bounds checking.";
			break;

		case EXCEPTION_BREAKPOINT:
			msgText = "A breakpoint was encountered.";
			break;

		case EXCEPTION_DATATYPE_MISALIGNMENT:
			msgText = "The thread tried to read or write data that "
				      "is misaligned on hardware\nthat does not provide "
					  "alignment. For example, 16-bit values must be "
					  "aligned on\n2-byte boundaries; 32-bit values on "
					  "4-byte boundaries, and so on.";
			break;

		case EXCEPTION_FLT_DENORMAL_OPERAND:
			msgText = "One of the operands in a floating-point operation "
				      "is denormal. A denormal\nvalue is one that is too "
					  "small to represent as a standard floating-point "
					  "value.";
			break;

		case EXCEPTION_FLT_DIVIDE_BY_ZERO:
			msgText = "Attempt to divide a floating-point value by a "
				      "floating-point divisor of zero.";
			break;

		case EXCEPTION_FLT_INEXACT_RESULT:
			msgText = "The result of a floating-point operation cannot "
				      "be represented exactly as a decimal fraction.";
			break;

		case EXCEPTION_FLT_INVALID_OPERATION:
			msgText = "This exception represents any floating-point "
				      "exception not covered specific.";
			break;

		case EXCEPTION_FLT_OVERFLOW:
			msgText = "The exponent of a floating-point operation is "
				      "greater than the magnitude\nallowed by the "
					  "corresponding type.";
			break;

		case EXCEPTION_FLT_STACK_CHECK:
			msgText = "The stack overflowed or underflowed as the result "
				      "of\na floating-point operation.";
			break;

		case EXCEPTION_FLT_UNDERFLOW:
			msgText = "The exponent of a floating-point operation is less "
				      "than the\nmagnitude allowed by the corresponding type.";
			break;

		case EXCEPTION_ILLEGAL_INSTRUCTION:
			msgText = "Attempt to execute an invalid instruction.";
			break;

		case EXCEPTION_IN_PAGE_ERROR:
			msgText = "Attempt to access a page that was not present, "
				      "and the system was\nunable to load the page. For "
					  "example, this exception might occur if a\nnetwork "
					  "connection is lost while running a program over "
					  "the network.";
			break;

		case EXCEPTION_INT_DIVIDE_BY_ZERO:
			msgText = "The thread tried to divide an integer value by an "
				      "integer divisor of zero.";
			break;

		case EXCEPTION_INT_OVERFLOW:
			msgText = "The result of an integer operation caused a carry "
				      "out of the most\nsignificant bit of the result.";
			break;

		case EXCEPTION_INVALID_DISPOSITION:
			msgText = "An exception handler returned an invalid disposition "
				      "to the exception\ndispatcher. Programmers using a "
					  "high-level language such as C should\nnever encounter "
					  "this exception.";
			break;

		case EXCEPTION_NONCONTINUABLE_EXCEPTION:
			msgText = "The thread tried to continue execution after a "
				      "noncontinuable exception occurred.";
			break;

		case EXCEPTION_PRIV_INSTRUCTION:
			msgText = "The thread tried to execute an instruction whose "
				      "operation is not allowed\nin the current machine mode.";
			break;

		case EXCEPTION_SINGLE_STEP:
			msgText = "A trace trap or other single-instruction mechanism "
				      "signaled\nthat one instruction has been executed.";
			break;

		case EXCEPTION_STACK_OVERFLOW:
			msgText = "The thread used up its stack.";
			break;
		}

	throw exceptions::StreamException(exceptionCode,msgText);
}

void term_func()
{
}

void Application::init()
{
	// http://msdn.microsoft.com/library/default.asp?url=/library/en-us/vclib/html/_crt_exception_handling_routines.asp

	_set_se_translator(trans_func); // para convertir las excepciones de C en excepciones C++
	set_terminate(term_func); // para controlar cuando la aplicacion se cierra.
}

void Application::initSocketService(const std::string& listenPort, ref_count_ptr<DynamicClass> commandParser, const std::string& listenIP)
{
	init();

	m_appSocketThread.m_listenPort = listenPort;
	m_appSocketThread.m_listenIP = listenIP;

	m_appSocketThread.start();	
}

void Application::SocketThread::run()
{
	net::ServerSocket serverSock(m_listenPort,m_listenIP);

	CommandThread command(this);
	do
	{
		m_socket = std::auto_ptr<net::Socket>(serverSock.accept());
		command.start();
	}while(true);
}

void Application::CommandThread::run()
{
	do
	{


	}while(true);
}


} // namespace util

} // namespace stream
