

#ifndef __SOCKSIFIEDSOCKET___H_
#define __SOCKSIFIEDSOCKET___H_
#pragma once

/// namespace stream
namespace stream
{

/// namespace exceptions
namespace exceptions
{
	//Errorcodes
	enum EProxyError
	{
	PROXYERROR_NOCONN = 1,
	PROXYERROR_REQUESTFAILED = 2,
	PROXYERROR_AUTHREQUIRED = 3,
	PROXYERROR_AUTHTYPEUNKNOWN = 4,
	PROXYERROR_AUTHFAILED = 5,
	PROXYERROR_AUTHNOLOGON = 6
	};

	/**
		Proxy exception.
	*/
	class ProxyException : public StreamException
	{
	public:
		ProxyException(EProxyError id_code):StreamException(id_code,"")
		{
			std::string description;
			switch(id_code)
			{
			case PROXYERROR_NOCONN:
				description = "Fail connecting proxy server.";
				break;
			case PROXYERROR_REQUESTFAILED:
				description = "Request failed.";
				break;
			case PROXYERROR_AUTHREQUIRED:
				description = "Authetication required.";
				break;
			case PROXYERROR_AUTHTYPEUNKNOWN:
				description = "Authetication type unknown.";
				break;
			case PROXYERROR_AUTHFAILED:
				description = "Authetication fail.";
				break;
			case PROXYERROR_AUTHNOLOGON:
				description = "No logon params specified";
				break;
			};
			m_desc = description;
		}
	};

} // namespace exceptions

/**
Provides the classes for implementing networking applications. 
*/
namespace net
{
/** 
	Authentication credentials query interface
*/
class IProxyAuthData
{
public:
	/**
		On return, implementator class must specify the login and password.
	*/
	virtual void GetAuthData(std::string& login, std::string& password) = 0;
};

/**
This class implements several proxy protocols: HTTP-PROXY, SOCKS4, SOCKS5 with optional authentication.
The following example explains usage:<br>
	SocksifiedSocket ss;<br><br>
	ss.setProxy(SocksifiedSocket::PROXYTYPE_CONNECT,"proxy.domain.com","8080");<br>	
	if(ss.connectTo("www.microsoft.com","80"))<br>
	{<br>
		Socket* sock = ss.getSocket().release();<br>
		// Uses sock to send/receive data to host.

<br>
<br>
<br>
* This class can only be used with plain sockets; no SSL is suported in this library.
 */
class SocksifiedSocket
{

public:

/**
	Proxy types
	<lu>
	<li><b>PROXYTYPE_NOPROXY</b> No proxy protocol is used</li>
	<li><b>PROXYTYPE_SOCKS4</b> SOCKS 4 protocol</li>
	<li><b>PROXYTYPE_SOCKS5</b> SOCKS 5 protocol</li>
	<li><b>PROXYTYPE_CONNECT</b> HTTP-PROXY protocol</li>
	</lu>
*/
enum EProxyType
{
PROXYTYPE_NOPROXY = 0,
PROXYTYPE_SOCKS4 = 1,
PROXYTYPE_SOCKS5 = 2,
PROXYTYPE_CONNECT = 3
};

	std::string m_ProxyHost;
	std::string m_ProxyPort;
	std::string m_ProxyUser;
	std::string m_ProxyPass;
	std::string m_host;
	std::string m_port; 
	bool m_bUseSocks5Logon;

	
	EProxyType m_nProxyType;



public:
	SocksifiedSocket(const std::string& userAgent = "", std::auto_ptr<IProxyAuthData> authDataInterface = std::auto_ptr<IProxyAuthData>(0));
	virtual ~SocksifiedSocket();

	/**
		To start proxy communication, call this method and specify name and port of destination server.
		@param lpszHostAddress Host name or ip of the destination server.
		@param nHostPort port on the destination server.
		@return <b>true</b> if the conection is saccesfull, otherwise an exception is thrown.
		@exceptions ProxyException* if method fails.
	*/
	virtual bool connectTo(const std::string& lpszHostAddress, const std::string& nHostPort )throw(exceptions::ProxyException*);

	/**
		Use this method to specify the proxy connection parameters.
		@param nProxyType Proxy protocol to use. EProxyType
		@param ProxyHost Name or ip of the proxy server.
		@param ProxyPort Port on proxy server.
		@param ProxyUser User name used on proxy authentication.
		@param ProxyPass Password used on proxy authentication.
		@param authenticateFirst The first try will include the authentication parameters.
		@param bUseSocks5Logon Set to <b>true</b> to use SOCK5 with authentication. This param only has effect when used with PROXYTYPE_SOCKS5.
	*/
	void setProxy(EProxyType nProxyType,const std::string& ProxyHost,const std::string& ProxyPort,const std::string& ProxyUser="",const std::string& ProxyPass="", bool authenticateFirst = false, bool bUseSocks5Logon=FALSE);

	/** 
		@return An automatic pointer to the object Socket created to comunicate with proxy server.
		Once called method ConnectTo, this method can be used to retrive the object of class 
		Socket that can be used to communicate with destination server.
	*/
	SocketPtr releaseSocket();

	/**
		@return last reponse of the proxy server.
	*/
	std::string getLastResponse();

protected:
	int m_nProxyPeerPort;
	ULONG m_nProxyPeerIp;

	/**
		This method creates the connection string that is send to the proxy when PROXYTYPE_CONNECT is used.
	*/
	std::string constructConnectStr(bool include_auth_params);
	
	bool connect( const SOCKADDR* lpSockAddr, int nSockAddrLen);

	SocketPtr m_sock;

	std::string m_userAgent;

	// Removes all the input data, leaving this stream empty.
	void clearInput(io::IInputStream* input);

	std::auto_ptr<IProxyAuthData> m_authDataInterface;

	// Last html response of the proxy server, without http headers.
	std::string m_lastResponse;

	bool m_authenticateFirst;
};

} // namespace net

} //namespace stream

#endif __SOCKSIFIEDSOCKET___H_