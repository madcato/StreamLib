// NetCommandServer.h: interface for the NetCommandServer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NETCOMMANDSERVER_H__D6CD0081_DE3C_4C74_A410_C3912440E860__INCLUDED_)
#define AFX_NETCOMMANDSERVER_H__D6CD0081_DE3C_4C74_A410_C3912440E860__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{

/// namespace net
namespace net
{

/** 
	This class waits for commands that receive in sockets.
	Protocol:
	(S is the sender, R the receiver)

	S -> CMDN <command>\r\n -> R
	R -> +OK\r\n -> S or R -> -ERR <error_text>\r\n -> S
	Then, the client and/or the server must close the socket connection.

	Every line is finished with a \r\n(0x0D 0x0A).
	The text identifiers can be lowercase or uppercase("cmdn","CMDN").
	In addition can be possible any combination of lowercase and uppercase("CmDn","cmDN").

	Errors:
	- Invalid protocol. This error is produced when the line doesn't start with "CMDN"


	This class is not designed for applications that require a large amount of commands.
	This is because every command send require a new connection. Use only for simple commands
	like: "SHUTDOWN", "RESTART", "STOP", "CONFIGURE", "WAKEUP", "SLEEP", etc
*/
class NetCommandServer
{
public:
	/**
		@param listen_port Port to listen for commands.
	*/
	NetCommandServer::NetCommandServer(const std::string& listen_port,const std::string& listen_ip);
	virtual ~NetCommandServer();
	
	/**
		Waits for a connection and listen the command
		@return The received comman. Return empty string if found an error.
	*/
	std::string waitForCommand();

	static bool sendCommand(const std::string& command, const std::string& ip, const std::string& port);

private:
	ServerSocketPtr m_server;
};

/**
	NetCommandServer automatic pointer.
*/
typedef std::auto_ptr<NetCommandServer> NetCommandServerPtr;

} // namespace net

} // namespace stream

#endif // !defined(AFX_NETCOMMANDSERVER_H__D6CD0081_DE3C_4C74_A410_C3912440E860__INCLUDED_)
