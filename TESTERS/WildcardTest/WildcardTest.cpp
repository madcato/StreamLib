// WildcardTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main(int argc, char* argv[])
{

	if(Wildcard::check("Hola Pepe","*a *"))
	{
		cout << "Ok"<< endl;
	}
	else
	{
		cout <<"Err" <<endl;
	}

	if(Wildcard::check("Hola Pepe","*a Pe?e"))
	{
		cout << "Ok"<< endl;
	}
	else
	{
		cout <<"Err" <<endl;
	}

	if(Wildcard::check("Hola Pepe","?????????"))
	{
		cout << "Ok"<< endl;
	}
	else
	{
		cout <<"Err" <<endl;
	}


	if(Wildcard::check("Hola Pepe","*sPe?e"))
	{
		cout << "Ok"<< endl;
	}
	else
	{
		cout <<"Err" <<endl;
	}

	if(Wildcard::check("Hola Pepe","*as"))
	{
		cout << "Ok"<< endl;
	}
	else
	{
		cout <<"Err" <<endl;
	}

	return 0;
}
