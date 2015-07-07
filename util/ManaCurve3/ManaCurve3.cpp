// ManaCurve3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


class Test
{
public:
	Test(){}
	~Test(){}
};
REGISTER_CLASS(Test);
long randomGen(long min,long max)
{
	long r = rand(); // From 0 to RAND_MAX

	long posibles_number = max - min + 1;

	return ((r * posibles_number)/ (RAND_MAX + 1)) + min;
}


long checkLibrary2(long type4Cards,long type3Cards,long type2Cards,
				  long libraryLands,long libraryCards,
				  long turns)
{

	long type4 = 0;
	long type3 = 0;
	long type2 = 0;


	long result = 0;
	// Construir librería

	vector<long> library;

	for(int i = 0 ; i < type4Cards; i++)
	{
		library.push_back(i);
		library.push_back(i);
		library.push_back(i);
		library.push_back(i);
	}
	for(i = 0 ; i < type3Cards ; i++)
	{
		library.push_back(i+100);
		library.push_back(i+100);
		library.push_back(i+100);
	}
	for(i = 0 ; i < type2Cards ; i++)
	{
		library.push_back(i+200);
		library.push_back(i+200);
	}
	for(i = 0 ; i < libraryLands ; i++)
	{
		library.push_back(-1);
	}

	ASSERT(library.size() == 60);


	// Prev Start. Get 7 cards.
	vector<long> hand;
	for(i = 0 ; i < 7 ; i++)
	{
		int selected = randomGen(0,library.size() - 1);
		int data = library[selected];

		hand.push_back(data);

		
		library.erase(library.begin() + selected);
	}

	long life = 20;
	bool cardPlayed = false;
	int landsPlayed = 0;
	for(int t = 0 ; t < turns && life > 0 ; t++)
	{
		cardPlayed = false;
		// First draw;
		int selected = randomGen(0,library.size() -1 );
		int data = library[selected];

		hand.push_back(data);

		library.erase(library.begin() + selected);
	}

	long vec[300];

	memset(vec,0,300);

	for(t = 0 ; t < hand.size() ; t++)
	{
		vec[hand[t]]++;
	}

	for(i = 0 ; i < type4Cards; i++)
	{
		if(vec[i] > 0 )
		{
			result++;
		}
	}
	for(i = 0 ; i < type3Cards ; i++)
	{
		if(vec[i+100] >= 1)
		{
			result += 2;
		}
		if(vec[i+100] == 0)
		{
			result -= 1;
		}
	}
	for(i = 0 ; i < type2Cards ; i++)
	{
		if(vec[i+200] >= 1)
		{
			
				result+=2;
		}
		else
		{
			if(turns > 15)
			{
				result--;
			}		
		}
		
	}
	for(i = 0 ; i < libraryLands ; i++)
	{
		library.push_back(-1);
	}

	return result;
}


float checkLibrary(long type4Cards,long type3Cards,long type2Cards,
				  long libraryLands,long libraryCards,
				  long turns)
{
	float result = 0;

	for(int i = 1 ; i < 500 ; i ++)
	{
		rand();
		long manaUsed = checkLibrary2(type4Cards,type3Cards,type2Cards,
			libraryLands,libraryCards,turns);

		result = ((result * i - 1) + manaUsed ) / i;
	}

	return result;
}


int main(int argc, char* argv[])
{
	long libraryLands = atol(argv[1]);
	long libraryCards = atol(argv[2]);
	long turns = atol(argv[3]);

	unsigned t = (unsigned)time( NULL );
	srand(t);
	rand();



	float maxManaUsed =-1000000;

	for(long type4Cards = 0 ; type4Cards < 10 ; type4Cards++)
	{
	for(long type3Cards = 0 ; type3Cards < 10 ; type3Cards++)
	{
	for(long type2Cards = 0 ; type2Cards < 10 ; type2Cards++)
	{
		if(((type4Cards * 4) + (type3Cards * 3) + (type2Cards * 2))  == (libraryCards - libraryLands))
		{
			float manaUsed = 0;
			manaUsed = checkLibrary(type4Cards,type3Cards,type2Cards
				,libraryLands,libraryCards,turns);


			if(manaUsed >= maxManaUsed)
			{
				csout << "------------------------------"<< endln;
				csout << "type4: " << type4Cards << endln;
				csout << "type3: " << type3Cards << endln;
				csout << "type2: " << type2Cards << endln;
				csout << "------------------------------"<< endln << endln;
				
				maxManaUsed = manaUsed;
			}
		}
	//}
	}
	}
	}



	return 0;
}
