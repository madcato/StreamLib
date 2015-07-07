// SocketBase.h: interface for the CSocketBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOCKETBASE_H__69F2AF13_0C1A_42D6_9A59_F760C606E29C__INCLUDED_)
#define AFX_SOCKETBASE_H__69F2AF13_0C1A_42D6_9A59_F760C606E29C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSocketBase  
{
public:
	CSocketBase();
	CSocketBase(SOCKET sock);
	virtual ~CSocketBase();

	int Send(const void* lpBuf, int nBufLen, int nFlags = 0);
	int Receive(void* lpBuf, int nBufLen, int nFlags = 0);
	BOOL Create(UINT nSocketPort = 0, int nSocketType=SOCK_STREAM, LPCTSTR lpszSocketAddress = 0);
	BOOL Accept(CSocketBase& rConnectedSocket,	SOCKADDR* lpSockAddr = 0, int* lpSockAddrLen = 0);
	void Close();
	BOOL Connect(LPCTSTR lpszHostAddress, UINT nHostPort);
	BOOL Connect(const SOCKADDR* lpSockAddr, int nSockAddrLen);
	BOOL Listen(int nConnectionBacklog=5);


private:
	
	SOCKET m_socket;


};

#endif // !defined(AFX_SOCKETBASE_H__69F2AF13_0C1A_42D6_9A59_F760C606E29C__INCLUDED_)
