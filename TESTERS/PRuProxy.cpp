// PRuProxy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include "f:\miscos\stream\Exceptions.h"
#include "f:\miscos\stream\IInputStream.h"
#include "f:\miscos\stream\IOutputStream.h"
#include "f:\miscos\stream\Socket.h"
#include "f:\miscos\stream\SocksifiedSocket.h"

using namespace Stream;
using namespace std;



string GetProxyTypeDesc(CSocksifiedSocket::EProxyType type)
{
	switch(type)
	{
	case CSocksifiedSocket::PROXYTYPE_NOPROXY:
		return "NO-PROXY";
	case CSocksifiedSocket::PROXYTYPE_SOCKS4:
		return "PROXY_SOCKS4";
	case CSocksifiedSocket::PROXYTYPE_SOCKS5:
		return "PROXY_SOCKS5";
	case CSocksifiedSocket::PROXYTYPE_CONNECT:
		return "PROXY_HTTP";
	default:
		return "UNKNOWN_PROXY";
	};
}
void Test(CSocksifiedSocket::EProxyType type,string dest_ip,string dest_port,string server_proxy,string port_proxy,string login,string password)
{
	try
	{
		CSocksifiedSocket ss;

		ss.SetProxy(type,server_proxy,port_proxy,login,password);

		if(ss.ConnectTo(dest_ip,dest_port))
		{
			auto_ptr<CSocket>sock = ss.GetSocket();
			IInputStream* i = sock->getInputStream();
			IOutputStream* o = sock->getOutputStream();

			o->write((unsigned char*)"Data received OK.",17);
			char buffer[100];
			int readed = i->read((unsigned char*)buffer,99);
			
			buffer[readed] = '\0';

			cout << endl << "OK: " << GetProxyTypeDesc(type) << ":" << login << " : " << buffer <<endl;
		}
		else
		{
			cout << endl << "FAIL: " << GetProxyTypeDesc(type) << ":" << login << endl;
		}
	}catch(Exceptions::StreamException* e)
	{

		cout << endl << "ERROR: " << GetProxyTypeDesc(type) << ":" << login << " : " << e->GetDesc() << endl;
	}
}

// Host destino
#define DEST_IP_GOOD "localhost"
// Puerto destino
#define DEST_PORT_GOOD "7"
// Puerto destino incorrecto
#define DEST_PORT_BAD "1"

// Host proxy
#define PROXY_IP_GOOD "localhost"
// Puerto de escucha del servidor proxy con SOCKS4
#define PROXY_4_PORT_GOOD "1080"
// Puerto de escucha del servidor proxy con SOCKS5
#define PROXY_5_PORT_GOOD "1080"
// Puerto de escucha del servidor proxy con HTTP
#define PROXY_C_PORT_GOOD "8080"

// Puerto de escucha del servidor proxy con SOCKS4 incorrecto
#define PROXY_4_PORT_BAD "1090"
// Puerto de escucha del servidor proxy con SOCKS5 incorrecto
#define PROXY_5_PORT_BAD "1090"
// Puerto de escucha del servidor proxy con HTTP incorrecto
#define PROXY_C_PORT_BAD "8090"



int main(int argc, char* argv[])
{
	// Procondiciones de testeo.

	// Es necesario tener instalado el servicio echo(puerto 7) en localhost.
	// Es necesario tener un proxy en el puerto 8080 de tipo http  en localhost.
	// Es necesario tener un proxy SOCKS4 y SOCKS5 en el puerto 1080 en localhost.



	Test(CSocksifiedSocket::PROXYTYPE_NOPROXY,DEST_IP_GOOD,DEST_PORT_GOOD,DEST_IP_GOOD,DEST_PORT_GOOD,"","");
	
	// Conexiones correctas
	cout << "Conexiones correctas: " << endl;
	Test(CSocksifiedSocket::PROXYTYPE_SOCKS4,DEST_IP_GOOD,DEST_PORT_GOOD,PROXY_IP_GOOD,PROXY_4_PORT_GOOD,"","");
	Test(CSocksifiedSocket::PROXYTYPE_SOCKS5,DEST_IP_GOOD,DEST_PORT_GOOD,PROXY_IP_GOOD,PROXY_5_PORT_GOOD,"","");
	Test(CSocksifiedSocket::PROXYTYPE_CONNECT,DEST_IP_GOOD,DEST_PORT_GOOD,PROXY_IP_GOOD,PROXY_C_PORT_GOOD,"","");

	// Conexiones correctas autenticadas
	cout << "Conexiones correctas autenticadas: " << endl;
//	Test(CSocksifiedSocket::PROXYTYPE_SOCKS4,DEST_IP_GOOD,DEST_PORT_GOOD,PROXY_IP_GOOD,PROXY_PORT_GOOD,"MadCat","remote");
//	Test(CSocksifiedSocket::PROXYTYPE_SOCKS5,DEST_IP_GOOD,DEST_PORT_GOOD,PROXY_IP_GOOD,PROXY_PORT_GOOD,"MadCat","remote");
//	Test(CSocksifiedSocket::PROXYTYPE_CONNECT,DEST_IP_GOOD,DEST_PORT_GOOD,"localhost","81","MadCat","remote");
	

	// Conexiones al proxy fallidas
	cout << "Conexiones al proxy fallidas: " << endl;
	Test(CSocksifiedSocket::PROXYTYPE_SOCKS4,DEST_IP_GOOD,DEST_PORT_GOOD,PROXY_IP_GOOD,PROXY_4_PORT_BAD,"","");
	Test(CSocksifiedSocket::PROXYTYPE_SOCKS5,DEST_IP_GOOD,DEST_PORT_GOOD,PROXY_IP_GOOD,PROXY_5_PORT_BAD,"","");
	Test(CSocksifiedSocket::PROXYTYPE_CONNECT,DEST_IP_GOOD,DEST_PORT_GOOD,PROXY_IP_GOOD,PROXY_C_PORT_BAD,"","");

	// Conexiones al proxy correctas, a destino fallidas
	cout << "Conexiones correctas, a destino fallidas: " << endl;
	Test(CSocksifiedSocket::PROXYTYPE_SOCKS4,DEST_IP_GOOD,DEST_PORT_BAD,PROXY_IP_GOOD,PROXY_4_PORT_GOOD,"","");
	Test(CSocksifiedSocket::PROXYTYPE_SOCKS5,DEST_IP_GOOD,DEST_PORT_BAD,PROXY_IP_GOOD,PROXY_5_PORT_GOOD,"","");
	Test(CSocksifiedSocket::PROXYTYPE_CONNECT,DEST_IP_GOOD,DEST_PORT_BAD,PROXY_IP_GOOD,PROXY_C_PORT_GOOD,"","");


	return 0;
}
