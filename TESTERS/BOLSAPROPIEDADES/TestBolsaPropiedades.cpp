// TestBolsaPropiedades.cpp : Defines the entry point for the console application.
//
// CurrentTests: 9

#include "stdafx.h"
#pragma warning(disable: 4786)	// stl warning
#include <iostream>
#include <Stream.h>
using namespace std;
using namespace Stream;
int main(int argc, char* argv[])
{
	try
	{
	
	cout << "class unit test: CBolsaPropiedades"<< endl;

	CBolsaPropiedades<std::string,std::string> prop;

	prop.put("Hola","pepe");
	if(prop.size() != 1)
	{
		cout << "FAIL TEST: 1"<< endl;
		return -1;
	}
	prop.put("Adios","jose");
	if(prop.size() != 2)
	{
		cout << "FAIL TEST: 2"<< endl;
		return -1;
	}
	if(prop.get("Adios") != string("jose"))
	{
		cout << "FAIL TEST: 3"<< endl;
		return -1;
	}
	if(prop.get("Adios") != string("jose"))
	{
		cout << "FAIL TEST: 4"<< endl;
		return -1;
	}
	if(prop.get("Hola") != string("pepe"))
	{
		cout << "FAIL TEST: 5"<< endl;
		return -1;
	}
	
	string result;
	try
	{
		string result = prop.get("dsa"); // Aquí debe saltar una excepción porque este elemento no existe.
		cout << "FAIL TEST: 9"<< endl;
		return -1;
	}catch(Exceptions::BolsaPropiedadesException*)
	{}

	if(!result.empty())
	{
		cout << "FAIL TEST: 6"<< endl;
		return -1;
	}

	prop.remove("Hola");
	if(prop.size() != 1)
	{
		cout << "FAIL TEST: 7"<< endl;
		return -1;
	}

	prop.put("Adios","jose2");
	if(prop.size() != 1)
	{
		cout << "FAIL TEST: 8"<< endl;
		return -1;
	}

	



	}catch(...)
	{
		cout << "class unit test: CBolsaPropiedades. UNHANDLED EXCEPTION"<< endl;
	}
	return 0;
}
