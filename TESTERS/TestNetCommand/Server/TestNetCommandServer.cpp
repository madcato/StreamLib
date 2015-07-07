// TestNetCommandServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main(int argc, char* argv[])
{
	try
	{
		NetCommandServer server("1010","localhost");

		string command = "";
		do
		{
			command = server.waitForCommand();
			cout << command << endl;
		}while(command != "QUIT");
	}catch(stream::exceptions::StreamException* e)
	{
		cerr << e->what() << endl;
	}
	return 0;
}
