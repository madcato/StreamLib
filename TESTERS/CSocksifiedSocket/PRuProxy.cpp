// PRuProxy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include "Exceptions.h"
#include "IInputStream.h"
#include "IOutputStream.h"
#include "Socket.h"
#include "SocksifiedSocket.h"

using namespace Stream;
using namespace std;


class LoginPass : public IProxyAuthData
{
	void GetAuthData(std::string& login, std::string& password)
	{
		login = "prueba";
		password = "prueba";
	}
};

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
int Test(CSocksifiedSocket::EProxyType type,string dest_ip,string dest_port,string server_proxy,string port_proxy,string login,string password)
{
	CSocksifiedSocket ss("ProxyTest",std::auto_ptr<IProxyAuthData>((IProxyAuthData*)new LoginPass()));
	try
	{
		

		ss.SetProxy(type,server_proxy,port_proxy,login,password);

		ss.ConnectTo(dest_ip,dest_port);
		auto_ptr<CSocket>sock = ss.GetSocket();
		IInputStream* i = sock->getInputStream();
		IOutputStream* o = sock->getOutputStream();

		o->write((unsigned char*)"Data received OK.",17);
		/*char buffer[100];
		int readed = i->read((unsigned char*)buffer,99);
		
		buffer[readed] = '\0';*/

		cout << "OK: " << GetProxyTypeDesc(type) << ":" << login << " : " << endl;
	
	}
	catch(Exceptions::ProxyException* e)
	{
		cout << endl << "ERROR_PROXY: " << GetProxyTypeDesc(type) << ":" << login << " : " << e->GetDesc() << endl;
		cout << ss.GetLastResponse() << endl;


#define ERR_CREATING_SOCKET									-1001
// PROXY
#define ERR_PROXY_CONNECT									-1002
#define ERR_HOST_RESOLUTION									-1003
#define ERR_SOCKS4_CONNECT									-1008
#define ERR_SOCKS4_RESPONSE									-1009
#define ERR_SOCKS5_CONNECT									-1013
#define ERR_SOCKS5_RESPONSE									-1014
#define	ERR_NO_PASSWORD_FUNCTION							-1010
#define ERR_NO_INPUT_PASSWORD								-1011
#define ERR_PROXY_ERROR_RESPONSE							-1012


		switch(e->GetIdError())
		{
		case Exceptions::PROXYERROR_NOCONN:
			return ERR_PROXY_CONNECT;
			break;
		case Exceptions::PROXYERROR_REQUESTFAILED:
			// Fallo en el request.			
			// response
			return ERR_PROXY_ERROR_RESPONSE;
			break;
		case Exceptions::PROXYERROR_AUTHREQUIRED:
			// Autenticación requerida
			// response
			return ERR_PROXY_ERROR_RESPONSE;
			break;
		case Exceptions::PROXYERROR_AUTHTYPEUNKNOWN:
			// Tipo de autenticación desconocida
			return ERR_SOCKS5_RESPONSE;
			break;
		case Exceptions::PROXYERROR_AUTHFAILED:
			// Autenticación fallida.
			// response
			return ERR_PROXY_ERROR_RESPONSE;
			break;
		case Exceptions::PROXYERROR_AUTHNOLOGON:
			// Autenticación requerida
			// response
			return ERR_PROXY_ERROR_RESPONSE;
			break;
		default:
			return -1;
			break;
		};
	}
	catch(Exceptions::StreamException* e)
	{
		cout << endl << "ERROR_STREAM: " << e->GetDesc() << endl;		
	}

	return ss.GetSocket()->ReleaseSocketHandle();
}

// Host destino
#define DEST_IP_GOOD "www.microsoft.com"
// Puerto destino
#define DEST_PORT_GOOD "80"
// Puerto destino incorrecto
#define DEST_PORT_BAD "1"

// Host proxy
#define PROXY_IP_GOOD "dirac"
// Puerto de escucha del servidor proxy con SOCKS4
#define PROXY_4_PORT_GOOD "8080"
// Puerto de escucha del servidor proxy con SOCKS5
#define PROXY_5_PORT_GOOD "8080"
// Puerto de escucha del servidor proxy con HTTP
#define PROXY_C_PORT_GOOD "4435"

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



	//Test(CSocksifiedSocket::PROXYTYPE_NOPROXY,DEST_IP_GOOD,DEST_PORT_GOOD,DEST_IP_GOOD,DEST_PORT_GOOD,"","");
	
	// Conexiones correctas
	cout << endl << "Conexiones correctas: " << endl;
//	Test(CSocksifiedSocket::PROXYTYPE_SOCKS4,DEST_IP_GOOD,DEST_PORT_GOOD,PROXY_IP_GOOD,PROXY_4_PORT_GOOD,"","");
//	Test(CSocksifiedSocket::PROXYTYPE_SOCKS5,DEST_IP_GOOD,DEST_PORT_GOOD,PROXY_IP_GOOD,PROXY_5_PORT_GOOD,"","");
	Test(CSocksifiedSocket::PROXYTYPE_CONNECT,DEST_IP_GOOD,DEST_PORT_GOOD,PROXY_IP_GOOD,PROXY_C_PORT_GOOD,"","");

	// Conexiones correctas autenticadas
	cout << endl << "Conexiones correctas autenticadas: " << endl;
	//Test(CSocksifiedSocket::PROXYTYPE_SOCKS4,DEST_IP_GOOD,DEST_PORT_GOOD,PROXY_IP_GOOD,PROXY_4_PORT_GOOD,"prueba","prueba");
	//Test(CSocksifiedSocket::PROXYTYPE_SOCKS5,DEST_IP_GOOD,DEST_PORT_GOOD,PROXY_IP_GOOD,PROXY_5_PORT_GOOD,"prueba","prueba");
	Test(CSocksifiedSocket::PROXYTYPE_CONNECT,DEST_IP_GOOD,DEST_PORT_GOOD,PROXY_IP_GOOD,PROXY_C_PORT_GOOD,"","");
	

	// Conexiones al proxy fallidas
	cout << endl << "Conexiones al proxy fallidas: " << endl;
//	Test(CSocksifiedSocket::PROXYTYPE_SOCKS4,DEST_IP_GOOD,DEST_PORT_GOOD,PROXY_IP_GOOD,PROXY_4_PORT_BAD,"","");
//	Test(CSocksifiedSocket::PROXYTYPE_SOCKS5,DEST_IP_GOOD,DEST_PORT_GOOD,PROXY_IP_GOOD,PROXY_5_PORT_BAD,"","");
	Test(CSocksifiedSocket::PROXYTYPE_CONNECT,DEST_IP_GOOD,DEST_PORT_GOOD,PROXY_IP_GOOD,PROXY_C_PORT_BAD,"","");

	// Conexiones al proxy correctas, a destino fallidas
	cout << endl << "Conexiones correctas, a destino fallidas: " << endl;
	//Test(CSocksifiedSocket::PROXYTYPE_SOCKS4,DEST_IP_GOOD,DEST_PORT_BAD,PROXY_IP_GOOD,PROXY_4_PORT_GOOD,"","");
	//Test(CSocksifiedSocket::PROXYTYPE_SOCKS5,DEST_IP_GOOD,DEST_PORT_BAD,PROXY_IP_GOOD,PROXY_5_PORT_GOOD,"","");
	Test(CSocksifiedSocket::PROXYTYPE_CONNECT,DEST_IP_GOOD,DEST_PORT_BAD,PROXY_IP_GOOD,PROXY_C_PORT_GOOD,"","");


	return 0;
}
