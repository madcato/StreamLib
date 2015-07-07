/********************************************************************************************
* MOD-NAME      : sslsocket.cpp
* LONG-NAME     : 
*
* AUTHOR        : Martin Ziacek (martin.ziacek@pobox.sk)
* DEPARTMENT    : 
* TELEPHONE     : 
* CREATION-DATE : 29/05/2001 15:27:36
* SP-NO         : 
* FUNCTION      : 
* 
*********************************************************************************************/

#include "stdafx.h"

#include "SocketBase.h"
#include "sslsocket.h"

/////////////////////////////////////////////////////////////////////////////
// CSslSocket

void CSslSocket::SetLastError(DWORD dwErrCode)				//this method and following macro will
{															//provide trace output of error description
	m_dwLastError = dwErrCode;								//with file name and line number where
	::SetLastError(dwErrCode);								//error occures - it works correctly
}															//only in this order

#ifdef _DEBUG
#define SetLastError(err) SetLastError(err)
#endif



CSslSocket::CSslSocket() :
	m_hMyCertStore(0),
	m_dwLastError(0),
	m_dwProtocol(0),
	m_bMachineStore(FALSE),
	m_hSecurity(0),
	m_bServer(FALSE),
	m_bAuthClient(FALSE),
	m_bConInit(FALSE),
	m_pbReceiveBuf(0),
	m_dwReceiveBuf(0),
	m_bAllowPlainText(FALSE),
	m_pbIoBuffer(0),
	m_cbIoBuffer(0),
	m_pCertContext(0)
{
	ZeroMemory(&m_SchannelCred,sizeof(m_SchannelCred));

	m_hCreds.dwLower = 0;
	m_hCreds.dwUpper = 0;

	m_hContext.dwLower = 0;
	m_hContext.dwUpper = 0;
}

CSslSocket::~CSslSocket()
{
    if ((m_hCreds.dwLower != 0) && (m_hCreds.dwUpper != 0)) {
		m_SecurityFunc.FreeCredentialHandle(&m_hCreds);
	}
	if ((m_hContext.dwLower != 0) && (m_hContext.dwUpper != 0)) {
		m_SecurityFunc.DeleteSecurityContext(&m_hContext);
	}
    if(m_pCertContext) CertFreeCertificateContext(m_pCertContext);
    if(m_hMyCertStore) CertCloseStore(m_hMyCertStore, 0);
	if (m_hSecurity) FreeLibrary(m_hSecurity);
	if (m_pbReceiveBuf) delete [] m_pbReceiveBuf;
	if (m_pbIoBuffer) delete [] m_pbIoBuffer;
}

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CSslSocket, CSocket)
	//{{AFX_MSG_MAP(CSslSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CSslSocket member functions

int CSslSocket::Send(const void* lpBuf, int nBufLen, int nFlags) 
{
	int rc = 0;
	SecPkgContext_StreamSizes Sizes;
	SECURITY_STATUS scRet;
	SecBufferDesc   Message;
	SecBuffer       Buffers[4];

	SecBuffer *     pDataBuffer;
	SecBuffer *     pExtraBuffer;

	PBYTE pbIoBuffer = 0;
	DWORD cbIoBufferLength;
	PBYTE pbMessage;
	DWORD cbMessage;

	DWORD dwAvaLn = 0;
	DWORD dwDataToSend = 0;
	DWORD dwSendInd = 0;
	DWORD dwCurrLn = 0;

	DWORD dwTotSent = 0;
	
	if (m_bConInit) {

		do {

			scRet = m_SecurityFunc.QueryContextAttributes(&m_hContext,SECPKG_ATTR_STREAM_SIZES,&Sizes);
			if(scRet != SEC_E_OK) {
				SetLastError(scRet);
				break;
			}

			cbIoBufferLength = Sizes.cbHeader + 
				Sizes.cbMaximumMessage +
				Sizes.cbTrailer;

			pbIoBuffer = new BYTE[cbIoBufferLength];
			if(pbIoBuffer == 0) {
				SetLastError(ERROR_OUTOFMEMORY);
				break;
			}

			pbMessage = pbIoBuffer + Sizes.cbHeader;
			dwAvaLn = Sizes.cbMaximumMessage;
			dwDataToSend = ((DWORD)nBufLen);

			do {
				ZeroMemory(pbIoBuffer,cbIoBufferLength);
				dwCurrLn = ((DWORD)nBufLen)-dwSendInd > dwAvaLn ? dwAvaLn : (((DWORD)nBufLen)-dwSendInd);

				CopyMemory(pbMessage,((BYTE*)lpBuf)+dwSendInd,dwCurrLn);

				//DUMP(_T("Plain text to send"),pbMessage,dwCurrLn);

				dwSendInd += dwCurrLn;
				dwDataToSend -= dwCurrLn;

				cbMessage = dwCurrLn;

				Buffers[0].pvBuffer     = pbIoBuffer;
				Buffers[0].cbBuffer     = Sizes.cbHeader;
				Buffers[0].BufferType   = SECBUFFER_STREAM_HEADER;

				Buffers[1].pvBuffer     = pbMessage;
				Buffers[1].cbBuffer     = cbMessage;
				Buffers[1].BufferType   = SECBUFFER_DATA;

				Buffers[2].pvBuffer     = pbMessage + cbMessage;
				Buffers[2].cbBuffer     = Sizes.cbTrailer;
				Buffers[2].BufferType   = SECBUFFER_STREAM_TRAILER;

				Buffers[3].BufferType   = SECBUFFER_EMPTY;

				Message.ulVersion       = SECBUFFER_VERSION;
				Message.cBuffers        = 4;
				Message.pBuffers        = Buffers;

				scRet = m_SecurityFunc.EncryptMessage(&m_hContext, 0, &Message, 0);

				if(FAILED(scRet)) {
					SetLastError(scRet);
					break;
				}

				pDataBuffer  = 0;
				pExtraBuffer = 0;
				for (int i = 1; i < 4; i++) {
					if (pDataBuffer == 0 && Buffers[i].BufferType == SECBUFFER_DATA) {
						pDataBuffer = &Buffers[i];
					}
					if (pExtraBuffer == 0 && Buffers[i].BufferType == SECBUFFER_EXTRA) {
						pExtraBuffer = &Buffers[i];
					}
				}

				//DUMP(_T("Cipher text to send"),pbIoBuffer,Buffers[0].cbBuffer + Buffers[1].cbBuffer + Buffers[2].cbBuffer);

				rc = CSocketBase::Send(pbIoBuffer, Buffers[0].cbBuffer + Buffers[1].cbBuffer + Buffers[2].cbBuffer, nFlags);

				if ((rc == SOCKET_ERROR) && (WSAGetLastError() == WSAEWOULDBLOCK)) {
					rc = nBufLen;
				} else {
					if (rc == SOCKET_ERROR) {
						SetLastError(WSAGetLastError());
						dwTotSent = rc;
						break;
					} else {
						dwTotSent += rc;
					}
				}

			} while (dwDataToSend != 0);

		} while (FALSE);

		if (pbIoBuffer) delete [] pbIoBuffer;
		
	} else {
		if (m_bAllowPlainText) {
			rc = CSocketBase::Send(lpBuf, nBufLen, nFlags);
			if ((rc == SOCKET_ERROR) && (GetLastError() == WSAEWOULDBLOCK)) {
				rc = nBufLen;
			}
			dwTotSent = rc;
		}
	}

	return dwTotSent > ((DWORD)nBufLen) ? nBufLen : dwTotSent;	
}

int CSslSocket::Receive(void* lpBuf, int nBufLen, int nFlags) 
{
	int rc = 0;
	SecPkgContext_StreamSizes Sizes;
	SECURITY_STATUS scRet;
	DWORD cbIoBufferLength;
	DWORD cbData;
	SecBufferDesc   Message;
	SecBuffer       Buffers[4];
    SecBuffer *     pDataBuffer;
    SecBuffer *     pExtraBuffer;
	SecBuffer       ExtraBuffer;

	BYTE *pDataBuf = 0;
	DWORD dwDataLn = 0;
	DWORD dwBufDataLn = 0;
	BOOL bCont = TRUE;

	if (m_bConInit) {
		if (m_dwReceiveBuf) {
			if ((DWORD)nBufLen < m_dwReceiveBuf) {
				rc = nBufLen;
				CopyMemory(lpBuf,m_pbReceiveBuf,rc);
				MoveMemory(m_pbReceiveBuf,m_pbReceiveBuf+rc,m_dwReceiveBuf-rc);
				m_dwReceiveBuf -= rc;
			} else {
				rc = m_dwReceiveBuf;
				CopyMemory(lpBuf,m_pbReceiveBuf,rc);
				delete [] m_pbReceiveBuf;
				m_pbReceiveBuf = 0;
				m_dwReceiveBuf = 0;
			}
		} else {

			do {
				scRet = m_SecurityFunc.QueryContextAttributes(&m_hContext,SECPKG_ATTR_STREAM_SIZES,&Sizes);
				if(scRet != SEC_E_OK) {
					SetLastError(scRet);
					break;
				}

				cbIoBufferLength = Sizes.cbHeader + 
					Sizes.cbMaximumMessage +
					Sizes.cbTrailer;

				if (!m_pbIoBuffer) m_pbIoBuffer = new BYTE[cbIoBufferLength];
				pDataBuf = new BYTE[cbIoBufferLength];
				dwBufDataLn = cbIoBufferLength;
				if ((m_pbIoBuffer == 0) || (pDataBuf == 0)) {
					SetLastError(ERROR_OUTOFMEMORY);
					break;
				}

				do {
					cbData = CSocketBase::Receive(m_pbIoBuffer + m_cbIoBuffer,cbIoBufferLength - m_cbIoBuffer);

					if(cbData == SOCKET_ERROR) {
						SetLastError(WSAGetLastError());
						break;
					} else if (cbData == 0) {
						if(m_cbIoBuffer) {
							//TRACE(_T("**** Server unexpectedly disconnected\n"));
							scRet = SEC_E_INTERNAL_ERROR;
							break;
						} else {
							break;
						}
					} else {
						m_cbIoBuffer += cbData;
					}
					//DUMP(_T("Received cipher text"),m_pbIoBuffer,cbData);

					Buffers[0].pvBuffer     = m_pbIoBuffer;
					Buffers[0].cbBuffer     = m_cbIoBuffer;
					Buffers[0].BufferType   = SECBUFFER_DATA;

					Buffers[1].BufferType   = SECBUFFER_EMPTY;
					Buffers[2].BufferType   = SECBUFFER_EMPTY;
					Buffers[3].BufferType   = SECBUFFER_EMPTY;

					Message.ulVersion       = SECBUFFER_VERSION;
					Message.cBuffers        = 4;
					Message.pBuffers        = Buffers;

					scRet = m_SecurityFunc.DecryptMessage(&m_hContext,&Message,0,0);

					if (scRet == SEC_E_INCOMPLETE_MESSAGE) {
						continue;
					}
					if (scRet == SEC_I_CONTEXT_EXPIRED) {
						SetLastError(scRet);
						break;
					}
					if (scRet != SEC_E_OK && scRet != SEC_I_RENEGOTIATE && scRet != SEC_I_CONTEXT_EXPIRED) {
						SetLastError(scRet);
						break;
					}

					pDataBuffer  = 0;
					pExtraBuffer = 0;
					for (int i = 1; i < 4; i++) {
						if (pDataBuffer == 0 && Buffers[i].BufferType == SECBUFFER_DATA) {
							pDataBuffer = &Buffers[i];
						}
						if (pExtraBuffer == 0 && Buffers[i].BufferType == SECBUFFER_EXTRA) {
							pExtraBuffer = &Buffers[i];
						}
					}

					if (pDataBuffer) {
						//DUMP(_T("Plain text received"),(BYTE *)(pDataBuffer->pvBuffer),pDataBuffer->cbBuffer);
						if ((dwDataLn + (pDataBuffer->cbBuffer)) > dwBufDataLn) {
							BYTE *bNewDataBuf = new BYTE[dwBufDataLn+(pDataBuffer->cbBuffer)];
							CopyMemory(bNewDataBuf,pDataBuf,dwDataLn);
							delete [] pDataBuf;
							pDataBuf = bNewDataBuf;
							dwBufDataLn = dwBufDataLn+(pDataBuffer->cbBuffer);
						}
						CopyMemory(pDataBuf+dwDataLn,pDataBuffer->pvBuffer,pDataBuffer->cbBuffer);
						dwDataLn += pDataBuffer->cbBuffer;
					}

					if (pExtraBuffer) {
						MoveMemory(m_pbIoBuffer, pExtraBuffer->pvBuffer, pExtraBuffer->cbBuffer);
						m_cbIoBuffer = pExtraBuffer->cbBuffer;
						continue;
					} else {
						m_cbIoBuffer = 0;
						bCont = FALSE;
					}

					if (scRet == SEC_I_RENEGOTIATE) {

						scRet = ClientHandshakeLoop(
                                        &m_hCreds, 
                                        &m_hContext, 
                                        FALSE, 
                                        &ExtraBuffer);
						if(scRet != SEC_E_OK) {
							break;
						}

						if(ExtraBuffer.pvBuffer) {
							MoveMemory(m_pbIoBuffer, ExtraBuffer.pvBuffer, ExtraBuffer.cbBuffer);
							m_cbIoBuffer = ExtraBuffer.cbBuffer;
						}

						if (ExtraBuffer.pvBuffer) delete [] ExtraBuffer.pvBuffer;
					}
				} while (bCont);

			} while (FALSE);

			if (dwDataLn) {

				if (dwDataLn > (DWORD)nBufLen) {

					m_dwReceiveBuf = dwDataLn - ((DWORD)(nBufLen));
					m_pbReceiveBuf = new BYTE[m_dwReceiveBuf];

					CopyMemory(lpBuf,pDataBuf,nBufLen);
					rc = nBufLen;

					CopyMemory(m_pbReceiveBuf,pDataBuf+nBufLen,m_dwReceiveBuf);

				} else {
					CopyMemory(lpBuf,pDataBuf,dwDataLn);
					rc = dwDataLn;
				}
			}

			if (pDataBuf) delete [] pDataBuf;
		}
	} else {
		if (m_bAllowPlainText) rc = CSocketBase::Receive(lpBuf, nBufLen, nFlags);
	}

	return rc;
}

BOOL CSslSocket::Create(UINT nSocketPort/* = 0*/, LPCTSTR lpszSocketAddress/* = 0*/, const TCHAR *szCertName/* = NULL*/, BOOL bMachineStore/* = FALSE*/, DWORD dwProtocol/* = 0*/)
{
	BOOL rc = FALSE;
		
	rc = CSocketBase::Create(nSocketPort,SOCK_STREAM,lpszSocketAddress);

	if (rc) {
		if (LoadSecurityLibrary()) {
			m_CsCertName = szCertName;
			m_bMachineStore = bMachineStore;
			m_dwProtocol = dwProtocol;
		} else {
			rc = FALSE;
		}
	} else {
		SetLastError(WSAGetLastError());
	}

	return rc;
}

BOOL CSslSocket::Accept(CSslSocket & rConnectedSocket, SOCKADDR* lpSockAddr/* = 0*/, int* lpSockAddrLen/* = NULL*/)
{
	BOOL rc = FALSE;
	
	rc = CSocketBase::Accept(rConnectedSocket,lpSockAddr,lpSockAddrLen);

	if (rc) {
		rConnectedSocket.m_bAuthClient = m_bAuthClient;
		rConnectedSocket.m_CsCertName = m_CsCertName;
		rConnectedSocket.m_dwProtocol = m_dwProtocol;
		rConnectedSocket.m_bMachineStore = m_bMachineStore;

		rConnectedSocket.LoadSecurityLibrary();
		rConnectedSocket.ServerCreateCredentials(LPCTSTR(m_CsCertName),&(rConnectedSocket.m_hCreds));
		rc = rConnectedSocket.ServerConnect(lpSockAddr,lpSockAddrLen);
		rConnectedSocket.m_bConInit = rc;
	}

	return rc;
}

void CSslSocket::Close()
{
	if (m_bServer) {
		ServerDisconect(&m_hCreds,&m_hContext);
	} else {
		ClientDisconnect(&m_hCreds,&m_hContext);
	}
	CSocketBase::Close();
}

BOOL CSslSocket::Connect(LPCTSTR lpszHostAddress, UINT nHostPort)
{
	if (CSocketBase::Connect(lpszHostAddress,nHostPort)) {
		m_bConInit = ClientConnect(lpszHostAddress);
		return m_bConInit;
	} else {
		return FALSE;
	}
}

BOOL CSslSocket::Connect(const SOCKADDR* lpSockAddr, int nSockAddrLen)
{
	if (CSocketBase::Connect(lpSockAddr,nSockAddrLen)) {

		HOSTENT *pHostEnt = gethostbyaddr((const char *)lpSockAddr,nSockAddrLen,AF_INET);

#ifdef _UNICODE
		DWORD dwServerName = MultiByteToWideChar(CP_ACP, 0, pHostEnt->h_name, -1, 0, 0);
		WCHAR *wszServerName = new WCHAR[dwServerName];
		MultiByteToWideChar(CP_ACP, 0, pHostEnt->h_name, -1, wszServerName, dwServerName);
		m_bConInit = ClientConnect(wszServerName);
		delete [] wszServerName;
#else
		m_bConInit = ClientConnect(pHostEnt->h_name);
#endif
		return m_bConInit;
	} else {
		return FALSE;
	}
}

BOOL CSslSocket::Listen(int nConnectionBacklog/* = 5*/,BOOL bAuthClient/* = FALSE*/)
{
	m_bAuthClient = bAuthClient;
	m_bServer = TRUE;

	if ((m_hCreds.dwLower == 0) && (m_hCreds.dwUpper == 0)) {
		if (ServerCreateCredentials(LPCTSTR(m_CsCertName),&m_hCreds) == 0) {
			return CSocketBase::Listen(nConnectionBacklog);
		} else {
			return FALSE;
		}
	} else {
		return CSocketBase::Listen(nConnectionBacklog);
	}
}

DWORD CSslSocket::GetLastError()
{
	return m_dwLastError;
}

BOOL CSslSocket::LoadSecurityLibrary(void)
{
	BOOL rc = FALSE;

	PSecurityFunctionTable  pSecurityFunc;
	INIT_SECURITY_INTERFACE pInitSecurityInterface;

	do {
		m_hSecurity = LoadLibrary(_T("SCHANNEL.DLL"));
		if(m_hSecurity == 0) {
			SetLastError(::GetLastError());
			break;
		}

#ifdef _UNICODE
		pInitSecurityInterface = (INIT_SECURITY_INTERFACE)GetProcAddress(m_hSecurity,"InitSecurityInterfaceW");
#else
		pInitSecurityInterface = (INIT_SECURITY_INTERFACE)GetProcAddress(m_hSecurity,"InitSecurityInterfaceA");
#endif
    
		if(pInitSecurityInterface == 0) {
			SetLastError(::GetLastError());
			break;
		}

		pSecurityFunc = pInitSecurityInterface();

		if(pSecurityFunc == 0) {
			SetLastError(::GetLastError());
			break;
		}

		CopyMemory(&m_SecurityFunc, pSecurityFunc, sizeof(m_SecurityFunc));

		rc = TRUE;

	} while (FALSE);

    return rc;
}

SECURITY_STATUS CSslSocket::ClientCreateCredentials(const TCHAR *pszUserName, PCredHandle phCreds)
{
	TimeStamp       tsExpiry;
	SECURITY_STATUS Status;
	CERT_RDN cert_rdn;
	CERT_RDN_ATTR cert_rdn_attr;

	do {
		if(m_hMyCertStore == 0) {
			m_hMyCertStore = CertOpenSystemStore(0,_T("MY"));
			if(!m_hMyCertStore) {
				SetLastError(::GetLastError());
				Status = SEC_E_NO_CREDENTIALS;
				break;
			}
		}

		if(pszUserName && _tcslen(pszUserName) != 0) {

			cert_rdn.cRDNAttr = 1;
			cert_rdn.rgRDNAttr = &cert_rdn_attr;

			cert_rdn_attr.pszObjId = szOID_COMMON_NAME;
			cert_rdn_attr.dwValueType = CERT_RDN_ANY_TYPE;
			cert_rdn_attr.Value.cbData = _tcslen(pszUserName);

#ifdef _UNICODE
			char *pszUn = new char[wcslen(pszUserName)+1];
			WideCharToMultiByte(CP_ACP,0,pszUserName,-1,pszUn,wcslen(pszUserName)+1,0,0);
			cert_rdn_attr.Value.pbData = (BYTE *)pszUn;
#else
			cert_rdn_attr.Value.pbData = (BYTE *)pszUserName;
#endif			
			m_pCertContext = CertFindCertificateInStore(m_hMyCertStore, 
													  X509_ASN_ENCODING, 
													  0,
													  CERT_FIND_SUBJECT_ATTR,
													  &cert_rdn,
													  0);

#ifdef _UNICODE
			delete [] pszUn;
#endif
			if(m_pCertContext == 0) {
				SetLastError(::GetLastError());
				Status = SEC_E_NO_CREDENTIALS;
				break;
			}
		}

		ZeroMemory(&m_SchannelCred, sizeof(m_SchannelCred));

		m_SchannelCred.dwVersion  = SCHANNEL_CRED_VERSION;

		if(m_pCertContext) {
			m_SchannelCred.cCreds     = 1;
			m_SchannelCred.paCred     = &m_pCertContext;
		}

		m_SchannelCred.grbitEnabledProtocols = m_dwProtocol;

		m_SchannelCred.dwFlags |= SCH_CRED_NO_DEFAULT_CREDS;
		m_SchannelCred.dwFlags |= SCH_CRED_NO_DEFAULT_CREDS | SCH_CRED_NO_SYSTEM_MAPPER | CRYPT_E_NO_REVOCATION_CHECK;

		Status = m_SecurityFunc.AcquireCredentialsHandle(
							0,
							UNISP_NAME,
							SECPKG_CRED_OUTBOUND,
							0,
							&m_SchannelCred,
							0,
							0,
							phCreds,
							&tsExpiry);

		if(Status != SEC_E_OK) {
			SetLastError(::GetLastError());
			Status = Status;
			break;
		}

	} while (FALSE);

	return Status;
}

SECURITY_STATUS CSslSocket::ServerCreateCredentials(const TCHAR * pszUserName, PCredHandle phCreds)
{
	TimeStamp       tsExpiry;
	SECURITY_STATUS Status;
	CERT_RDN cert_rdn;
	CERT_RDN_ATTR cert_rdn_attr;

	do {

		if(pszUserName == 0 || _tcslen(pszUserName) == 0) {
			SetLastError(ERROR_NO_SUCH_USER);
			Status = SEC_E_NO_CREDENTIALS;
			break;
		}

		if(m_hMyCertStore == 0) {
			if(m_bMachineStore) {
				m_hMyCertStore = CertOpenStore(CERT_STORE_PROV_SYSTEM,
											 X509_ASN_ENCODING,
											 0,
											 CERT_SYSTEM_STORE_LOCAL_MACHINE,
											 L"MY");
			} else {
				m_hMyCertStore = CertOpenSystemStore(0,_T("MY"));
			}

			if(!m_hMyCertStore) {
				SetLastError(::GetLastError());
				Status = SEC_E_NO_CREDENTIALS;
				break;
			}
		}

		cert_rdn.cRDNAttr = 1;
		cert_rdn.rgRDNAttr = &cert_rdn_attr;

		cert_rdn_attr.pszObjId = szOID_COMMON_NAME;
		cert_rdn_attr.dwValueType = CERT_RDN_ANY_TYPE;
		cert_rdn_attr.Value.cbData = _tcslen(pszUserName);

#ifdef _UNICODE
			char *pszUn = new char[wcslen(pszUserName)+1];
			WideCharToMultiByte(CP_ACP,0,pszUserName,-1,pszUn,wcslen(pszUserName)+1,0,0);
			cert_rdn_attr.Value.pbData = (BYTE *)pszUn;
#else
			cert_rdn_attr.Value.pbData = (BYTE *)pszUserName;
#endif			
			m_pCertContext = CertFindCertificateInStore(m_hMyCertStore, 
													  X509_ASN_ENCODING, 
													  0,
													  CERT_FIND_SUBJECT_ATTR,
													  &cert_rdn,
													  0);

#ifdef _UNICODE
			delete [] pszUn;
#endif

		if(m_pCertContext == 0) {
			SetLastError(::GetLastError());
			Status = SEC_E_NO_CREDENTIALS;
			break;
		}

		ZeroMemory(&m_SchannelCred, sizeof(m_SchannelCred));

		m_SchannelCred.dwVersion = SCHANNEL_CRED_VERSION;

		m_SchannelCred.cCreds = 1;
		m_SchannelCred.paCred = &m_pCertContext;
		m_SchannelCred.hRootStore = m_hMyCertStore;
		m_SchannelCred.dwMinimumCipherStrength = 80;
		m_SchannelCred.grbitEnabledProtocols = m_dwProtocol;
		m_SchannelCred.dwFlags |= SCH_CRED_NO_DEFAULT_CREDS | SCH_CRED_NO_SYSTEM_MAPPER | CRYPT_E_NO_REVOCATION_CHECK;
		
		Status = m_SecurityFunc.AcquireCredentialsHandle(
							0,
							UNISP_NAME,
							SECPKG_CRED_INBOUND,
							0,
							&m_SchannelCred,
							0,
							0,
							phCreds,
							&tsExpiry);

		if(Status != SEC_E_OK) {
			SetLastError(Status);
			Status = Status;
			break;
		}

	} while (FALSE);

    return Status;
}

BOOL CSslSocket::ClientConnect(const TCHAR *szHostName)
{
	BOOL rc = FALSE;
	SecBuffer  ExtraData;
	SECURITY_STATUS Status;
	PCCERT_CONTEXT pRemoteCertContext = 0;

	memset(&ExtraData,0,sizeof(SecBuffer));
	do {
		if(ClientCreateCredentials(LPCTSTR(m_CsCertName), &m_hCreds)) {
			break;
		}

		if(ClientHandshake(&m_hCreds,szHostName,&m_hContext,&ExtraData)) {
			break;
		}

		Status = m_SecurityFunc.QueryContextAttributes(&m_hContext,SECPKG_ATTR_REMOTE_CERT_CONTEXT,(PVOID)&pRemoteCertContext);
		if(Status != SEC_E_OK) {
			SetLastError(Status);
			break;
		}

		Status = ClientVerifyCertificate(pRemoteCertContext, szHostName, 0);
		if(Status) {
			SetLastError(Status);
			break;
		}

		CertFreeCertificateContext(pRemoteCertContext);	//pRemoteCertContext

		rc = TRUE;
	} while (FALSE);

	return rc;
}

SECURITY_STATUS CSslSocket::ClientHandshake(PCredHandle phCreds, const TCHAR *pszServerName, CtxtHandle *phContext, SecBuffer *pExtraData)
{
    SecBufferDesc   OutBuffer;
    SecBuffer       OutBuffers[1];
    DWORD           dwSSPIFlags;
    DWORD           dwSSPIOutFlags;
    TimeStamp       tsExpiry;
    SECURITY_STATUS scRet;
    DWORD           cbData;

    dwSSPIFlags = ISC_REQ_SEQUENCE_DETECT   |
                  ISC_REQ_REPLAY_DETECT     |
                  ISC_REQ_CONFIDENTIALITY   |
                  ISC_RET_EXTENDED_ERROR    |
                  ISC_REQ_ALLOCATE_MEMORY   |
                  ISC_REQ_STREAM;

    OutBuffers[0].pvBuffer   = 0;
    OutBuffers[0].BufferType = SECBUFFER_TOKEN;
    OutBuffers[0].cbBuffer   = 0;

    OutBuffer.cBuffers = 1;
    OutBuffer.pBuffers = OutBuffers;
    OutBuffer.ulVersion = SECBUFFER_VERSION;

    scRet = m_SecurityFunc.InitializeSecurityContext(
                    phCreds,
                    0,
                    (TCHAR*)pszServerName,
                    dwSSPIFlags,
                    0,
                    SECURITY_NATIVE_DREP,
                    0,
                    0,
                    phContext,
                    &OutBuffer,
                    &dwSSPIOutFlags,
                    &tsExpiry);

    if (scRet != SEC_I_CONTINUE_NEEDED) {
        SetLastError(scRet);
        return scRet;
    }

    if (OutBuffers[0].cbBuffer != 0 && OutBuffers[0].pvBuffer != 0) {
		m_bAllowPlainText = TRUE;
		cbData = Send(OutBuffers[0].pvBuffer,OutBuffers[0].cbBuffer);
		m_bAllowPlainText = FALSE;

        if (cbData == SOCKET_ERROR || cbData == 0) {
            SetLastError(WSAGetLastError());
            m_SecurityFunc.FreeContextBuffer(OutBuffers[0].pvBuffer);
            m_SecurityFunc.DeleteSecurityContext(phContext);
            return SEC_E_INTERNAL_ERROR;
        }

        m_SecurityFunc.FreeContextBuffer(OutBuffers[0].pvBuffer);
        OutBuffers[0].pvBuffer = 0;
    }

    SECURITY_STATUS rc = ClientHandshakeLoop(phCreds, phContext, TRUE, pExtraData);

	if (pExtraData->pvBuffer) delete [] pExtraData->pvBuffer;

	return rc;
}

SECURITY_STATUS CSslSocket::ClientHandshakeLoop(PCredHandle phCreds, CtxtHandle *phContext, BOOL fDoInitialRead, SecBuffer *pExtraData)
{
    SecBufferDesc   InBuffer;
    SecBuffer       InBuffers[2];
    SecBufferDesc   OutBuffer;
    SecBuffer       OutBuffers[1];
    DWORD           dwSSPIFlags;
    DWORD           dwSSPIOutFlags;
    TimeStamp       tsExpiry;
    SECURITY_STATUS scRet;
    DWORD           cbData;

    PUCHAR          IoBuffer;
    DWORD           cbIoBuffer;
    BOOL            fDoRead;


    dwSSPIFlags = ISC_REQ_SEQUENCE_DETECT   |
                  ISC_REQ_REPLAY_DETECT     |
                  ISC_REQ_CONFIDENTIALITY   |
                  ISC_RET_EXTENDED_ERROR    |
                  ISC_REQ_ALLOCATE_MEMORY   |
                  ISC_REQ_STREAM;

    IoBuffer = new BYTE[IO_BUFFER_SIZE];
    if (IoBuffer == 0) {
		SetLastError(ERROR_OUTOFMEMORY);
        return SEC_E_INTERNAL_ERROR;
    }
    cbIoBuffer = 0;

    fDoRead = fDoInitialRead;

    scRet = SEC_I_CONTINUE_NEEDED;

    while(scRet == SEC_I_CONTINUE_NEEDED        ||
          scRet == SEC_E_INCOMPLETE_MESSAGE     ||
          scRet == SEC_I_INCOMPLETE_CREDENTIALS) {

        if(0 == cbIoBuffer || scRet == SEC_E_INCOMPLETE_MESSAGE) {
            if(fDoRead) {
					m_bAllowPlainText = TRUE;
					cbData = Receive((char *)(IoBuffer + cbIoBuffer),IO_BUFFER_SIZE - cbIoBuffer);
					m_bAllowPlainText = FALSE;

                if (cbData == SOCKET_ERROR) {
					SetLastError(WSAGetLastError());
					scRet = SEC_E_INTERNAL_ERROR;
					break;
                } else if(cbData == 0) {
                    SetLastError(ERROR_VC_DISCONNECTED);
                    scRet = SEC_E_INTERNAL_ERROR;
                    break;
                }

                cbIoBuffer += cbData;
            } else {
                fDoRead = TRUE;
            }
        }

        InBuffers[0].pvBuffer   = IoBuffer;
        InBuffers[0].cbBuffer   = cbIoBuffer;
        InBuffers[0].BufferType = SECBUFFER_TOKEN;

        InBuffers[1].pvBuffer   = 0;
        InBuffers[1].cbBuffer   = 0;
        InBuffers[1].BufferType = SECBUFFER_EMPTY;

        InBuffer.cBuffers       = 2;
        InBuffer.pBuffers       = InBuffers;
        InBuffer.ulVersion      = SECBUFFER_VERSION;

        OutBuffers[0].pvBuffer  = 0;
        OutBuffers[0].BufferType= SECBUFFER_TOKEN;
        OutBuffers[0].cbBuffer  = 0;

        OutBuffer.cBuffers      = 1;
        OutBuffer.pBuffers      = OutBuffers;
        OutBuffer.ulVersion     = SECBUFFER_VERSION;

        scRet = m_SecurityFunc.InitializeSecurityContext(phCreds,
                                          phContext,
                                          0,
                                          dwSSPIFlags,
                                          0,
                                          SECURITY_NATIVE_DREP,
                                          &InBuffer,
                                          0,
                                          0,
                                          &OutBuffer,
                                          &dwSSPIOutFlags,
                                          &tsExpiry);

        if(scRet == SEC_E_OK                ||
           scRet == SEC_I_CONTINUE_NEEDED   ||
           FAILED(scRet) && (dwSSPIOutFlags & ISC_RET_EXTENDED_ERROR)) {

            if(OutBuffers[0].cbBuffer != 0 && OutBuffers[0].pvBuffer != 0) {
					m_bAllowPlainText = TRUE;
					cbData = Send((const char *)(OutBuffers[0].pvBuffer),OutBuffers[0].cbBuffer);
					m_bAllowPlainText = FALSE;

                if(cbData == SOCKET_ERROR || cbData == 0) {
                    SetLastError(WSAGetLastError());
                    m_SecurityFunc.FreeContextBuffer(OutBuffers[0].pvBuffer);
                    m_SecurityFunc.DeleteSecurityContext(phContext);
                    return SEC_E_INTERNAL_ERROR;
                }

                m_SecurityFunc.FreeContextBuffer(OutBuffers[0].pvBuffer);
                OutBuffers[0].pvBuffer = 0;
            }
        }

        if(scRet == SEC_E_INCOMPLETE_MESSAGE) {
            continue;
        }

        if(scRet == SEC_E_OK) {

            if(InBuffers[1].BufferType == SECBUFFER_EXTRA) {

                pExtraData->pvBuffer = new BYTE[InBuffers[1].cbBuffer];

                if(pExtraData->pvBuffer == 0) {
                    SetLastError(ERROR_OUTOFMEMORY);
                    return SEC_E_INTERNAL_ERROR;
                }

                MoveMemory(pExtraData->pvBuffer,
                           IoBuffer + (cbIoBuffer - InBuffers[1].cbBuffer),
                           InBuffers[1].cbBuffer);

                pExtraData->cbBuffer   = InBuffers[1].cbBuffer;
                pExtraData->BufferType = SECBUFFER_TOKEN;
            } else {
                pExtraData->pvBuffer   = 0;
                pExtraData->cbBuffer   = 0;
                pExtraData->BufferType = SECBUFFER_EMPTY;
            }

            break;
        }

        if(FAILED(scRet)) {
            SetLastError(scRet);
            break;
        }

        if(scRet == SEC_I_INCOMPLETE_CREDENTIALS) {
			SetLastError(scRet);
			break;
        }

        if ( InBuffers[1].BufferType == SECBUFFER_EXTRA ) {
            MoveMemory(IoBuffer,
                       IoBuffer + (cbIoBuffer - InBuffers[1].cbBuffer),
                       InBuffers[1].cbBuffer);

            cbIoBuffer = InBuffers[1].cbBuffer;
        } else {
            cbIoBuffer = 0;
        }
    }

    if(FAILED(scRet)) {
        m_SecurityFunc.DeleteSecurityContext(phContext);
    }

	if (IoBuffer) delete [] IoBuffer;

    return scRet;
}

DWORD CSslSocket::ClientVerifyCertificate(PCCERT_CONTEXT pServerCert,const TCHAR *pszServerName,DWORD dwCertFlags)
{
    HTTPSPolicyCallbackData		polHttps;
    CERT_CHAIN_POLICY_PARA		PolicyPara;
    CERT_CHAIN_POLICY_STATUS	PolicyStatus;
    CERT_CHAIN_PARA				ChainPara;
    PCCERT_CHAIN_CONTEXT		pChainContext = 0;

    DWORD   Status;
    PWSTR   pwszServerName = 0;
#ifndef _UNICODE
    DWORD   cchServerName;
#endif

	do {
		if(pServerCert == 0) {
			Status = SEC_E_WRONG_PRINCIPAL;
			SetLastError(Status);
			break;
		}
		int iRc = CertVerifyTimeValidity(0,pServerCert->pCertInfo);
		if (iRc != 0) {
			Status = SEC_E_CERT_EXPIRED;
			SetLastError(Status);
			break;
		}

#ifndef _UNICODE
		if (pszServerName == 0 || strlen(pszServerName) == 0) {
			return SEC_E_WRONG_PRINCIPAL;
		}

		cchServerName = MultiByteToWideChar(CP_ACP, 0, pszServerName, -1, 0, 0);
		pwszServerName = new WCHAR[cchServerName];
		if (pwszServerName == 0) {
			return SEC_E_INSUFFICIENT_MEMORY;
		}
		cchServerName = MultiByteToWideChar(CP_ACP, 0, pszServerName, -1, pwszServerName, cchServerName);
		if (cchServerName == 0) {
			return SEC_E_WRONG_PRINCIPAL;
		}
#else
		pwszServerName = (WCHAR*)pszServerName;
#endif

		ZeroMemory(&ChainPara, sizeof(ChainPara));
		ChainPara.cbSize = sizeof(ChainPara);

		if (!CertGetCertificateChain(
								0,
								pServerCert,
								0,
								0,
								&ChainPara,
								0,
								0,
								&pChainContext)) {
			Status = ::GetLastError();
			SetLastError(Status);
			break;
		}

		ZeroMemory(&polHttps, sizeof(HTTPSPolicyCallbackData));
		polHttps.cbStruct           = sizeof(HTTPSPolicyCallbackData);
		polHttps.dwAuthType         = AUTHTYPE_SERVER;
		polHttps.fdwChecks          = dwCertFlags;
		polHttps.pwszServerName     = pwszServerName;

		memset(&PolicyPara, 0, sizeof(PolicyPara));
		PolicyPara.cbSize            = sizeof(PolicyPara);
		PolicyPara.pvExtraPolicyPara = &polHttps;

		memset(&PolicyStatus, 0, sizeof(PolicyStatus));
		PolicyStatus.cbSize = sizeof(PolicyStatus);

	    if (!CertVerifyCertificateChainPolicy(
                            CERT_CHAIN_POLICY_SSL,
                            pChainContext,
                            &PolicyPara,
                            &PolicyStatus)) {
			Status = ::GetLastError();
			SetLastError(Status);
			break;
		}

		if (PolicyStatus.dwError) {
			Status = PolicyStatus.dwError;
			SetLastError(Status);
			break;
		}

		PCERT_CONTEXT *pCerts = new PCERT_CONTEXT[pChainContext->cChain];

		for (DWORD i = 0; i < pChainContext->cChain; i++) {
			pCerts[i] = (PCERT_CONTEXT)(pChainContext->rgpChain[i]->rgpElement[0]->pCertContext);
		}
		
		CERT_REVOCATION_STATUS revStat;
		revStat.cbSize = sizeof(CERT_REVOCATION_STATUS);

		/*BOOL bRc = CertVerifyRevocation(
						X509_ASN_ENCODING,
						CERT_CONTEXT_REVOCATION_TYPE,
						pChainContext->cChain,
						(void **)pCerts,
						CERT_VERIFY_REV_CHAIN_FLAG,
						0,
						&revStat);
		if (!bRc) {
			SetLastError(revStat.dwError);
			break;
		}*/

		delete [] pCerts;

		Status = SEC_E_OK;

		} while (FALSE);

    if (pChainContext) {
        CertFreeCertificateChain(pChainContext);
    }

#ifndef _UNICODE
	if (pwszServerName) delete [] pwszServerName;
#endif

    return Status;
}

LONG CSslSocket::ClientDisconnect(PCredHandle phCreds, CtxtHandle *phContext)
{
    DWORD           dwType;
    PBYTE           pbMessage;
    DWORD           cbMessage;
    DWORD           cbData;

    SecBufferDesc   OutBuffer;
    SecBuffer       OutBuffers[1];
    DWORD           dwSSPIFlags;
    DWORD           dwSSPIOutFlags;
    TimeStamp       tsExpiry;
    DWORD           Status;

    dwType = SCHANNEL_SHUTDOWN;

    OutBuffers[0].pvBuffer   = &dwType;
    OutBuffers[0].BufferType = SECBUFFER_TOKEN;
    OutBuffers[0].cbBuffer   = sizeof(dwType);

    OutBuffer.cBuffers  = 1;
    OutBuffer.pBuffers  = OutBuffers;
    OutBuffer.ulVersion = SECBUFFER_VERSION;

	do {

		Status = m_SecurityFunc.ApplyControlToken(phContext, &OutBuffer);

		if(FAILED(Status)) {
			SetLastError(Status);
			break;
		}

		dwSSPIFlags = ISC_REQ_SEQUENCE_DETECT   |
					  ISC_REQ_REPLAY_DETECT     |
					  ISC_REQ_CONFIDENTIALITY   |
					  ISC_RET_EXTENDED_ERROR    |
					  ISC_REQ_ALLOCATE_MEMORY   |
					  ISC_REQ_STREAM;

		OutBuffers[0].pvBuffer   = 0;
		OutBuffers[0].BufferType = SECBUFFER_TOKEN;
		OutBuffers[0].cbBuffer   = 0;

		OutBuffer.cBuffers  = 1;
		OutBuffer.pBuffers  = OutBuffers;
		OutBuffer.ulVersion = SECBUFFER_VERSION;

		Status = m_SecurityFunc.InitializeSecurityContext(
                    phCreds,
                    phContext,
                    0,
                    dwSSPIFlags,
                    0,
                    SECURITY_NATIVE_DREP,
                    0,
                    0,
                    phContext,
                    &OutBuffer,
                    &dwSSPIOutFlags,
                    &tsExpiry);

		if(FAILED(Status)) {
			SetLastError(Status);
			break;
		}

		pbMessage = (BYTE *)(OutBuffers[0].pvBuffer);
		cbMessage = OutBuffers[0].cbBuffer;

		if(pbMessage != 0 && cbMessage != 0) {
			m_bAllowPlainText = TRUE; m_bConInit = FALSE;
			cbData = Send(pbMessage, cbMessage);
			m_bAllowPlainText = FALSE;
			if(cbData == SOCKET_ERROR || cbData == 0) {
				Status = WSAGetLastError();
				SetLastError(Status);
				break;
			}

			m_SecurityFunc.FreeContextBuffer(pbMessage);
		}
    
	} while (FALSE);

    m_SecurityFunc.DeleteSecurityContext(phContext);

    return Status;
}

LONG CSslSocket::ServerDisconect(PCredHandle phCreds, CtxtHandle *phContext)
{
    DWORD           dwType;
    PBYTE           pbMessage;
    DWORD           cbMessage;
    DWORD           cbData;

    SecBufferDesc   OutBuffer;
    SecBuffer       OutBuffers[1];
    DWORD           dwSSPIFlags;
    DWORD           dwSSPIOutFlags;
    TimeStamp       tsExpiry;
    DWORD           Status;

    dwType = SCHANNEL_SHUTDOWN;

    OutBuffers[0].pvBuffer   = &dwType;
    OutBuffers[0].BufferType = SECBUFFER_TOKEN;
    OutBuffers[0].cbBuffer   = sizeof(dwType);

    OutBuffer.cBuffers  = 1;
    OutBuffer.pBuffers  = OutBuffers;
    OutBuffer.ulVersion = SECBUFFER_VERSION;

	do {

		Status = m_SecurityFunc.ApplyControlToken(phContext, &OutBuffer);

		if(FAILED(Status)) {
			SetLastError(Status);
			break;
		}

		dwSSPIFlags =   ASC_REQ_SEQUENCE_DETECT     |
						ASC_REQ_REPLAY_DETECT       |
						ASC_REQ_CONFIDENTIALITY     |
						ASC_REQ_EXTENDED_ERROR      |
						ASC_REQ_ALLOCATE_MEMORY     |
						ASC_REQ_STREAM;

		OutBuffers[0].pvBuffer   = 0;
		OutBuffers[0].BufferType = SECBUFFER_TOKEN;
		OutBuffers[0].cbBuffer   = 0;

		OutBuffer.cBuffers  = 1;
		OutBuffer.pBuffers  = OutBuffers;
		OutBuffer.ulVersion = SECBUFFER_VERSION;

		Status = m_SecurityFunc.AcceptSecurityContext(
						phCreds,
						phContext,
						0,
						dwSSPIFlags,
						SECURITY_NATIVE_DREP,
						0,
						&OutBuffer,
						&dwSSPIOutFlags,
						&tsExpiry);

		if(FAILED(Status))  {
			SetLastError(Status);
			break;
		}

		pbMessage = (BYTE *)(OutBuffers[0].pvBuffer);
		cbMessage = OutBuffers[0].cbBuffer;

		if(pbMessage != 0 && cbMessage != 0) {
			m_bAllowPlainText = TRUE; m_bConInit = FALSE;
			cbData = Send(pbMessage, cbMessage);
			m_bAllowPlainText = FALSE;
			if(cbData == SOCKET_ERROR || cbData == 0) {
				Status = WSAGetLastError();
				SetLastError(Status);
				break;
			}

			m_SecurityFunc.FreeContextBuffer(pbMessage);
		}

	} while (FALSE);

    m_SecurityFunc.DeleteSecurityContext(phContext);

    return Status;
}

BOOL CSslSocket::ServerConnect(SOCKADDR* lpSockAddr, int* lpSockAddrLen)
{
	BOOL rc = FALSE;
	SECURITY_STATUS scRet;
	PCCERT_CONTEXT pRemoteCertContext = 0;
	SecPkgContext_StreamSizes Sizes;

	do {

		if (!ServerHandshakeLoop(&m_hContext,&m_hCreds,m_bAuthClient,TRUE,TRUE)) {
			break;
		}

		if(m_bAuthClient) {
            scRet = m_SecurityFunc.QueryContextAttributes(&m_hContext,
                                            SECPKG_ATTR_REMOTE_CERT_CONTEXT,
                                            (PVOID)&pRemoteCertContext);

            if(scRet != SEC_E_OK) {
                SetLastError(scRet);
				break;
            } else {
                scRet = ServerVerifyCertificate(pRemoteCertContext, 0);
                if(scRet) {
                    SetLastError(scRet);
                    break;
                }
				CertFreeCertificateContext(pRemoteCertContext);
            }
        }

        scRet = m_SecurityFunc.QueryContextAttributes(&m_hContext, SECPKG_ATTR_STREAM_SIZES, &Sizes);

        if(scRet != SEC_E_OK) {
            SetLastError(scRet);
            break;
        }

		rc = TRUE;

	} while (FALSE);

	return rc;
}

BOOL CSslSocket::ServerHandshakeLoop(PCtxtHandle phContext, PCredHandle phCred, BOOL fClientAuth, BOOL fDoInitialRead, BOOL NewContext)
{
    TimeStamp            tsExpiry;
    SECURITY_STATUS      scRet;
    SecBufferDesc        InBuffer;
    SecBufferDesc        OutBuffer;
    SecBuffer            InBuffers[2];
    SecBuffer            OutBuffers[1];
    DWORD                err;

    BOOL                 fDoRead;
    BOOL                 fInitContext = NewContext;

    DWORD                dwSSPIFlags, dwSSPIOutFlags;

	BYTE IoBuffer[IO_BUFFER_SIZE];
	DWORD cbIoBuffer = 0;

    scRet = SEC_E_SECPKG_NOT_FOUND;
    err = 0;

    fDoRead = fDoInitialRead;

    dwSSPIFlags =   ASC_REQ_SEQUENCE_DETECT        |
                    ASC_REQ_REPLAY_DETECT      |
                    ASC_REQ_CONFIDENTIALITY  |
                    ASC_REQ_EXTENDED_ERROR    |
                    ASC_REQ_ALLOCATE_MEMORY  |
                    ASC_REQ_STREAM;

    if(fClientAuth) {
        dwSSPIFlags |= ASC_REQ_MUTUAL_AUTH;
    }


    OutBuffer.cBuffers = 1;
    OutBuffer.pBuffers = OutBuffers;
    OutBuffer.ulVersion = SECBUFFER_VERSION;

    scRet = SEC_I_CONTINUE_NEEDED;

    while( scRet == SEC_I_CONTINUE_NEEDED ||
            scRet == SEC_E_INCOMPLETE_MESSAGE ||
            scRet == SEC_I_INCOMPLETE_CREDENTIALS)  {

        if(0 == cbIoBuffer || scRet == SEC_E_INCOMPLETE_MESSAGE) {

            if(fDoRead) {
				m_bAllowPlainText = TRUE;
				err = Receive(IoBuffer+cbIoBuffer, IO_BUFFER_SIZE);
				m_bAllowPlainText = FALSE;

				if (err == SOCKET_ERROR || err == 0) {
					SetLastError(::WSAGetLastError());
					return FALSE;
				} else {
					cbIoBuffer += err;
				}
            } else {
                fDoRead = TRUE;
            }
        }

        InBuffers[0].pvBuffer = IoBuffer;
        InBuffers[0].cbBuffer = cbIoBuffer;
        InBuffers[0].BufferType = SECBUFFER_TOKEN;

        InBuffers[1].pvBuffer   = 0;
        InBuffers[1].cbBuffer   = 0;
        InBuffers[1].BufferType = SECBUFFER_EMPTY;

        InBuffer.cBuffers        = 2;
        InBuffer.pBuffers        = InBuffers;
        InBuffer.ulVersion       = SECBUFFER_VERSION;

        OutBuffers[0].pvBuffer   = 0;
        OutBuffers[0].BufferType = SECBUFFER_TOKEN;
        OutBuffers[0].cbBuffer   = 0;

        scRet = m_SecurityFunc.AcceptSecurityContext(
                        phCred,
                        (fInitContext?0:phContext),
                        &InBuffer,
                        dwSSPIFlags,
                        SECURITY_NATIVE_DREP,
                        (fInitContext?phContext:0),
                        &OutBuffer,
                        &dwSSPIOutFlags,
                        &tsExpiry);

        fInitContext = FALSE;

        if ( scRet == SEC_E_OK ||
             scRet == SEC_I_CONTINUE_NEEDED ||
             (FAILED(scRet) && (0 != (dwSSPIOutFlags & ISC_RET_EXTENDED_ERROR)))) {

            if  (OutBuffers[0].cbBuffer != 0    &&
                 OutBuffers[0].pvBuffer != 0 ) {

				m_bAllowPlainText = TRUE;
                err = Send(OutBuffers[0].pvBuffer,OutBuffers[0].cbBuffer);
				m_bAllowPlainText = FALSE;

                m_SecurityFunc.FreeContextBuffer( OutBuffers[0].pvBuffer );
                OutBuffers[0].pvBuffer = 0;
            }
        }

        if ( scRet == SEC_E_OK ) {
            if ( InBuffers[1].BufferType == SECBUFFER_EXTRA ) {
                    memcpy(IoBuffer,
                           (LPBYTE) (IoBuffer + (cbIoBuffer - InBuffers[1].cbBuffer)),
                            InBuffers[1].cbBuffer);
                    cbIoBuffer = InBuffers[1].cbBuffer;
            } else {
                cbIoBuffer = 0;
            }

            return TRUE;
        } else if (FAILED(scRet) && (scRet != SEC_E_INCOMPLETE_MESSAGE)) {
            SetLastError(scRet);
            return FALSE;
        }

        if ( scRet != SEC_E_INCOMPLETE_MESSAGE &&
             scRet != SEC_I_INCOMPLETE_CREDENTIALS) {

            if ( InBuffers[1].BufferType == SECBUFFER_EXTRA ) {
                memcpy(IoBuffer,
                       (LPBYTE) (IoBuffer + (cbIoBuffer - InBuffers[1].cbBuffer)),
                        InBuffers[1].cbBuffer);
                cbIoBuffer = InBuffers[1].cbBuffer;
            } else {
                cbIoBuffer = 0;
            }
        }
    }

    return FALSE;
}

DWORD CSslSocket::ServerVerifyCertificate(PCCERT_CONTEXT pServerCert, DWORD dwCertFlags)
{
    HTTPSPolicyCallbackData		polHttps;
    CERT_CHAIN_POLICY_PARA		PolicyPara;
    CERT_CHAIN_POLICY_STATUS	PolicyStatus;
    CERT_CHAIN_PARA				ChainPara;
    PCCERT_CHAIN_CONTEXT		pChainContext = 0;

    DWORD   Status;

	do {
		if(pServerCert == 0) {
			Status = SEC_E_WRONG_PRINCIPAL;
			SetLastError(Status);
			break;
		}

		int iRc = CertVerifyTimeValidity(0,pServerCert->pCertInfo);
		if (iRc != 0) {
			Status = SEC_E_CERT_EXPIRED;
			SetLastError(Status);
			break;
		}

		ZeroMemory(&ChainPara, sizeof(ChainPara));
		ChainPara.cbSize = sizeof(ChainPara);

		if(!CertGetCertificateChain(
								0,
								pServerCert,
								0,
								0,
								&ChainPara,
								CERT_CHAIN_REVOCATION_CHECK_CHAIN,
								0,
								&pChainContext)) {
			Status = ::GetLastError();
			SetLastError(Status);
			break;
		}

		ZeroMemory(&polHttps, sizeof(HTTPSPolicyCallbackData));
		polHttps.cbStruct           = sizeof(HTTPSPolicyCallbackData);
		polHttps.dwAuthType         = AUTHTYPE_CLIENT;
		polHttps.fdwChecks          = dwCertFlags;
		polHttps.pwszServerName     = 0;

		memset(&PolicyPara, 0, sizeof(PolicyPara));
		PolicyPara.cbSize            = sizeof(PolicyPara);
		PolicyPara.pvExtraPolicyPara = &polHttps;

		memset(&PolicyStatus, 0, sizeof(PolicyStatus));
		PolicyStatus.cbSize = sizeof(PolicyStatus);

		if(!CertVerifyCertificateChainPolicy(
								CERT_CHAIN_POLICY_SSL,
								pChainContext,
								&PolicyPara,
								&PolicyStatus)) {
			Status = ::GetLastError();
			SetLastError(Status);
			break;
		}

		if(PolicyStatus.dwError) {
			Status = PolicyStatus.dwError;
			SetLastError(Status);
			break;
		}

		PCERT_CONTEXT *pCerts = new PCERT_CONTEXT[pChainContext->cChain];

		for (DWORD i = 0; i < pChainContext->cChain; i++) {
			pCerts[i] = (PCERT_CONTEXT)(pChainContext->rgpChain[i]->rgpElement[0]->pCertContext);
		}
		
		CERT_REVOCATION_STATUS revStat;
		revStat.cbSize = sizeof(CERT_REVOCATION_STATUS);

		BOOL bRc = CertVerifyRevocation(
						X509_ASN_ENCODING,
						CERT_CONTEXT_REVOCATION_TYPE,
						pChainContext->cChain,
						(void **)pCerts,
						CERT_VERIFY_REV_CHAIN_FLAG,
						NULL,
						&revStat);
		if (!bRc) {
			SetLastError(revStat.dwError);
			break;
		}

		delete [] pCerts;
		Status = SEC_E_OK;

	} while(FALSE);

    if (pChainContext) {
        CertFreeCertificateChain(pChainContext);
    }

    return Status;
}
