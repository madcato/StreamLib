
#include "stdafx.h"

#include "Exceptions.h"

#include "stringUtil.h"
#include "memory_stream.h"
#include "Blob.h"
#include "FileUtil.h"


namespace Stream
{
/**
	Group of exception classes used by the Stream classes
*/
namespace Exceptions
{



StreamException::StreamException(int id_code,std::string desc):exception(desc.c_str())
{
	m_err_code = id_code;
	m_desc = desc;
}


Win32ErrorException::Win32ErrorException(const std::string& file,long line)
{
	DWORD id_error = GetLastError();
	char message[1000];
	int length = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,0,id_error,0,message,1000,NULL);
	m_message = message;
	m_idError = id_error;
	m_file = file;
	m_line = line;

	m_finalMessage = "";
	m_finalMessage += "Win32 error. Code: ";
	m_finalMessage += stringUtil::toString(m_idError);
	m_finalMessage += " Description: ";
	m_finalMessage += m_message;
	m_finalMessage += " at ";
	m_finalMessage += FileUtil::ExtractFileNameFromPath(m_file);
	m_finalMessage += ":";
	m_finalMessage += stringUtil::toString(m_line);


	StreamException(id_error,m_finalMessage);
}

Win32ErrorException::~Win32ErrorException()
{

}

const char* Win32ErrorException::what() const
{

	return m_finalMessage.c_str();
}

} // namespace Exceptions
} // namespace Stream
