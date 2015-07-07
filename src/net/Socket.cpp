// Socket.cpp: implementation of the Socket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "IOutputStream.h"	// Added by ClassView
#include "IInputStream.h"
#include "Exceptions.h"
#include "Socket.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace stream
{
using namespace io;

namespace exceptions
{

SocketStreamException::SocketStreamException()
{

	
	DWORD err = WSAGetLastError();

	char message[1000];
	int length = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,0,err,0,message,1000,NULL);


	m_err_code = err;
	m_desc = message;
}

} // namespace exceptions
/// namespace net
namespace net
{
void SocketOptions::setSockOpt(SOCKET& sock)
{


	if(m_recvBuf != -1)
	{
		if(::setsockopt(sock,SOL_SOCKET,SO_RCVBUF,(const char *)&m_recvBuf,sizeof(int)) != 0)
			throw new exceptions::SocketStreamException();
	}
	if(m_sendBuf != -1)
	{
		if(::setsockopt(sock,SOL_SOCKET,SO_SNDBUF,(const char *)&m_sendBuf,sizeof(int)) != 0)
			throw new exceptions::SocketStreamException();	
	}
	if(m_recvTimeOut != -1)
	{
		if(::setsockopt(sock,SOL_SOCKET,SO_RCVTIMEO,(const char *)&m_recvTimeOut,sizeof(int)) != 0)
			throw new exceptions::SocketStreamException();	
	}
	if(m_sendTimeOut != -1)
	{
		if(::setsockopt(sock,SOL_SOCKET,SO_SNDTIMEO,(const char *)&m_sendTimeOut,sizeof(int)) != 0)
			throw new exceptions::SocketStreamException();	
	}

	if(m_tcpNoDelay)
	{
		if(::setsockopt(sock,IPPROTO_TCP,TCP_NODELAY,(const char *)&m_tcpNoDelay,sizeof(BOOL)) != 0)
			throw new exceptions::SocketStreamException();	
	}
}

void SocketOptions::getSockOpt(SOCKET& sock)
{

	int size = sizeof(int);
	if(::getsockopt(sock,SOL_SOCKET,SO_RCVBUF,(char *)&m_recvBuf,&size) != 0)
		throw new exceptions::SocketStreamException();
	
	
	if(::getsockopt(sock,SOL_SOCKET,SO_SNDBUF,(char *)&m_sendBuf,&size) != 0)
		throw new exceptions::SocketStreamException();	


	if(::getsockopt(sock,SOL_SOCKET,SO_RCVTIMEO,(char *)&m_recvTimeOut,&size) != 0)
		throw new exceptions::SocketStreamException();	


	if(::getsockopt(sock,SOL_SOCKET,SO_SNDTIMEO,(char *)&m_sendTimeOut,&size) != 0)
		throw new exceptions::SocketStreamException();	

	size = sizeof(BOOL);
	if(::getsockopt(sock,IPPROTO_TCP,TCP_NODELAY,(char *)&m_tcpNoDelay,&size) != 0)
		throw new exceptions::SocketStreamException();	
}


void Socket::getSocketOptions(SocketOptions& prop)
{
	prop.getSockOpt(m_sock);
}

void Socket::setSocketOptions(SocketOptions& prop)
{
	prop.setSockOpt(m_sock);
}
#pragma warning(disable: 4355)	// this warning
Socket::Socket(SOCKET s,int socket_type):m_Internal_OutputStream_udp(this),m_Internal_InputStream_udp(this),m_Internal_OutputStream(this),m_Internal_InputStream(this)
{
	m_sock = s;
	m_socket_type = socket_type;
	WSADATA		wsd;
	WSAStartup(MAKEWORD(2,2),&wsd);
}

Socket::Socket(std::string host,std::string port,std::string bind_ip,std::string bind_port,SockProto proto,SocketOptions* options):m_Internal_OutputStream_udp(this),m_Internal_InputStream_udp(this),m_Internal_OutputStream(this),m_Internal_InputStream(this)
{	
	m_sock = 0;

	int type;
	WSADATA		wsd;
	WSAStartup(MAKEWORD(2,2),&wsd);

	switch(proto)
	{
	case SP_TCP:
			type = SOCK_STREAM;
			break;
	case SP_UDP:
			type = SOCK_DGRAM;
			break;
	case SP_RAW:
			type = SOCK_RAW;
			break;
	default:
			type = SOCK_STREAM;
			break;
	}

	
	m_sock = socket(AF_INET,type,0);
	if(m_sock != INVALID_SOCKET )
	{
		struct hostent	   *hp = 0;
		unsigned int		addr;				// destination's addr
		
		m_sock_in.sin_family = AF_INET;
		//sock_in.sin_addr.S_un.S_addr = inet_addr(host.c_str());
		m_sock_in.sin_port = htons(atol(port.c_str()));
		memset(m_sock_in.sin_zero,0,sizeof(m_sock_in.sin_zero));


		if ((addr = inet_addr(host.c_str())) == INADDR_NONE)
		{
			hp = gethostbyname(host.c_str());
			if (hp)
				memcpy(&(m_sock_in.sin_addr), hp->h_addr, hp->h_length);
			else
			{
				throw new exceptions::SocketStreamException();	
			}
		}
		else
			m_sock_in.sin_addr.s_addr = addr;

		if (hp)
			m_sock_in.sin_family = hp->h_addrtype;
		else
			m_sock_in.sin_family = AF_INET;

	}
	else
	{
		throw new exceptions::SocketStreamException();
	}


	if(options)
		options->setSockOpt(m_sock);
	

	if(bind_ip != "")
	{
		struct hostent	   *hp_local = 0;
		struct sockaddr_in m_sock_bind;
		unsigned int		bind_addr;				// bind's addr

		m_sock_bind.sin_port = htons(atol(bind_port.c_str()));
		memset(m_sock_in.sin_zero,0,sizeof(m_sock_in.sin_zero));

		if ((bind_addr = inet_addr(bind_ip.c_str())) == INADDR_NONE)
			{
			hp_local = gethostbyname(bind_ip.c_str());
			if (hp_local)
				memcpy(&(m_sock_bind.sin_addr), hp_local->h_addr, hp_local->h_length);
			else
			{
				throw new exceptions::SocketStreamException();	
			}
		}
		else
			m_sock_bind.sin_addr.s_addr = bind_addr;

		if (hp_local)
			m_sock_bind.sin_family = hp_local->h_addrtype;
		else
			m_sock_bind.sin_family = AF_INET;


		int r = ::bind(m_sock,(struct sockaddr *)&m_sock_bind,sizeof(sockaddr_in));
		
		if(r != 0)
		{
			throw new exceptions::SocketStreamException();
		}

  	}



	int result = ::connect(m_sock,(struct sockaddr *)&m_sock_in,sizeof(sockaddr_in));

	if(result != 0)
	{
		if(m_sock)
		{
			shutdown(m_sock,SD_BOTH);
			closesocket(m_sock);
			m_sock = 0;
		}
		throw new exceptions::SocketStreamException();	
	}
}

Socket::~Socket()
{
	if(m_sock)
	{
		shutdown(m_sock,SD_BOTH);
		closesocket(m_sock);
		m_sock = 0;
	}

	WSACleanup();
}

IInputStream* Socket::getInputStream()
{
	if(m_sock)
	{
		if(m_socket_type != SOCK_DGRAM)
		{
			return &m_Internal_InputStream;
			
		}
		else
		{
			return &m_Internal_InputStream_udp;
			
		}
	}

	return 0;
}

IOutputStream* Socket::getOutputStream()
{
	if(m_sock)
	{
		if(m_socket_type != SOCK_DGRAM)
		{
		
			return &m_Internal_OutputStream;
		}
		else
		{
			return &m_Internal_OutputStream_udp;
		}

	}

	return 0;
}


void Socket::close()
{
	if(m_sock)
	{
		shutdown(m_sock,SD_BOTH);
		closesocket(m_sock);
		m_sock = 0;
	}
}


std::string Socket::getInetAddress()throw(exceptions::SocketStreamException*)
{
	struct sockaddr_in name;
	int namelen = sizeof(sockaddr_in);
	int err = getpeername(m_sock,(struct sockaddr *)&name,&namelen);

	if(err != 0)
	{
		// Errrorrrrr !!!!!!!!
		throw new exceptions::SocketStreamException();
	}

	return std::string(inet_ntoa(name.sin_addr));  
}
std::string Socket::getLocalAddress()throw(exceptions::SocketStreamException*)
{
	struct sockaddr_in name;
	int namelen = sizeof(sockaddr_in);
	int err = getsockname(m_sock,(struct sockaddr *)&name,&namelen);

	if(err != 0)
	{
		// Errrorrrrr !!!!!!!!
		throw new exceptions::SocketStreamException();
	}
	return std::string(inet_ntoa(name.sin_addr));
}
unsigned int Socket::getPort()throw(exceptions::SocketStreamException*)
{
	struct sockaddr_in name;
	int namelen = sizeof(sockaddr_in);
	int err = getpeername(m_sock,(struct sockaddr *)&name,&namelen);

	if(err != 0)
	{
		// Errrorrrrr !!!!!!!!
		throw new exceptions::SocketStreamException();
	}

	return ntohs(name.sin_port);  
}
unsigned int Socket::getLocalPort()throw(exceptions::SocketStreamException*)
{
	struct sockaddr_in name;
	int namelen = sizeof(sockaddr_in);
	int err = getsockname(m_sock,(struct sockaddr *)&name,&namelen);

	if(err != 0)
	{
		// Errrorrrrr !!!!!!!!
		throw new exceptions::SocketStreamException();
	}

	return ntohs(name.sin_port);
}


std::string Socket::getConnectionString()throw(exceptions::SocketStreamException*)
{
	char cad[10];
	std::string connection;
	connection = getInetAddress();
	connection += std::string(":");
	itoa(getPort(),cad,10);
	connection += cad;
	connection += std::string(">");
	connection += getLocalAddress();
	connection += std::string(":");
	itoa(getLocalPort(),cad,10);
	connection += cad;
	return connection;
}

Socket::Internal_OutputStream::Internal_OutputStream(Socket* parent)
{
	m_parent = parent;
}

void Socket::Internal_OutputStream::close()
{	
}

void Socket::Internal_OutputStream::flush()
{
}

void Socket::Internal_OutputStream::write(unsigned char* b,long length)throw(exceptions::SocketStreamException*)
{
	if(send(m_parent->m_sock,(const char*)b,length,0) == SOCKET_ERROR)
	{
		throw new exceptions::SocketStreamException();	
	}
}

void Socket::Internal_OutputStream::write(unsigned char* b, int off, int len)throw(exceptions::SocketStreamException*)
{
	if(send(m_parent->m_sock,(const char*)(b+off),len,0) == SOCKET_ERROR)
	{
		throw new exceptions::SocketStreamException();	
	}
}

void Socket::Internal_OutputStream::write(int b)throw(exceptions::SocketStreamException*)
{
	char p = b;
	if(send(m_parent->m_sock,(const char*)&p,sizeof(char),0) == SOCKET_ERROR)
	{
		throw new exceptions::SocketStreamException();	
	}
}



Socket::Internal_InputStream::Internal_InputStream(Socket* parent)
{
	m_parent = parent;
}


int Socket::Internal_InputStream::available()
{
	unsigned long data = 0;
	if(ioctlsocket(m_parent->m_sock,FIONREAD,&data) == SOCKET_ERROR)
	{
		throw new exceptions::SocketStreamException();
	}

	return data;
}

void Socket::Internal_InputStream::close()
{
}

void Socket::Internal_InputStream::mark(int readlimit)
{
}

bool Socket::Internal_InputStream::markSupported()
{
	return false;
}

int Socket::Internal_InputStream::read()throw(exceptions::SocketStreamException*)
{
	char data[1];

	int ret = 0;
	if((ret = recv(m_parent->m_sock,data,1,0)) == SOCKET_ERROR)
	{
		throw new exceptions::SocketStreamException();	
	}

	if(ret == SOCKET_ERROR)
	{
		throw new exceptions::SocketStreamException();	
	}

	/*if(ret == 0)
	{
		throw new exceptions::SocketStreamException();	
	}*/

	return data[0];
}

int Socket::Internal_InputStream::read(unsigned char* b,long length)throw(exceptions::SocketStreamException*)
{
	int ret = recv(m_parent->m_sock,(char*)b,length,0);
	if(ret == SOCKET_ERROR)
	{
		throw new exceptions::SocketStreamException();	
	}

/*	if(ret == 0)
	{
		throw new exceptions::SocketStreamException();	
	}*/

	return ret;
}

int Socket::Internal_InputStream::read(unsigned char* b, int off, int len)throw(exceptions::SocketStreamException*)
{
	int ret = recv(m_parent->m_sock,(char*)b+off,len,0);
	if(ret == SOCKET_ERROR)
	{
		throw new exceptions::SocketStreamException();	
	}

/*	if(ret == 0)
	{
		throw new exceptions::SocketStreamException();	
	}*/

	return ret;
}

void Socket::Internal_InputStream::reset()
{
}

long Socket::Internal_InputStream::skip(long n)throw(exceptions::SocketStreamException*)
{
	char* buffer = new char[n];

	long result = recv(m_parent->m_sock,buffer,n,0);

	if(result == SOCKET_ERROR)
	{
		throw new exceptions::SocketStreamException();	
	}

	if(result == 0)
	{
		throw new exceptions::SocketStreamException();	
	}

	return result;
}

Socket::Internal_OutputStream_udp::Internal_OutputStream_udp(Socket* parent)
{
	m_parent = parent;
}

void Socket::Internal_OutputStream_udp::close()
{	
}

void Socket::Internal_OutputStream_udp::flush()
{
}

void Socket::Internal_OutputStream_udp::write(unsigned char* b,long length)throw(exceptions::SocketStreamException*)
{
	struct sockaddr from;
	int fromlen = sizeof(sockaddr);
	if(sendto(m_parent->m_sock,(const char*)b,length,0,(struct sockaddr *)&from,fromlen) == SOCKET_ERROR)
	{
		throw new exceptions::SocketStreamException();	
	}
}

void Socket::Internal_OutputStream_udp::write(unsigned char* b, int off, int len)throw(exceptions::SocketStreamException*)
{
	struct sockaddr from;
	int fromlen = sizeof(sockaddr);
	if(sendto(m_parent->m_sock,(const char*)(b+off),len,0,(struct sockaddr *)&from,fromlen) == SOCKET_ERROR)
	{
		throw new exceptions::SocketStreamException();	
	}
}

void Socket::Internal_OutputStream_udp::write(int b)throw(exceptions::SocketStreamException*)
{
	struct sockaddr from;
	int fromlen = sizeof(sockaddr);
	char p = b;
	if(sendto(m_parent->m_sock,(const char*)&p,sizeof(char),0,(struct sockaddr *)&from,fromlen) == SOCKET_ERROR)
	{
		throw new exceptions::SocketStreamException();	
	}
}



Socket::Internal_InputStream_udp::Internal_InputStream_udp(Socket* parent)
{
	m_parent = parent;
}


int Socket::Internal_InputStream_udp::available()
{
	unsigned long data = 0;
	if(ioctlsocket(m_parent->m_sock,FIONREAD,&data) == SOCKET_ERROR)
	{
		throw new exceptions::SocketStreamException();
	}

	return data;
}

void Socket::Internal_InputStream_udp::close()
{
}

void Socket::Internal_InputStream_udp::mark(int readlimit)
{
}

bool Socket::Internal_InputStream_udp::markSupported()
{
	return false;
}

int Socket::Internal_InputStream_udp::read()throw(exceptions::SocketStreamException*)
{
	char data[1];
	struct sockaddr from;
	int fromlen = sizeof(sockaddr);
	int ret = 0;
	if((ret = recvfrom(m_parent->m_sock,data,1,0,(struct sockaddr *)&from,&fromlen)) == SOCKET_ERROR)
	{
		throw new exceptions::SocketStreamException();	
	}

	/*if(ret == 0)
	{
		throw new exceptions::SocketStreamException();	
	}*/

	return data[0];
}

int Socket::Internal_InputStream_udp::read(unsigned char* b,long length)throw(exceptions::SocketStreamException*)
{
	struct sockaddr from;
	int fromlen = sizeof(sockaddr);
	int ret = recvfrom(m_parent->m_sock,(char*)b,length,0,(struct sockaddr *)&from,&fromlen);
	if(ret == SOCKET_ERROR)
	{
		throw new exceptions::SocketStreamException();	
	}

	/*if(ret == 0)
	{
		throw new exceptions::SocketStreamException();	
	}*/

	return ret;
}

int Socket::Internal_InputStream_udp::read(unsigned char* b, int off, int len)throw(exceptions::SocketStreamException*)
{
	struct sockaddr from;
	int fromlen = sizeof(sockaddr);
	int ret = recvfrom(m_parent->m_sock,(char*)b+off,len,0,(struct sockaddr *)&from,&fromlen);
	if(ret == SOCKET_ERROR)
	{
		throw new exceptions::SocketStreamException();	
	}

	/*if(ret == 0)
	{
		throw new exceptions::SocketStreamException();	
	}*/

	return ret;
}

void Socket::Internal_InputStream_udp::reset()
{
}

long Socket::Internal_InputStream_udp::skip(long n)throw(exceptions::SocketStreamException*)
{
	char* buffer = new char[n];

	struct sockaddr from;
	int fromlen = sizeof(sockaddr);
	long result = recvfrom(m_parent->m_sock,buffer,n,0,(struct sockaddr *)&from,&fromlen);

	if(result == SOCKET_ERROR)
	{
		throw new exceptions::SocketStreamException();	
	}

	if(result == 0)
	{
		throw new exceptions::SocketStreamException();	
	}

	return result;
}

std::string Socket::getHostName()
{
	char buffer[256];
	::gethostname(buffer,255);
	return buffer;
}

SOCKET Socket::ReleaseSocketHandle()
{
	SOCKET s = m_sock;
	m_sock = 0;
	return s;
}

bool Socket::haveErrors()
{
	FD_SET error;
	FD_ZERO(&error);
	FD_SET(m_sock,&error);
	
	timeval t;
	t.tv_sec = 0;
	t.tv_usec = 0;
	if(select(0,0,0,&error,&t) == 0)
	{
		// timeout, no hay error;
		return false;
	}

	return true;

}

bool Socket::isClosed()
{
	timeval waitTime;
	
	waitTime.tv_sec = 0;
	waitTime.tv_usec = 0;

	fd_set readFds;
	fd_set exceptFds;

	FD_ZERO(&readFds);
	FD_ZERO(&exceptFds);

	FD_SET(m_sock,&readFds);

	int retval = ::select(0,&readFds,0,&exceptFds,&waitTime);

	if(retval == SOCKET_ERROR)
	{
		throw new exceptions::SocketStreamException();	
	}

	if(retval == 0)
	{
		return false;
	}
	else
	{
		unsigned long data = 0;
		if(ioctlsocket(m_sock,FIONREAD,&data) == SOCKET_ERROR)
		{
			throw new exceptions::SocketStreamException();
		}

		if(data == 0)
		{
			// Si se puede leer, pero hay no hay datos que leer esto significa que el socket se ha cerrado.
			return true;
		}
	}

	
	return false;
}

} // namespace net

}