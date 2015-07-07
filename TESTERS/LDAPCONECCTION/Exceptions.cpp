
#include "stdafx.h"
#include "Exceptions.h"


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


Win32ErrorException::Win32ErrorException()
{
	DWORD id_error = GetLastError();
	char message[1000];
	int length = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,0,id_error,0,message,1000,NULL);
	
	
	StreamException(id_error,message);
}

Win32ErrorException::~Win32ErrorException()
{

}

} // namespace Exceptions
} // namespace Stream
