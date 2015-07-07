// AdvSockServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define MAX_PENDING_CONNECTS 100

enum ESockType
{
	ST_LISTEN,
	ST_ACCEPTED
};
class SocketData
{
public:
	SOCKET m_socket;
	int m_port;
	ESockType m_type;
	Blob<char> m_receivedData;
};

SocketData** g_vectorSockets;

vector<SOCKET> g_listenSockets;



class AdvSocketListener
{
public:
	AdvSocketListener()
	{
		WSADATA		wsd;
		WSAStartup(MAKEWORD(2,2),&wsd);

		
	}

	~AdvSocketListener()
	{
		WSACleanup();
	}

	SOCKET listen(int puerto)
	{
		SOCKET sock = socket(AF_INET,SOCK_STREAM,0);
		SOCKADDR_IN local_sin;              // Local socket address
		local_sin.sin_family = AF_INET;		
		local_sin.sin_addr.s_addr = htonl (INADDR_ANY);
		local_sin.sin_port = htons (puerto);  

		::bind(sock, 
			(struct sockaddr *) &local_sin, 
			sizeof (local_sin));

		::listen(sock, MAX_PENDING_CONNECTS);

		// Convertir a socket no bloqueante.
		ulong b = 1;
		ioctlsocket(sock,FIONBIO,&b);

		g_listenSockets.push_back(sock);

		return sock;
	}

	void listen(const vector<string>& vectorPuertos)
	{
		vector<string>::const_iterator it;

		for(it = vectorPuertos.begin(); it != vectorPuertos.end() ; it++)
		{
			int puerto = (ulong)sstring(*it);
			SOCKET s = listen(puerto);
			SocketData* sd = new SocketData;
			sd->m_socket = s;
			sd->m_port = puerto;
			sd->m_type = ST_LISTEN;

			g_vectorSockets[s] = sd;
			
		}
	}


	void accept()
	{
		do
		{
			vector<SOCKET>::iterator it;

			FD_ZERO(&m_readfds);
			FD_ZERO(&m_writefds);
			FD_ZERO(&m_exceptfds);

			for(it = g_listenSockets.begin() ; it != g_listenSockets.end() ; it++)
			{
				FD_SET(*it,&m_readfds);
			}

			int ret = ::select(0,&m_readfds,&m_writefds,&m_exceptfds,0);

			if(ret == SOCKET_ERROR)
			{
				int a = 0;
				return;
			}

			for(it = g_listenSockets.begin() ; it != g_listenSockets.end() && ret ; it++)
			{
				if(FD_ISSET(*it,&m_readfds))
				{
					ret--;
					switch(g_vectorSockets[*it]->m_type)
					{
					case ST_ACCEPTED:
						{
							char buffer[1000];
							int readed = recv(*it,buffer,1000,0);

							if(readed == 0)
							{
								// Se ha cerrado.
								g_listenSockets.erase(it);
								delete g_vectorSockets[*it];
								g_vectorSockets[*it] = 0;
							}
							else
							{
								g_vectorSockets[*it]->m_receivedData.attach(buffer,readed);
							}
							break;
						}
					case ST_LISTEN:
						{
							SOCKADDR_IN addr;
							int len = sizeof(SOCKADDR_IN);
							SOCKET s = ::accept(*it,(struct sockaddr *)&addr,&len);

							if(s == INVALID_SOCKET)
							{
								DWORD err = WSAGetLastError();

								char message[1000];
								int length = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,0,err,0,message,1000,NULL);

							}
							else
							{
								// El socket ha sido aceptado.
								
								g_vectorSockets[s] = new SocketData;
								g_vectorSockets[s]->m_socket = s;
								g_vectorSockets[s]->m_port = addr.sin_port;
								g_vectorSockets[s]->m_type = ST_ACCEPTED;

								g_listenSockets.push_back(s);
							}
						}
						break;
					}
				}
			}
		}while(true);
	}


private:
	fd_set m_readfds;
	fd_set m_writefds;
	fd_set m_exceptfds;

};

int main(int argc, char* argv[])
{
	g_vectorSockets = new SocketData*[65536];

	vector<string> data;

	data.push_back("8001");
	data.push_back("8002");
	data.push_back("8003");

	AdvSocketListener adv;

	adv.listen(data);

	adv.accept();
	return 0;
}
