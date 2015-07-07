// unzip.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		csout << "Usage: unzip <zipped_file>\r\n";
		return -1;
	}

	try
	{
		string tempFilename = FileUtil::getTempFileName();
	
		zip::GZInputStream zin(argv[1]);



		Tar t;

		t.RunExtract(&zin,".");

		zin.close();

	}catch(exception* e)
	{
		csout << e->what() << "\r\n";
		return -1;
	}
	return 0;
}
