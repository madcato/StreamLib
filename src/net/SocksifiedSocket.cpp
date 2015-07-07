


#include "stdafx.h"


#include "IOutputStream.h"	// Added by ClassView
#include "IInputStream.h"
#include "Exceptions.h"
#include "socket.h"
#include "Tokenizer.h"
#include "Date.h"
#include "StringUtil.h"
#include <memory>
#include "Base64Coder.h"
#include "Exceptions.h"

#include "SocksifiedSocket.h"

#include "CriticalSection.h"
#include "memory_stream.h"

/////////////////////////////////////////////////////////////////////////////
// SocksifiedSocket

namespace stream
{
/// namespace net
namespace net
{
using namespace util;
using namespace io;
SocksifiedSocket::SocksifiedSocket(const std::string& userAgent,std::auto_ptr<IProxyAuthData> authDataInterface):m_userAgent(userAgent),m_authDataInterface(authDataInterface)
{
	m_nProxyType = PROXYTYPE_NOPROXY;

	WSADATA		wsd;
	WSAStartup(MAKEWORD(2,2),&wsd);

	m_ProxyHost = "localhost";
	m_ProxyPort = "8080";
	m_ProxyUser = "";
	m_ProxyPass = "";
	m_host = "";
	m_port = ""; 
	m_authenticateFirst = false;
	m_bUseSocks5Logon = false;;

}

SocksifiedSocket::~SocksifiedSocket()
{
	WSACleanup();
}

bool SocksifiedSocket::connectTo(const std::string& lpszHostAddress, const std::string& nHostPort )
{

		

	m_host = lpszHostAddress;
	m_port = nHostPort;
	//Translate the host address


	SOCKADDR_IN sockAddr;
	memset(&sockAddr,0,sizeof(sockAddr));

	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr.s_addr = inet_addr(lpszHostAddress.c_str());

	if (sockAddr.sin_addr.s_addr == INADDR_NONE)
	{
		LPHOSTENT lphost;
		lphost = gethostbyname(lpszHostAddress.c_str());
		if (lphost != 0)
			sockAddr.sin_addr.s_addr = ((LPIN_ADDR)lphost->h_addr)->s_addr;
		else
		{
			WSASetLastError(WSAEINVAL);
			throw new exceptions::ProxyException(exceptions::PROXYERROR_NOCONN);
		}
	}

	sockAddr.sin_port = htons((u_short)StringUtil::intValue(nHostPort));

	return connect((SOCKADDR*)&sockAddr, sizeof(sockAddr));
	
}

bool SocksifiedSocket::connect( const SOCKADDR* lpSockAddr, int nSockAddrLen)
{
	
	
	//Connect to proxy server
	try
	{
		m_sock = std::auto_ptr<Socket>(new Socket(m_ProxyHost,m_ProxyPort));
	}catch(...)
	{
		throw new exceptions::ProxyException(exceptions::PROXYERROR_NOCONN);
	}
	

	LPSOCKADDR_IN sockAddr=(LPSOCKADDR_IN)lpSockAddr;

	//Save server details
	m_nProxyPeerIp=sockAddr->sin_addr.S_un.S_addr;
	m_nProxyPeerPort=sockAddr->sin_port;

	switch(m_nProxyType)
	{
	case PROXYTYPE_CONNECT:
		{

			std::string connect_str = constructConnectStr(m_authenticateFirst);
			
			try
			{
				m_sock->getOutputStream()->write((unsigned char*)connect_str.c_str(),connect_str.length());
			}catch(...)
			{
				throw new exceptions::ProxyException(exceptions::PROXYERROR_REQUESTFAILED);
			}
			//Get response
			std::string response_str = "";
			char buffer[100];

			int num = 0;
			try
			{
				int position = 0;
				do
				{
					num = m_sock->getInputStream()->read((unsigned char*)buffer,99);
					buffer[num] = '\0';
					response_str += buffer;
				}while((position = response_str.find("\r\n\r\n")) == std::string::npos);

				m_lastResponse = response_str.substr(position + 2);
				
				clearInput(m_sock->getInputStream());

			}
			catch(...)
			{
				throw new exceptions::ProxyException(exceptions::PROXYERROR_REQUESTFAILED);
			}
							
			// Check the first line of the response for the existence of a " 200 " code

			std::string response_status = response_str.substr(0,response_str.find("\r\n"));

			if(response_status.find(" 200 ") == std::string::npos)
			{
				if(response_status.find(" 407 ") == std::string::npos)
				{
					throw new exceptions::ProxyException(exceptions::PROXYERROR_REQUESTFAILED);
				}
				else
				{
					if(m_authDataInterface.get() != 0)
					{
						m_authDataInterface->GetAuthData(m_ProxyUser,m_ProxyPass);
					}

					if(m_ProxyUser == "")
					{
						throw new exceptions::ProxyException(exceptions::PROXYERROR_AUTHNOLOGON);
					}
					// Authentication required
					// Re-send query adding authentication params.
		
					connect_str = constructConnectStr(true);
					
					try
					{
						try
						{
							m_sock->getOutputStream()->write((unsigned char*)connect_str.c_str(),connect_str.length());
						}
						catch(...)
						{
							throw new exceptions::ProxyException(exceptions::PROXYERROR_REQUESTFAILED);
						}
						//Get response
						std::string response_str = "";
						char buffer[100];

						int num = 0;
						try
						{
							int position = 0;
							do
							{
								num = m_sock->getInputStream()->read((unsigned char*)buffer,99);
								buffer[num] = '\0';
								response_str += buffer;
							}while((position = response_str.find("\r\n\r\n")) == std::string::npos);

							m_lastResponse = response_str.substr(position + 2);

							clearInput(m_sock->getInputStream());

						}
						catch(...)
						{
							throw new exceptions::ProxyException(exceptions::PROXYERROR_REQUESTFAILED);
						}
						
						// Check the first line of the response for the existence of a " 200 " code

						std::string response_status = response_str.substr(0,response_str.find("\r\n"));

						if(response_status.find(" 200 ") == std::string::npos)
						{
							throw new exceptions::ProxyException(exceptions::PROXYERROR_AUTHFAILED);
						}
					}
					catch(...)
					{
							throw new exceptions::ProxyException(exceptions::PROXYERROR_AUTHFAILED);
					}
				}
			}
			
	
	
			break;
		}
	case PROXYTYPE_SOCKS4:
		{ //SOCKS4 proxy

			//Send request
			char command[9];
			memset(command,0,9);
			command[0]=4;
			command[1]=1;
			memcpy(&command[2],&sockAddr->sin_port,2);
			memcpy(&command[4],&sockAddr->sin_addr.S_un.S_addr,4);
			try
			{
				m_sock->getOutputStream()->write((unsigned char*)command,9);
				//Get response
				int num = m_sock->getInputStream()->read((unsigned char*)command,8);
				
				if (num!=8)
				{
					throw new exceptions::ProxyException(exceptions::PROXYERROR_REQUESTFAILED);
				}
			}
			catch(...)
			{
				throw new exceptions::ProxyException(exceptions::PROXYERROR_AUTHREQUIRED);
			}
			
			if (command[1]!=90)
			{
				throw new exceptions::ProxyException(exceptions::PROXYERROR_REQUESTFAILED);
			}
			break;
		}
	case PROXYTYPE_SOCKS5:
		{ //SOCKS5 proxy
			//Send initialization request
			unsigned char command[10];
			memset(command,0,10);
			command[0]=5;
			command[1]=m_bUseSocks5Logon?2:1;
			command[2]=m_bUseSocks5Logon?2:0;
			try
			{
				m_sock->getOutputStream()->write((unsigned char*)command,m_bUseSocks5Logon?4:3);
				//Get initialization response
				int num = m_sock->getInputStream()->read((unsigned char*)command,2);			
				if (num!=2)
				{
					throw new exceptions::ProxyException(exceptions::PROXYERROR_REQUESTFAILED);
				}
			}
			catch(...)
			{
				throw new exceptions::ProxyException(exceptions::PROXYERROR_REQUESTFAILED);
			}
			
			if (command[1]==0xFF)
			{
				throw new exceptions::ProxyException(exceptions::PROXYERROR_AUTHREQUIRED);
			}
			if (command[1])
			{
				if (command[1]!=2)
				{
					throw new exceptions::ProxyException(exceptions::PROXYERROR_AUTHTYPEUNKNOWN);
				}
				if (m_bUseSocks5Logon)
				{
					if(m_authDataInterface.get() != 0)
					{
						m_authDataInterface->GetAuthData(m_ProxyUser,m_ProxyPass);
					}

					//Send authentication
					auto_array_ptr<unsigned char> buffer(4+m_ProxyUser.length()+m_ProxyPass.length());
					sprintf((char *)buffer.get(),"  %s %s",m_ProxyUser.c_str(),m_ProxyPass.c_str());
					buffer[0]=5;
					buffer[1]=m_ProxyUser.length();
					buffer[2+m_ProxyUser.length()]=m_ProxyPass.length();
					try
					{					
						m_sock->getOutputStream()->write((unsigned char*)buffer.get(),3+m_ProxyUser.length()+m_ProxyPass.length());
						//Get auth response
						int num = m_sock->getInputStream()->read((unsigned char*)command,2);					
						if (num!=2)
						{
							throw new exceptions::ProxyException(exceptions::PROXYERROR_AUTHFAILED);
						}
					}
					catch(...)
					{
						throw new exceptions::ProxyException(exceptions::PROXYERROR_AUTHFAILED);
					}
					
					if (command[1]!=0x00)
					{
						throw new exceptions::ProxyException(exceptions::PROXYERROR_AUTHFAILED);
					}
				}
				else
				{
					throw new exceptions::ProxyException(exceptions::PROXYERROR_AUTHNOLOGON);
				}
			}
			
			//Send request
			memset(command,0,10);
			command[0]=5;
			command[1]=1;
			command[2]=0;
			command[3]=1;
			memcpy(&command[4],&sockAddr->sin_addr.S_un.S_addr,4);
			memcpy(&command[8],&sockAddr->sin_port,2);
			try
			{
				m_sock->getOutputStream()->write((unsigned char*)command,10);			
				//Get response
				int num = m_sock->getInputStream()->read((unsigned char*)command,10);			
				if (num!=10)
				{
					throw new exceptions::ProxyException(exceptions::PROXYERROR_REQUESTFAILED);
				}
			}
			catch(...)
			{
				throw new exceptions::ProxyException(exceptions::PROXYERROR_REQUESTFAILED);
			}
			
			if (command[1]!=0x00)
			{
				throw new exceptions::ProxyException(exceptions::PROXYERROR_REQUESTFAILED);
			}
			
		}
		break;
	};
	//It worked! SOCKS is really easy, isn't it?
	return TRUE;
}




/////////////////////////////////////////////////////////////////////////////
// Member-Funktion SocksifiedSocket 

void SocksifiedSocket::setProxy(EProxyType nProxyType,const std::string& ProxyHost,const std::string& ProxyPort,const std::string& ProxyUser,const std::string& ProxyPass, bool authenticateFirst, bool bUseSocks5Logon)
{
	m_nProxyType=nProxyType;

	m_ProxyHost=ProxyHost;
	m_ProxyPort=ProxyPort;
	m_ProxyUser=ProxyUser;
	m_ProxyPass=ProxyPass;
	m_authenticateFirst = authenticateFirst;
	m_bUseSocks5Logon=bUseSocks5Logon;
}


std::string SocksifiedSocket::constructConnectStr(bool include_auth_params)
{
	std::string connect_str;

	connect_str = "CONNECT ";
	connect_str += m_host;
	if(m_ProxyPort != "")
	{
		connect_str += ":";
		connect_str += m_port;
	}
	connect_str += " HTTP/1.1\r\n";



	if(m_userAgent != "")
	{
		connect_str += "User-Agent: " + m_userAgent + "\r\n";
	}

	connect_str += "Host: ";
	connect_str += m_host;
	if(m_ProxyPort != "")
	{
		connect_str += ":";
		connect_str += m_port;
	}
	connect_str += "\r\n";

	connect_str += "Content-Length: 0\r\n";

	connect_str += "Proxy-Connection: Keep-Alive\r\n";

	connect_str += "Pragma: no-cache\r\n";

	
	if(include_auth_params)
	{
		connect_str += "Proxy-authorization: Basic ";
		Base64Coder b64;
		b64.Encode((m_ProxyUser + ":" + m_ProxyPass).c_str());
		connect_str += b64.EncodedMessage();
		connect_str += "\r\n";	
	}
	connect_str += "\r\n";

	return connect_str;
}

void SocksifiedSocket::clearInput(IInputStream* input)
{
	char buffer[100];
	while(input->available())
	{
		int readed = input->read((unsigned char*)buffer,99);
		buffer[readed] = 0;
		m_lastResponse += buffer;
	}
}

SocketPtr SocksifiedSocket::releaseSocket()
{
	return m_sock;
}

std::string SocksifiedSocket::getLastResponse()
{
	return m_lastResponse;
}

} // namespace net

} //namespace stream

