// WebServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main(int argc, char* argv[])
{
	CoInitialize(0);
	try
	{
		FreeConsole();

		
		if(argc != 2)
		{
			console << "Usage. WebServer <DB_INIT>";
		}
		else
		{

			DB::init(argv[1]);	// "Provider=SQLOLEDB;Database=TODOlist;Server=localhost;uid=todouser;pwd=todouser"
								// "DRIVER={MySQL ODBC 3.51 Driver};SERVER=localhost;DATABASE=emailservice;USER=;PASSWORD=;OPTION=3;"
			WebApp web;

			web.run();
		}
	}
	catch(exceptions::StreamException* e)
	{
		console << e->what();
	}
	CoUninitialize();

	return 0;
}
