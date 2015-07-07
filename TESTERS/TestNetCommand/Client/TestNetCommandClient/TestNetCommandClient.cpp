// TestNetCommandClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main(int argc, char* argv[])
{

	try
	{
		if(NetCommandServer::sendCommand("Hola","localhost","1010"))
		{
			cout << "Command send" << endl;
		}
	}catch(stream::exceptions::StreamException* e)
	{
		cerr << e->what() << endl;
	}
	return 0;
}
