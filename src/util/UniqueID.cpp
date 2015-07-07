// UniqueID.cpp: implementation of the UniqueID class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "UniqueID.h"

#include "Exceptions.h"
#include "Tokenizer.h"
#include "Date.h"
#include "StringUtil.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#ifdef WIN32
#define ENVSTRING "USERNAME"
#endif

namespace stream
{

/// namespace util
namespace util
{

int UniqueID::GenRandom()
{
	return(((basedata = basedata * 214013L + 2531011L) >> 16) & 0x7fff);
}
int UniqueID::basedata = 1;

int UniqueID::mult(char* cad)
{
	int len = strlen(cad);
	int resul = 1;
	for(int i = 0 ;i < len ; i++)
		resul *= cad[i];



	return resul;

}
unsigned long UniqueID::do_hash(char* cad)
{
	unsigned long _V = 0;

	int len = strlen(cad);
	for (int i = 0 ; i  < len ; i++)
	{
		_V = (_V << 8 | _V >> 24) + cad[i];
	}
	return _V; 
}

UniqueID::UniqueID()
{
	time_t m_time;
	int m_pid;
	char userName[255];
	char hostName[255];
	int ip = 3434;



	time(&(m_time));
	UniqueID::basedata += m_time;
	

	m_pid = _getpid();

	strcpy(userName,getenv(ENVSTRING));


	WSADATA wsaData;

	if(WSAStartup(MAKEWORD( 2, 2),&wsaData) == 0)
	{
		gethostname(hostName,255);	

		HOSTENT * host = gethostbyname(hostName);
		memcpy((void*)&ip, host->h_addr, 4);
	}
	else
	{
		strcpy(hostName,"ERROR_SOCKET");
	}

#ifdef WIN32
	MEMORYSTATUS lpBuffer;   // memory status structure
	GlobalMemoryStatus(&lpBuffer);
	int paso = (lpBuffer.dwAvailVirtual >> 8) * GenRandom() + GenRandom();	
#else
	int paso = GenRandom() * GenRandom();
#endif WIN32


	char* temp = uid;
	sprintf(temp,"%04.4x-",m_pid);
	temp += 5;
	sprintf(temp,"%08.8x-",m_time);
	temp += 9;	
	sprintf(temp,"%08.8x",do_hash(userName) + ip);
	temp += 8;
	sprintf(temp,"%08.8x-",do_hash(hostName) + ip);
	temp += 9;
	sprintf(temp,"%08.8x",paso);

	UniqueID::basedata++;
}

std::string UniqueID::GenRandomGUID(const std::string& separator)
{
	GUID guid;

	CoCreateGuid(&guid);

	std::string response = "";

	response += StringUtil::toString(guid.Data1);
	response += separator;
	response += StringUtil::toString(guid.Data2);
	response += separator;
	response += StringUtil::toString(guid.Data3);
	response += separator;
//	response += (char*)guid.Data4;

	return response;

}

} // namespace util

} // namespace stream
