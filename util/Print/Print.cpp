// Print.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		console << "Usage: dprint.exe <file> <printer>";
		return -1;
	}

	try
	{
		FileInputStream file(argv[1]);

		HANDLE hPrinter = 0;
		if(!OpenPrinter(argv[2],&hPrinter,0))
			throw exceptions::Win32ErrorException(__FILE__,__LINE__);

		DOC_INFO_1 docInfo;
		docInfo.pDocName = "print"; 
		docInfo.pOutputFile = 0;
		docInfo.pDatatype = 0;

		if(!StartDocPrinter(hPrinter, 1, (uchar*)&docInfo))
			throw exceptions::Win32ErrorException(__FILE__,__LINE__);

		if(!StartPagePrinter(hPrinter))
			throw exceptions::Win32ErrorException(__FILE__,__LINE__);

		uchar buffer[4096];

		while(file.available())
		{
			ulong readed = file.read(buffer,4096);
			ulong written;
			if(!WritePrinter(hPrinter,buffer,readed,&written))
				throw exceptions::Win32ErrorException(__FILE__,__LINE__);
		}

		if(!EndPagePrinter(hPrinter))
			throw exceptions::Win32ErrorException(__FILE__,__LINE__);

		if(!EndDocPrinter(hPrinter))
			throw exceptions::Win32ErrorException(__FILE__,__LINE__);

	}catch(exception* e)
	{
		console << e->what() << endln;
	}

	return 0;
}
