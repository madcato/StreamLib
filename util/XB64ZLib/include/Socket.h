// Socket.h: interface for the Socket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOCKET_H__66DF4261_8EB9_459B_804C_8F172880BF98__INCLUDED_)
#define AFX_SOCKET_H__66DF4261_8EB9_459B_804C_8F172880BF98__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/// namespace stream
namespace stream
{

/// namespace exceptions
namespace exceptions
{
/**
	Socket exception.
*/
class SocketStreamException : public StreamException
{
public:
	SocketStreamException();
};

} // namespace exceptions

/**
Provides the classes for implementing networking applications. 
*/
namespace net
{

class SocketOptions
{
public:
	SocketOptions()
	{
		m_recvBuf = -1;
		m_sendBuf = -1;
		m_recvTimeOut = -1;
		m_sendTimeOut = -1;
		m_tcpNoDelay = FALSE;
	}

	int m_recvBuf;
	int m_sendBuf;

	int m_recvTimeOut;
	int m_sendTimeOut;
	BOOL m_tcpNoDelay;

	void setSockOpt(SOCKET& sock);
	void getSockOpt(SOCKET& sock);
};
enum SockProto{SP_TCP,SP_UDP,SP_RAW};

/**
	This class implements client sockets (also called just "sockets"). A socket is an endpoint for communication between two machines. 
	Sample:
	<code>
	Socket sock("localhost","9090");<br>
<br>
	IOutputStream* output = sock.getOutputStream();<br>
	IInputStream* input = sock.getInputStream();<br>
<br>
	unsigned char buff[1000];<br>
	unsigned int readed = input->read(buff,1000);
	</code>
*/
class Socket
{
public:

	/**
		Creates a socket and connects it to the specified remote address on the specified remote port. 
		The Socket will also bind() to the local address and port supplied. 
	*/
	Socket(std::string host,std::string port,std::string bind_ip = "",std::string bind_port = "1",SockProto proto = SP_TCP,SocketOptions* options = 0)throw(exceptions::SocketStreamException*);

	/**
		Destructor.
	*/
	virtual ~Socket();

	/**
		Closes this socket.
	*/
	void close();

	void setSocketOptions(SocketOptions& prop);
	void getSocketOptions(SocketOptions& prop);

	/**
		Returns the address to which the socket is connected
		@return The connected ip.
	*/
	std::string getInetAddress()throw(exceptions::SocketStreamException*);

	/**
		Gets the local address to which the socket is bound. 
		@return The bound ip.
	*/
	std::string getLocalAddress()throw(exceptions::SocketStreamException*);

	/**
		Return a string where is set the local ip and port and the bound ip and port.
		@return The connection string.
	*/
	std::string getConnectionString()throw(exceptions::SocketStreamException*);

	/**
		Returns the remote port to which this socket is connected.
		@return Remote port.
	*/
	unsigned int getPort()throw(exceptions::SocketStreamException*);

	/**
		Returns the local port to which this socket is bound.
		@return Bound port.
	*/
	unsigned int getLocalPort()throw(exceptions::SocketStreamException*);

	/**
		@return the output stream of the socket.
	*/
	io::IOutputStream* getOutputStream();

	/**
		@return the input stream of the socket.
	*/
	io::IInputStream* getInputStream();


	/**
		@return the host name.
	*/
	static std::string getHostName();

	/** 
		Release the ownership of the socket handle. This handle will not be disposed by this object.
		@return the socket handle.
	*/
	SOCKET ReleaseSocketHandle();


private:
	friend class ServerSocket;
	Socket(SOCKET s,int socket_type);  // Constructor para la clase CServerSocket
	
	
	class Internal_InputStream : public io::IInputStream
	{
	public:
		Internal_InputStream(Socket* parent);

		//Returns the number of bytes that can be read (or skipped over) from this input stream without blocking by the next caller of a method for this input stream. 
		virtual int available();
		//Closes this input stream and releases any system resources associated with the stream. 
		virtual void close();
		//Marks the current position in this input stream. 
		virtual void mark(int readlimit);          
		//Tests if this input stream supports the mark and reset methods. 
		virtual bool markSupported();
		//Reads the next byte of data from the input stream. 
		virtual int read()throw(exceptions::SocketStreamException*);
		//Reads some number of bytes from the input stream and stores them into the buffer array b. 
		virtual int read(unsigned char* b,long length)throw(exceptions::SocketStreamException*);
		//Reads up to len bytes of data from the input stream into an array of bytes. 
		virtual int read(unsigned char* b, int off, int len)throw(exceptions::SocketStreamException*);
		//Repositions this stream to the position at the time the mark method was last called on this input stream. 
		virtual void reset();
		//Skips over and discards n bytes of data from this input stream. 
		virtual long skip(long n)throw(exceptions::SocketStreamException*);

	private:
		Socket* m_parent;
	}m_Internal_InputStream;
	class Internal_OutputStream : public io::IOutputStream
	{
	public:
		Internal_OutputStream(Socket* parent);

		//Closes this output stream and releases any system resources associated with this stream. 
		virtual void close();
		//Flushes this output stream and forces any buffered output bytes to be written out. 
		virtual void flush();
		//Writes b.length bytes from the specified byte array to this output stream. 
		virtual void write(unsigned char* b,long length)throw(exceptions::SocketStreamException*);
		//Writes len bytes from the specified byte array starting at offset off to this output stream. 
		virtual void write(unsigned char* b, int off, int len)throw(exceptions::SocketStreamException*);
		//Writes the specified byte to this output stream. 
		virtual void write(int b)throw(exceptions::SocketStreamException*);

	private:
		Socket* m_parent;
	}m_Internal_OutputStream;

	class Internal_InputStream_udp : public io::IInputStream
	{
	public:
		Internal_InputStream_udp(Socket* parent);

		//Returns the number of bytes that can be read (or skipped over) from this input stream without blocking by the next caller of a method for this input stream. 
		virtual int available();
		//Closes this input stream and releases any system resources associated with the stream. 
		virtual void close();
		//Marks the current position in this input stream. 
		virtual void mark(int readlimit);          
		//Tests if this input stream supports the mark and reset methods. 
		virtual bool markSupported();
		//Reads the next byte of data from the input stream. 
		virtual int read()throw(exceptions::SocketStreamException*);
		//Reads some number of bytes from the input stream and stores them into the buffer array b. 
		virtual int read(unsigned char* b,long length)throw(exceptions::SocketStreamException*);
		//Reads up to len bytes of data from the input stream into an array of bytes. 
		virtual int read(unsigned char* b, int off, int len)throw(exceptions::SocketStreamException*);
		//Repositions this stream to the position at the time the mark method was last called on this input stream. 
		virtual void reset();
		//Skips over and discards n bytes of data from this input stream. 
		virtual long skip(long n)throw(exceptions::SocketStreamException*);

	private:
		Socket* m_parent;
	}m_Internal_InputStream_udp;
	class Internal_OutputStream_udp : public io::IOutputStream
	{
	public:
		Internal_OutputStream_udp(Socket* parent);

		//Closes this output stream and releases any system resources associated with this stream. 
		virtual void close();
		//Flushes this output stream and forces any buffered output bytes to be written out. 
		virtual void flush();
		//Writes b.length bytes from the specified byte array to this output stream. 
		virtual void write(unsigned char* b,long length)throw(exceptions::SocketStreamException*);
		//Writes len bytes from the specified byte array starting at offset off to this output stream. 
		virtual void write(unsigned char* b, int off, int len)throw(exceptions::SocketStreamException*);
		//Writes the specified byte to this output stream. 
		virtual void write(int b)throw(exceptions::SocketStreamException*);

	private:
		Socket* m_parent;
	}m_Internal_OutputStream_udp;


	friend Socket::Internal_InputStream;
	friend Socket::Internal_OutputStream;
	friend Socket::Internal_InputStream_udp;
	friend Socket::Internal_OutputStream_udp;
	SOCKET m_sock;
	sockaddr_in m_sock_in;
	int m_socket_type;
};

/**
	Socket automatic pointer.
*/
typedef std::auto_ptr<Socket> SocketPtr;

} // namespace net

}
#endif // !defined(AFX_SOCKET_H__66DF4261_8EB9_459B_804C_8F172880BF98__INCLUDED_)
