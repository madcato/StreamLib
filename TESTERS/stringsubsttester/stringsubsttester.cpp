// stringsubsttester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main(int argc, char* argv[])
{
	string finalString = "";

	string id(2,'0');
	id += "a";
	finalString += id.substr(id.length() - 2,2);

	return 0;
}
