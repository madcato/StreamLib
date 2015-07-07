// ServerSocket.cpp: implementation of the ServerSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "IInputstream.h"
#include "IOutputStream.h"
#include "Exceptions.h"
#include "Socket.h"
#include "ServerSocket.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define MAX_PENDING_CONNECTS 100

/// namespace stream
namespace stream
{
/// namespace net
namespace net
{

ServerSocket::ServerSocket(std::string port,std::string bind_ip,SockProto proto)throw(exceptions::SocketStreamException*)
{
	m_sock = 0;

	WSADATA		wsd;
	WSAStartup(MAKEWORD(1,1),&wsd);

	
	switch(proto)
	{
	case SP_TCP:
			m_socket_type = SOCK_STREAM;
			break;
	case SP_UDP:
			m_socket_type = SOCK_DGRAM;
			break;
	case SP_RAW:
			m_socket_type = SOCK_RAW;
			break;
	default:
			m_socket_type = SOCK_STREAM;
			break;
	}

	m_sock = socket(AF_INET,m_socket_type,0);
	if(m_sock != INVALID_SOCKET )
	{
		SOCKADDR_IN local_sin;              // Local socket address

                   
		local_sin.sin_port = htons (atol(port.c_str()));  


		if(bind_ip != "")
		{
			struct hostent	   *hp_local = 0;
			
			unsigned int		bind_addr;				// bind's addr
			if ((bind_addr = inet_addr(bind_ip.c_str())) == INADDR_NONE)
			{
				hp_local = gethostbyname(bind_ip.c_str());
				if (hp_local)
					memcpy(&(local_sin.sin_addr), hp_local->h_addr, hp_local->h_length);
				else
				{
					throw new exceptions::SocketStreamException();	
				}
			}
			else
				local_sin.sin_addr.s_addr = bind_addr;

			if (hp_local)
				local_sin.sin_family = hp_local->h_addrtype;
			else
				local_sin.sin_family = AF_INET;			

  		}
		else
		{
			// Associate the local address with WinSocket.
			local_sin.sin_family = AF_INET;		
			local_sin.sin_addr.s_addr = htonl (INADDR_ANY);
		}
	  


		if (bind (m_sock, 
				(struct sockaddr *) &local_sin, 
				sizeof (local_sin)) == SOCKET_ERROR) 
		{
			throw new exceptions::SocketStreamException();	
		}
		else
		{
			if(m_socket_type != SOCK_DGRAM)
			{			
				if (listen (m_sock, MAX_PENDING_CONNECTS) == SOCKET_ERROR)
				{
					throw new exceptions::SocketStreamException();	
				}
				else
				{

				}
			}
		}
	}
	else
	{
		throw new exceptions::SocketStreamException();	
	}
}

ServerSocket::~ServerSocket()
{
	if(m_sock)
	{
		closesocket(m_sock);

		m_sock = 0;
	}
	WSACleanup();
}

Socket* ServerSocket::accept(long seconds)throw(exceptions::SocketStreamException*)
{
	SOCKADDR_IN accept_sin;             // Receives the address of the client;
	
	int accept_sin_len;
	
	accept_sin_len = sizeof (accept_sin);

	if(m_socket_type != SOCK_DGRAM)
	{
		

		if(seconds != INFINITE)
		{
			timeval waitTime;
			waitTime.tv_sec = seconds;
			waitTime.tv_usec = 0;

			fd_set readFds;
			fd_set exceptFds;

			FD_ZERO(&readFds);
			FD_ZERO(&exceptFds);

			FD_SET(m_sock,&readFds);

			int retval = ::select(0,&readFds,0,&exceptFds,&waitTime);

			if(retval == 0)
			{
				// Time limit exceded
				return 0;
			}

			if(retval == SOCKET_ERROR)
			{
				throw new exceptions::SocketStreamException();	
			}
		}

	
		SOCKET ClientSock = ::accept (m_sock, 
						   (struct sockaddr *) &accept_sin, 
						   (int *) &accept_sin_len);


		if (ClientSock != INVALID_SOCKET) 
		{
			Socket* c = new Socket(ClientSock,m_socket_type);

			return c;
		}
		else
		{
			throw new exceptions::SocketStreamException();
		}
	}
	else
	{
		Socket* c = new Socket(m_sock,m_socket_type);

		return c;
	}

	return 0;
}

bool ServerSocket::isThereNewConnection(long seconds)
{
	timeval waitTime;
	
	waitTime.tv_sec = seconds;
	waitTime.tv_usec = 0;
	
	
	fd_set readFds;
	fd_set exceptFds;

	FD_ZERO(&readFds);
	FD_ZERO(&exceptFds);

	FD_SET(m_sock,&readFds);

	int retval = ::select(0,&readFds,0,&exceptFds,&waitTime);

	if(retval == 0)
	{
		// Time limit exceded
		return false;
	}

	if(retval == SOCKET_ERROR)
	{
		throw new exceptions::SocketStreamException();	
	}

	return true;
}

void ServerSocket::close()
{
	if(m_sock)
	{
		closesocket(m_sock);

		m_sock = 0;
	}

}

} // namespace net

} // namespace stream