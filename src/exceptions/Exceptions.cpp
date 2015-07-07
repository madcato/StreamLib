
#include "stdafx.h"

#include "Exceptions.h"

#include "Tokenizer.h"
#include "Date.h"
#include "StringUtil.h"
#include "CriticalSection.h"
#include "memory_stream.h"
#include "Blob.h"
#include "FileUtil.h"

namespace stream
{

using namespace util;

/**
	Group of exception classes used by the stream classes
*/
namespace exceptions
{



StreamException::StreamException(int id_code,std::string desc):exception(desc.c_str())
{
	m_err_code = id_code;
	m_desc = desc;
}

const char* StreamException::what() const
{
	return m_desc.c_str();
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
	m_finalMessage += StringUtil::toString(m_idError);
	m_finalMessage += " Description: ";
	m_finalMessage += m_message;
	m_finalMessage += "@";
	m_finalMessage += FileUtil::ExtractFileNameFromPath(m_file);
	m_finalMessage += "(";
	m_finalMessage += StringUtil::toString(m_line);
	m_finalMessage += ")";

	m_err_code = id_error;
	m_desc = m_finalMessage;
}

Win32ErrorException::~Win32ErrorException()
{

}

const char* Win32ErrorException::what() const
{

	return m_finalMessage.c_str();
}

} // namespace exceptions
} // namespace stream
