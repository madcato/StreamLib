// TimeT.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main(int argc, char* argv[])
{

	string s1,s2;

	s1 = "Hola";
	s2 = " mundo";

	s1 = s1 + s2;

	csout << Time::today() << "\r\n";

	Time t;

	csout << t.getYear() << t.getMonth() << t.getDay() << "\r\n";
	csout << t.getHour() << t.getMinute() << t.getSecond() << "\r\n";

	t.addHours(10);

	csout << t.getYear() << t.getMonth() << t.getDay() << "\r\n";
	csout << t.getHour() << t.getMinute() << t.getSecond() << "\r\n";

	t.addHours(10);

	csout << t.getYear() << t.getMonth() << t.getDay() << "\r\n";
	csout << t.getHour() << t.getMinute() << t.getSecond() << "\r\n";

	Time t2;

	Sleep(2000);
	Time t3;

	ulong u;
	
	u = t3 - t2;
	csout << "\r\n";
	csout << u;



	


	return 0;
}
