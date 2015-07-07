// ref_ptr_memmory_checker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

class Prueba
{
public:
	Prueba(){}
	Prueba(ref_count_ptr<int> data):m_data(data){}

ref_count_ptr<int> m_data;
};

Prueba g_cosa;


ref_count_ptr<int> foo(ref_count_ptr<int> f)
{
	Prueba g(f);
	ref_count_ptr<int> d = f;

	ref_count_ptr<int> d2(new int);
	f = d2;

	ref_count_ptr<int> d3(new int);

	return d3;

}
int main(int argc, char* argv[])
{
	

	//ref_count_ptr<int> d3(new int);
	ref_count_ptr<int> d4(new int);

	//Prueba h(d3);

	Prueba g(foo(d4));

	return 0;
}
