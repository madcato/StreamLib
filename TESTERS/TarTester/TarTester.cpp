// TarTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <Stream.h>

using namespace Stream;

void Run1()
{
	try
	{
		CFileOutputStream* output = new CFileOutputStream("c:\\temp\\pru.tar");

		std::auto_ptr<IOutputStream> ptr_output = std::auto_ptr<IOutputStream>(output);
		TarWriter tar(ptr_output);

		CFileInputStream* input1 = new CFileInputStream("c:\\temp\\test.txt");

		tar.write(std::auto_ptr<IInputStream>(input1),"test.txt");

		CFileInputStream* input2 = new CFileInputStream("c:\\temp\\Tipos.txt");

		tar.write(std::auto_ptr<IInputStream>(input2),"cosa\\NotifEngine.zip");

		tar.writeDirectory("cosa2\\temp");
		tar.writeDirectory("cosa3");
		tar.writeDirectory("aaaaaaaaaaaaaaaaaaaakkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkaaaaaaaaaaaaaaaaaaaaa/aaasdddddadddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd/aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaadaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa/aaaaaaaaaaaaaaaaaaaaaaaaajjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj/aaaaaaaaaaaaaatttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt");

		tar.close();
	}catch(exception* e)
	{
		std::cerr << e->what() << std::endl;
	}
	catch(...)
	{
		std::cerr << "Unhandled exception." << std::endl;
	}

}


void Run2()
{
	try
	{
		CFileInputStream* input = new CFileInputStream("c:\\temp\\pru.tar");
		std::auto_ptr<IInputStream> ptr_input = std::auto_ptr<IInputStream>(input);
		TarReader tar(ptr_input);

		unsigned char buffer[1001];

		std::auto_ptr<IInputStream> data;
		std::string path = "";
		bool directory;
		while(tar.getNextItem(path,directory,data))
		{
			if(!directory)
			{
				std::cout << "File: " << path << std::endl << std::endl;
				while(data->available())
				{
					int readed = data->read(buffer,1000);
					buffer[readed] = '\0';
					std::cout << (char*)buffer;
				}
				data->close();
				std::cout << std::endl << std::endl;
			}
			else
			{
				std::cout << "Directory: " << path << std::endl << std::endl;
			}
		}

		tar.close();
	}catch(exception* e)
	{
		std::cerr << e->what() << std::endl;
	}
	catch(...)
	{
		std::cerr << "Unhandled exception." << std::endl;
	}


}

void Run3()
{
	try
	{
		Tar tar;
		
		tar.RunAdd("c:\\temp\\file.tar","c:\\temp\\tas");

	}catch(exception* e)
	{
		std::cerr << e->what() << std::endl;
	}
	catch(...)
	{
		std::cerr << "Unhandled exception." << std::endl;
	}


}

void Run4()
{
	try
	{
		Tar tar;
		
		tar.RunExtract("c:\\temp\\file.tar","c:\\temp\\tas2");

	}catch(exception* e)
	{
		std::cerr << e->what() << std::endl;
	}
	catch(...)
	{
		std::cerr << "Unhandled exception." << std::endl;
	}


}

int main(int argc, char* argv[])
{

	Run1();

	Run2();

	Run3();

	Run4();
	
	return 0;
}
