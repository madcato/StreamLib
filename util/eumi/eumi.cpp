// eumi.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


long randomGen(long min,long max)
{
	long r = rand(); // From 0 to RAND_MAX

	long posibles_number = max - min + 1;

	return ((r * posibles_number)/ (RAND_MAX + 1)) + min;
}

int main(int argc, char* argv[])
{

	vector<long> bombo;

	for(int i = 0 ; i < 50 ; i++)
	{
		bombo.push_back(i+1);
	}

	
	/* Seed the random-number generator with current time so that
	* the numbers will be different every time we run.
	*/
	srand( (unsigned)time( NULL ) );
	rand();
	
/*	for(i = 0 ; i < 100 ; i++)
	{
		csout << randomGen(1,5) << " ";
	}
	return 0;*/

	vector<long>::iterator iter;
	/* Display 10 numbers. */
	for( i = 0;   i < 5;i++ )
	{
	
		long pos = randomGen(1,50 - i);
		
		

		for(iter = bombo.begin(); pos != 1 ; pos--)
		{
			iter++;
		}

		csout << *iter << " ";

		bombo.erase(iter);
		


	}

	csout << endln;

	bombo.clear();


	for(i = 0 ; i < 9 ; i++)
	{
		bombo.push_back(i+1);
	}

	for( i = 0;   i < 2;i++ )
	{
		long pos = randomGen(1,9 - i);

		for(iter = bombo.begin(); pos != 1 ; pos--)
		{
			iter++;
		}

		csout << *iter << " ";

		bombo.erase(iter);
	}

	csout << endln;
	csout << endln;
	for(i = 0 ; i < bombo.size() ; i++)
	{
		csout << bombo[i] << " ";
	}


	return 0;
}
