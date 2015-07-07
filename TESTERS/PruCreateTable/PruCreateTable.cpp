// PruCreateTable.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

class A1
{
};
REGISTER_CLASS_AND_CATEGORY(A1,PROMO);

class A2
{
};
REGISTER_CLASS_AND_CATEGORY(A2,PROMO);

class A3
{
};
REGISTER_CLASS_AND_CATEGORY(A3,PROMO);

class A4
{
};
REGISTER_CLASS_AND_CATEGORY(A4,PROMO);

class A5
{
};
REGISTER_CLASS_AND_CATEGORY(A5,PROMO);

class A6
{
};
REGISTER_CLASS_AND_CATEGORY(A6,ROMO);

class A7
{
};
REGISTER_CLASS_AND_CATEGORY(A7,ROMO);

class A8
{
};
REGISTER_CLASS_AND_CATEGORY(A8,ROMO);


int main(int argc, char* argv[])
{

	CoInitialize(NULL);

	try
	{

		list<string> classes = ClassFactory::getClassNames("PROMO");

		A2* a = (A2*)ClassFactory::createObject(*classes.begin());


		DB::init("Provider=MSDASQL;Driver={SQL Server};Server=(local);Database=SGTsim;");


		// Compatible con SQL Server.
		DB::execute("CREATE TABLE test "
					"(id Int IDENTITY(1,1) NOT NULL PRIMARY KEY, "
					" str Varchar(10) NULL, "
					" value Int NOT NULL DEFAULT 0, "
					" dtime DateTime NOT NULL)" );


		
	}catch(exceptions::StreamException* e)
	{
		console << e->what() << endln;

	}


	CoUninitialize();
	return 0;
}
