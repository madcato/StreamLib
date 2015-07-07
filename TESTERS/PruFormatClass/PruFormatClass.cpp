// PruFormatClass.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



int main(int argc, char* argv[])
{

	// La idea es crear una clase que permita la inclusión automática de subcadenas
	// dentro de una cadena preformada. 
	// Ejemplo: StrF("SELECT ? FROM ? WHERE ?=?")["id"]["table"]["column1"]["value"];


	try
	{
	string data = StrF("SELECT ? FROM ? WHERE ?=?")
						["id"]
						["table"]
						["column1"]
						["value"];

	string data2= StrF("SELECT ? FROM ? WHERE ?=?")["id"]["table"]["column1"]["mal"];

	string data3= StrF("SELECT ? FROM ? WHERE ?=?")["id"]["table"]["column1"];

	string data4= StrF("SELECT ? FROM ? WHERE ?=? ORDER BY ?")["id"]["table"]["column"]["value?"]["hola"];
	}catch(exceptions::StreamException* e)
	{
		console << e->what() << endln;
	}
	return 0;
}
