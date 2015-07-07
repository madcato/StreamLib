// NetCommandServer.cpp: implementation of the NetCommandServer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Exceptions.h"
#include "IInputStream.h"
#include "IOutputStream.h"
#include "Socket.h"
#include "ServerSocket.h"

#include "NetCommandServer.h"

#include "BufferedReader.h"
#include "PrintWriter.h"
#include "Tokenizer.h"
#include "Date.h"
#include "stringUtil.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/// namespace stream
namespace stream
{

/// namespace net
namespace net
{

NetCommandServer::NetCommandServer(const std::string& listen_port,const std::string& listen_ip)
{
	m_server = ServerSocketPtr(new ServerSocket(listen_port,listen_ip,SP_TCP));
}

NetCommandServer::~NetCommandServer()
{

}

std::string NetCommandServer::waitForCommand()
{
	SocketPtr socket(m_server->accept());

	io::BufferedReader reader(socket->getInputStream());
	io::PrintWriter printer(socket->getOutputStream());

	
	std::string command = reader.readLine();

	
	std::string id = command.substr(0,4);
	std::string message = command.substr(4);

	if(id != "CMD ")
	{
		printer.println("-ERR Invalid protocol");
		return "";
	}
	else
	{
		printer.println("+OK");
	}

	return message;
}



bool NetCommandServer::sendCommand(const std::string& command, const std::string& ip, const std::string& port)
{
	Socket socket(ip,port,"","1",SP_TCP);

	io::BufferedReader reader(socket.getInputStream());
	io::PrintWriter printer(socket.getOutputStream());

	printer.println("CMD " + command);
	
	std::string response = reader.readLine();
	if(response == "+OK")
		return true;

	return false;
}

} // namespace net

} // namespace stream
