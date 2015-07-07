// TestEmail.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main(int argc, char* argv[])
{

//	Beep( 750, 300 );
//	Beep( 1750, 300 );
	try
	{
		Log log;

		//log.traceOn("c:\\temp\\log.log",CREATE_NEW_LOG);
		log.traceOn("c:\\con",CREATE_NEW_LOG);
		//log.traceOn("socket://localhost:8100",CREATE_NEW_LOG);
setlocale(LC_ALL,"Spanish");

		unsigned char e = 'é';

		log.trace("Startóá");
		if(argc != 5)
		{
			cerr << "Invalid parameters." << endl << "Usage: TestEmail.exe <server> <port> <user> <password>" << endl;
			return -10;
		}
		Socket sock(argv[1],argv[2]);

		IOutputStream* output = sock.getOutputStream();
		IInputStream* input = sock.getInputStream();

		unsigned char buff[1001];
		unsigned int readed = input->read(buff,1000);
		
		buff[readed] = '\0';
		log.trace(std::string("< ") + (char*)buff);
		if(memcmp(buff,"+OK",3))
		{
			cerr << buff << endl;

			return -1;
		}

		
		string user = string("USER ") + argv[3] + string("\r\n");
		output->write((unsigned char*)user.c_str(),user.length());
		log.trace("> " + user);
		readed = input->read(buff,1000);

		buff[readed] = '\0';
		log.trace(std::string("< ") + (char*)buff);
		if(memcmp(buff,"+OK",3))
		{
			cerr << buff << endl;

			return -2;
		}
		


		string pass = string("PASS ") + CCaesar::UnOfuscate(argv[4]) + string("\r\n");
		output->write((unsigned char*)pass.c_str(),pass.length());
		log.trace("> " + pass);

		readed = input->read(buff,1000);

		buff[readed] = '\0';
		log.trace(std::string("< ") + (char*)buff);
		if(memcmp(buff,"+OK",3))
		{
			cerr << buff << endl;

			return -3;
		}

		string stat = string("STAT") + string("\r\n");
		output->write((unsigned char*)stat.c_str(),stat.length());
		log.trace("> " + stat);

		readed = input->read(buff,1000);

		buff[readed] = '\0';
		log.trace(std::string("< ") + (char*)buff);
		if(memcmp(buff,"+OK",3))
		{
			cerr << buff << endl;

			return -4;
		}
		else
		{
			cout << buff + 4 << endl;
		}




		log.trace("End");

	}
	catch(exception* e)
	{
		cerr << e->what() << endl;
	}
	catch(exception e)
	{
		cerr << e.what() << endl;
	}
	catch(...)
	{
		cerr << "Unknown exception." << endl;
	}

	

	return 0;
}
