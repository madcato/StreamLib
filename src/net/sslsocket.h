/********************************************************************************************
* MOD-NAME      : sslsocket.h
* LONG-NAME     : 
*
* AUTHOR        : Martin Ziacek (martin.ziacek@pobox.sk)
* DEPARTMENT    : 
* TELEPHONE     : 
* CREATION-DATE : 29/05/2001 15:27:01
* SP-NO         : 
* FUNCTION      : 
* 
*********************************************************************************************/
#if !defined(AFX_SSLSOCKET_H__CCE67526_C572_47F0_B3E9_79D2CE88D5F5__INCLUDED_)
#define AFX_SSLSOCKET_H__CCE67526_C572_47F0_B3E9_79D2CE88D5F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000





// sslsocket.h : header file
//


#define IO_BUFFER_SIZE  0x10000

#ifndef SEC_I_CONTEXT_EXPIRED
#define SEC_I_CONTEXT_EXPIRED            ((HRESULT)0x00090317L)
#endif
/////////////////////////////////////////////////////////////////////////////
// CSslSocket

class CSslSocket : public CSocketBase
{

// Attributes
public:

// Operations
public:
	CSslSocket();
	virtual ~CSslSocket();

	BOOL Create(UINT nSocketPort = 0, LPCTSTR lpszSocketAddress = 0,const TCHAR *szCertName = NULL, BOOL bMachineStore = FALSE, DWORD dwProtocol = 0);

	virtual BOOL Accept(CSslSocket & rConnectedSocket, SOCKADDR* lpSockAddr = 0, int* lpSockAddrLen = 0);

	virtual void Close();

	BOOL Connect(LPCTSTR lpszHostAddress, UINT nHostPort);
	BOOL Connect(const SOCKADDR* lpSockAddr, int nSockAddrLen);

	BOOL Listen(int nConnectionBacklog=5,BOOL bAuthClient = FALSE);

	DWORD GetLastError();

// Overrides
public:
	
	virtual int Send(const void* lpBuf, int nBufLen, int nFlags = 0);
	virtual int Receive(void* lpBuf, int nBufLen, int nFlags = 0);

// Implementation
protected:
	void SetLastError(DWORD dwErrCode);
	BOOL LoadSecurityLibrary(void);

	SECURITY_STATUS ClientCreateCredentials(const TCHAR *pszUserName, PCredHandle phCreds);
	BOOL ClientConnect(const TCHAR *szHostName);
	LONG ClientDisconnect(PCredHandle phCreds, CtxtHandle *phContext);
	SECURITY_STATUS ClientHandshakeLoop(PCredHandle phCreds, CtxtHandle *phContext, BOOL fDoInitialRead, SecBuffer *pExtraData);
	SECURITY_STATUS ClientHandshake(PCredHandle phCreds, const TCHAR *pszServerName, CtxtHandle *phContext, SecBuffer *pExtraData);
	DWORD ClientVerifyCertificate(PCCERT_CONTEXT pServerCert,const TCHAR *pszServerName,DWORD dwCertFlags);

	SECURITY_STATUS ServerCreateCredentials(const TCHAR *pszUserName, PCredHandle phCreds);
	BOOL ServerConnect(SOCKADDR* lpSockAddr, int* lpSockAddrLen);
	LONG ServerDisconect(PCredHandle phCreds, CtxtHandle *phContext);
	BOOL ServerHandshakeLoop(PCtxtHandle phContext, PCredHandle phCred, BOOL fClientAuth, BOOL fDoInitialRead, BOOL NewContext);
	DWORD ServerVerifyCertificate(PCCERT_CONTEXT  pServerCert, DWORD dwCertFlags);

	BOOL m_bServer;

	const char* m_CsCertName;
	BOOL m_bMachineStore;
	DWORD m_dwProtocol;

	PCCERT_CONTEXT  m_pCertContext;

	DWORD m_dwLastError;

	BOOL m_bAuthClient;

	HCERTSTORE      m_hMyCertStore;
	SCHANNEL_CRED   m_SchannelCred;
	CredHandle m_hCreds;
	CtxtHandle m_hContext;

	HMODULE m_hSecurity;
	SecurityFunctionTable m_SecurityFunc;

	BOOL m_bConInit;
	BOOL m_bAllowPlainText;

	BYTE *m_pbReceiveBuf;
	DWORD m_dwReceiveBuf;

	BYTE *m_pbIoBuffer;
	DWORD m_cbIoBuffer;

//	CEvent m_CeIO;
};

/////////////////////////////////////////////////////////////////////////////


#endif // !defined(AFX_SSLSOCKET_H__CCE67526_C572_47F0_B3E9_79D2CE88D5F5__INCLUDED_)

