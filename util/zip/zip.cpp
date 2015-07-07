// zip.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main(int argc, char* argv[])
{

	if(argc != 3)
	{
		csout << "Usage: zip <directory_to_zip> <output_file>\r\n";
		return -1;
	}

	try
	{
		string tempFilename = FileUtil::getTempFileName();

		string pathToZip = argv[1];

	

		Tar t;

		t.RunAdd(tempFilename,pathToZip);

		FileInputStream fin(tempFilename);

		
		zip::GZOutputStream zout(argv[2]);

		uchar buffer[512 * 512];
		ulong readed = 0;
		while(fin.available())
		{
			readed = fin.read(buffer,512 * 512);
			zout.write(buffer,readed);
		}

		zout.close();
		fin.close();

		FileUtil::deleteFile(tempFilename);
	}catch(exception* e)
	{
		csout << e->what() << "\r\n";
		return -1;
	}
	return 0;
}
