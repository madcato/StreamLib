// File2BufferTester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Exceptions.h"
#include "memory_stream.h"
#include "Blob.h"
#include "FileUtil.h"
#include "IInputStream.h"
#include "IOutputStream.h"
#include "BLOBInputStream.h"
#include "BLOBOutputStream.h"

#include <iostream>

using namespace Stream;
using namespace std;

int main(int argc, char* argv[])
{
	try
	{
		Stream::Blob<char> buffer = FileUtil::File2Buffer("d:\\temp\\php.ini");

		FileUtil::Buffer2File(buffer,"d:\\temp\\php2.ini");


		Stream::Blob<char> blob;

		BLOBOutputStream out(blob);

		out.write((unsigned char*)"hola pepe",9);
		out.write((unsigned char*)" Adios pepe",11);
		out.write((unsigned char*)"SM",2);

		BLOBInputStream in(blob);

		while(in.available())
		{
			cout << (char)in.read();
		}

		blob[3];

		int a = blob[2];

		const Stream::Blob<char> blob2(blob);

		blob2[2];

		
		FileUtil::GetFileVersion("cdffd");

	}catch(Exceptions::Win32ErrorException e)
	{
		
		cerr << e.what() << endl;
	}


	return 0;
}
