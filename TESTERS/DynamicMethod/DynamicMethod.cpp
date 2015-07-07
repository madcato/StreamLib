// DynamicMethod.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

class TestClass : public DynamicClass
{
public:

BEGIN_METHOD_MAP(TestClass)
	DECLARE_METHOD(run1)
	DECLARE_METHOD(run2)
END_METHOD_MAP()

	void run1(const Properties& input,Properties& output)
	{
		csout << "Method run1 called" << endln;
	}

	void run2(const Properties& input,Properties& output)
	{
		csout << "Method run2 called" << endln;
	}
};

int main(int argc, char* argv[])
{

	BEGIN_TRY_CATCH()

	TestClass c;

	Properties args;
	Properties oargs;

	c.invoke("run1",args,oargs);
	c.invoke("run2",args,oargs);
	c.invoke("run3",args,oargs);

	END_TRY_CATCH();

	return 0;
}
