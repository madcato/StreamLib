// ManaCurve2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

long randomGen(long min,long max)
{
	long r = rand(); // From 0 to RAND_MAX

	long posibles_number = max - min + 1;

	return ((r * posibles_number)/ (RAND_MAX + 1)) + min;
}


long checkLibrary2(long cost0Cards,long cost1Cards,long cost2Cards,long cost3Cards,
				  long cost4Cards,long cost5Cards,long cost6Cards,
				  long libraryLands,long libraryCards,
				  long turns)
{

	long result = 0;
	// Construir librería

	vector<long> library;

	for(int i = 0 ; i < cost0Cards ; i++)
	{
		library.push_back(0);
	}
	for(i = 0 ; i < cost1Cards ; i++)
	{
		library.push_back(1);
	}
	for(i = 0 ; i < cost2Cards ; i++)
	{
		library.push_back(2);
	}
	for(i = 0 ; i < cost3Cards ; i++)
	{
		library.push_back(3);
	}
	for(i = 0 ; i < cost4Cards ; i++)
	{
		library.push_back(4);
	}
	for(i = 0 ; i < cost5Cards ; i++)
	{
		library.push_back(5);
	}
	for(i = 0 ; i < cost6Cards ; i++)
	{
		library.push_back(6);
	}
	for(i = 0 ; i < libraryLands ; i++)
	{
		library.push_back(-1);
	}


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
	for(int t = 0 ; (t < turns) && (life > 0) ; t++)
	{
		cardPlayed = false;
		// First draw;
		int selected = randomGen(0,library.size() -1 );
		int data = library[selected];

		hand.push_back(data);

		library.erase(library.begin() + selected);


		// Play land

		for(i = 0 ; i < hand.size() ; i++ )
		{
			if(hand[i] == -1)
			{
				hand.erase(hand.begin() + i);
				landsPlayed++;
				break;
			}			
		}

		// Play a card
		int landsNotTapped = landsPlayed;
		
		bool retry = false;
		do
		{
			retry = false;
			for(int m = landsNotTapped ; m > 0 ; m--)
			{
				for(i = 0 ; i < hand.size() ; i++ )
				{
					if(hand[i] == m)
					{
						hand.erase(hand.begin() + i);
						//result += 1;
						landsNotTapped -= m;
						retry = true;
						
						result += m;
						cardPlayed = true;
					}			
				}
				if(retry)
					break;
			}
		}while(retry);
		//result -= landsNotTapped;

		if(!cardPlayed)
		{
			//result -= 1;
			life -= t*4;
		}
	}


	
	return result;
}


long checkLibrary(long cost0Cards,long cost1Cards,long cost2Cards,long cost3Cards,
				  long cost4Cards,long cost5Cards,long cost6Cards,
				  long libraryLands,long libraryCards,
				  long turns)
{
	long result = 0;

	for(int i = 1 ; i < 50 ; i ++)
	{
		long manaUsed = checkLibrary2(0,cost1Cards,cost2Cards,cost3Cards,cost4Cards,
				cost5Cards,cost6Cards,libraryLands,libraryCards,turns);

		result = ((result * (i - 1)) + manaUsed ) / i;
	}

	return result;
}


int main(int argc, char* argv[])
{
	long libraryLands;
	long libraryCards;
	long turns;
	bool showHelp = false;
	if(argc != 4)
		showHelp = true;
	else
	{
		libraryLands = atol(argv[1]); // Number of lands
	
		libraryCards = atol(argv[2]);// Number of cards

		turns = atol(argv[3]); // Number of turns

		if(libraryLands == 0)
		{
			csout << "Parameter <lands> invalid. Must be a number greater than zero."<< endln;
			showHelp = true;
		}

		if(libraryCards <= 7)
		{
			csout << "Parameter <cards> invalid. Must be a number greater than seven."<< endln;
			showHelp = true;
		}

		if(turns <= 0)
		{
			csout << "Parameter <turns> invalid. Must be a number greater than zero."<< endln;
			showHelp = true;
		}

		if(turns > (libraryCards - 8))
		{
			csout << "Parameter <turns> invalid. Must be a number lesser than <libraryCards> - 8."<< endln;
			showHelp = true;
		}

		
	}
	if(showHelp)
	{
		csout << "Command-line Syntax: ManaCurve2 <lands> <deck_cards> <turns>" << endln;
		return -1;
	}

	unsigned t = (unsigned)time( NULL );
	srand(t);
	rand();



	long maxManaUsed =-1000000;

	for(long cost6Cards = 0 ; cost6Cards < 10 ; cost6Cards++)
	{
	for(long cost5Cards = 0 ; cost5Cards < 10 ; cost5Cards++)
	{
	for(long cost4Cards = 0 ; cost4Cards < 20 ; cost4Cards++)
	{
	for(long cost3Cards = 0 ; cost3Cards < 20 ; cost3Cards++)
	{
	for(long cost2Cards = 0 ; cost2Cards < 20 ; cost2Cards++)
	{
	for(long cost1Cards = 0 ; cost1Cards < 20 ; cost1Cards++)
	{
	/*for(long cost6Cards = 0 ; cost6Cards < 10 ; cost6Cards++)
	{*/
		if((cost1Cards + cost2Cards + cost3Cards + cost4Cards
			+ cost5Cards + cost6Cards) == (libraryCards - libraryLands))
		{
			long manaUsed = 0;
			manaUsed = checkLibrary(0,cost1Cards,cost2Cards,cost3Cards,cost4Cards,
				cost5Cards,cost6Cards,libraryLands,libraryCards,turns);


			if(manaUsed >= maxManaUsed)
			{
				csout << "------------------------------"<< endln;
				csout << "ManaUsed: " << manaUsed << endln;
				csout << "0: " << 0 << endln;
				csout << "1: " << cost1Cards << endln;
				csout << "2: " << cost2Cards << endln;
				csout << "3: " << cost3Cards << endln;
				csout << "4: " << cost4Cards << endln;
				csout << "5: " << cost5Cards << endln;
				csout << "6: " << cost6Cards << endln;
				csout << "------------------------------"<< endln << endln;
				
				maxManaUsed = manaUsed;
			}
		}
	//}
	}
	}
	}
	}
	}
	}



	return 0;
}
