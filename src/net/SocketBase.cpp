// SocketBase.cpp: implementation of the CSocketBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"


#include "SocketBase.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSocketBase::CSocketBase()
{
	WSADATA		wsd;
	WSAStartup(MAKEWORD(1,1),&wsd);
	m_socket = 0;
}

CSocketBase::CSocketBase(SOCKET sock)
{
	m_socket = sock;
}


CSocketBase::~CSocketBase()
{
	WSACleanup();
}


int CSocketBase::Send(const void* lpBuf, int nBufLen, int nFlags )
{
	return send(m_socket,(const char*)lpBuf,nBufLen,nFlags);	
}

int CSocketBase::Receive(void* lpBuf, int nBufLen, int nFlags )
{
	return recv(m_socket,(char*)lpBuf,nBufLen,nFlags);
	
}
BOOL CSocketBase::Create(UINT nSocketPort , int nSocketType, LPCTSTR lpszSocketAddress )
{
	m_socket = socket(AF_INET,nSocketType,0);


	
	struct hostent	   *hp_local = 0;
	struct sockaddr_in sock_bind;
	unsigned int		bind_addr;				// bind's addr

	sock_bind.sin_port = htons(nSocketPort);
	
	if ((bind_addr = inet_addr(lpszSocketAddress)) == INADDR_NONE)
	{
		hp_local = gethostbyname(lpszSocketAddress);
		if (hp_local)
			memcpy(&(sock_bind.sin_addr), hp_local->h_addr, hp_local->h_length);
	}
	else
	{
		sock_bind.sin_addr.s_addr = bind_addr;
	}


	if (hp_local)
		sock_bind.sin_family = hp_local->h_addrtype;
	else
		sock_bind.sin_family = AF_INET;


	int r = ::bind(m_socket,(struct sockaddr *)&sock_bind,sizeof(sockaddr_in));
	
	if(r != 0)
	{
		return false;
	}



	return true;
}

BOOL CSocketBase::Accept(CSocketBase& rConnectedSocket,	SOCKADDR* lpSockAddr , int* lpSockAddrLen )
{

	
	*lpSockAddrLen = sizeof (sockaddr);

	SOCKET ClientSock = ::accept(m_socket, 
                       (struct sockaddr *) lpSockAddr, 
                       (int *) lpSockAddrLen);


	if (ClientSock != INVALID_SOCKET) 
	{
		CSocketBase* c = new CSocketBase(ClientSock);
		rConnectedSocket = *c;
		return true;		
	}
    

	return false;
}
void CSocketBase::Close()
{
//	shutdown(m_socket,SD_BOTH);
	closesocket(m_socket);
	m_socket = 0;
}
BOOL CSocketBase::Connect(LPCTSTR lpszHostAddress, UINT nHostPort)
{
	struct hostent	   *hp = 0;
	unsigned int		addr;				// destination's addr
	

	struct sockaddr_in sock_in;

	sock_in.sin_family = AF_INET;	
	sock_in.sin_port = htons(nHostPort);
	memset(sock_in.sin_zero,0,sizeof(sock_in.sin_zero));

	if ((addr = inet_addr(lpszHostAddress)) == INADDR_NONE)
	{
		hp = gethostbyname(lpszHostAddress);
		if (hp)
			memcpy(&(sock_in.sin_addr), hp->h_addr, hp->h_length);
		
	}
	else
	{
		sock_in.sin_addr.s_addr = addr;
	}
	if (hp)
		sock_in.sin_family = hp->h_addrtype;
	else
		sock_in.sin_family = AF_INET;



	if(::connect(m_socket,(struct sockaddr *)&sock_in,sizeof(sockaddr_in)) != SOCKET_ERROR)
	{
		return true;
	}

	return false;
	
}
BOOL CSocketBase::Connect(const SOCKADDR* lpSockAddr, int nSockAddrLen)
{
	if(::connect(m_socket,(struct sockaddr *)lpSockAddr,nSockAddrLen) != SOCKET_ERROR)
	{
		return true;
	}

	return false;
}
BOOL CSocketBase::Listen(int nConnectionBacklog)
{
	

	if(::listen (m_socket,nConnectionBacklog) != SOCKET_ERROR)
	{
		return true;
	}

	return false;
}
