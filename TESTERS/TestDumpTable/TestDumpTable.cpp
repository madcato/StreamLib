// TestDumpTable.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main(int argc, char* argv[])
{
	INIT_COM();

	try
	{
		DB::init(argv[1]);

		//DB::unloadTableToFile("textos","1:id:int(11),2:idJob:int(11),3:texto:varchar(255)","textos.txt",true);

		DB::loadFileToTable("textos.txt","textos","1:id:int(11),2:idJob:int(11),3:texto:varchar(255)",true);
		
		
  	


	}catch(exceptions::StreamException* e)
	{
		console << e->what() << endln;
	}
	return 0;
}

