// iwar.cpp : Defines the entry point for the console application.
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
	srand( (unsigned)time( NULL ) );
	rand();

	list<int> secret;
	list<int> secret_bak;
	for(int i = 0 ; i < 5 ; i++)
	{
		secret.push_back(randomGen(1,5));
	}

	secret_bak = secret;

	long count = 1;
	do {
		cout << count++ << "º ";
	
		list<int> test;
		do {
			

			int data;
			char c = getch();
			data = c - 48;

			if((data < 1)||(data > 5))
			{
				
			}
			else
			{
				cout << " " << c ;
				test.push_back(data);
			}
			
		} while(test.size()!= 5);

		int muertos = 0;
		int heridos = 0;

		list<int>::iterator test_iterator = test.begin();
		list<int>::iterator secret_iterator = secret.begin();

		list<int>::iterator test_iterator2;
		list<int>::iterator secret_iterator2;

		while(test_iterator != test.end())
		{
			if(*test_iterator == *secret_iterator)
			{
				muertos++;
				test_iterator2 = test_iterator;
				secret_iterator2 = secret_iterator;
				test_iterator2++;
				secret_iterator2++;
				test.erase(test_iterator);
				secret.erase(secret_iterator);
				test_iterator = test_iterator2;
				secret_iterator = secret_iterator2;
			}
			else
			{
				test_iterator++;
				secret_iterator++;
			}

			
		}

		if(muertos == 5)
		{
			cout << " --> FIN";
			return 0;
		}

		
		secret_iterator = secret.begin();

		while(secret_iterator != secret.end())
		{
			secret_iterator2 = secret_iterator;
			secret_iterator2++;
			test_iterator = test.begin();
			while(test_iterator != test.end())
			{
				if(*test_iterator == *secret_iterator)
				{
					heridos++;
					test_iterator2 = test_iterator;
					test_iterator2++;					
					test.erase(test_iterator);
					secret.erase(secret_iterator);
					test_iterator = test_iterator2;
					break;
				}
				else
				{
					test_iterator++;
				}
				
			}
			
			secret_iterator = secret_iterator2;
			
		}
		cout << " --> " << muertos<<"M "<<heridos<<"H"<<endl;
		secret = secret_bak;
	}
	while(true);
	
	return 0;
}
