// PacketSorterTester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main(int argc, char* argv[])
{


	try
	{
		IInputStreamPtr ptr(new FileInputStream("prueba.txt"));

		PacketSorter sorter(ptr);

	}catch(exception* e)
	{
		cerr << e->what() << endl;
	}
	return 0;
}
