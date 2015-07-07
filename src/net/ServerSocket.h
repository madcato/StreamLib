// ServerSocket.h: interface for the ServerSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERVERSOCKET_H__2034B871_A72A_4F99_9CB0_4DBACB187B4B__INCLUDED_)
#define AFX_SERVERSOCKET_H__2034B871_A72A_4F99_9CB0_4DBACB187B4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/// namespace stream
namespace stream
{
/**
Provides the classes for implementing networking applications. 
*/
namespace net
{

/**
	This class implements server sockets. A server socket waits for requests to come in over the network.
	It performs some operation based on that request, and then possibly returns a result to the requester. 
	Sample:
	<code>
		ServerSocket server("80");<br>
		<br>
		SocketPtr socket(server.accept());<br>
<br>
		IInputStream* input = socket->getInputStream();<br>
<br>
		unsigned char buff[1000];<br>
		unsigned int readed = input->read(buff,1000);
	</code>
*/
class ServerSocket
{
public:
	/**
		Create a server with the specified port, and local IP address to bind to. 
		If bind_ip is null, it will default accepting connections on any/all local addresses. 
		The port must be between 0 and 65535, inclusive. 
	*/
	ServerSocket(std::string port,std::string bind_ip = "",SockProto proto = SP_TCP)throw(exceptions::SocketStreamException*);

	/**
		Destructor.
	*/
	virtual ~ServerSocket();

	/**
		Listens for a connection to be made to this socket and accepts it. The method blocks until a connection is made. 
		@param seconds Number of second to wait for an incoming connection.
		@return The new socket created or zero if time limit expired.
	*/
	Socket* accept(long seconds = INFINITE)throw(exceptions::SocketStreamException*);

	/**
		Checks if new incoming connection is present in this socket.
		@param miliseconds Waiting time in  seconds.
		@return true if a new connection is waiting.
	*/
	bool isThereNewConnection(long seconds);

	/**
		Closes this socket.
	*/
	void close();



private:
	SOCKET m_sock;

	int m_socket_type;


};

/**
	ServerSocket automatic pointer.
*/
typedef std::auto_ptr<ServerSocket> ServerSocketPtr;
} // namespace net

} // namespace stream
#endif // !defined(AFX_SERVERSOCKET_H__2034B871_A72A_4F99_9CB0_4DBACB187B4B__INCLUDED_)
