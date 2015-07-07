// ManaCurve.cpp : Defines the entry point for the console application.
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
	std::string ta = "\x02\x01\x02\x02\x02\x2";
	vector<long> lands_vec;

	lands_vec.push_back(0);
	lands_vec.push_back(0);
	lands_vec.push_back(0);
	lands_vec.push_back(0);
	lands_vec.push_back(0);
	lands_vec.push_back(0);
	lands_vec.push_back(0);
	lands_vec.push_back(0);
	lands_vec.push_back(0);
	lands_vec.push_back(0);
	lands_vec.push_back(0);
	lands_vec.push_back(0);
	lands_vec.push_back(0);
	lands_vec.push_back(0);
	lands_vec.push_back(0);
	

	unsigned t = (unsigned)time( NULL );
	srand(t);
	rand();

	/* // Para comprobar el randomGen
	for(int a = 0 ; a < 10000000 ; a++)
	{
		long h = randomGen(0,59);


		if(h == 0)
		{
			int i = 0;
		}
		if(h == 59)
		{
			int i = 0;
		}
		if(h == 60)
		{
			int i = 0;
		}
	}*/

	bool showHelp = false;

	long lands  = 0;
	long cards = 0;
	if(argc != 3)
		showHelp = true;
	else
	{
		lands = atol(argv[1]); // Number of lands

		cards = atol(argv[2]); // Number of cards
			
		if(lands == 0)
		{
			console << "Parameter <lands> invalid. Must be a number greater than zero."<< endln;
			showHelp = true;
		}

		if(cards <= 7)
		{
			console<< "Parameter <cards> invalid. Must be a number greater than seven."<< endln;
			showHelp = true;
		}

		
	}
	if(showHelp)
	{
		console<< "Command-line Syntax: ManaCurve <lands> <deck_cards>" << endln;
		return -1;
	}


	float mediaTurnos = 0;
	int actualTest = 0;

	
	for(int timesTest = 1 ; timesTest < 10000 ; timesTest++)
	{
	
		srand(t*timesTest);
		rand();


		vector<int> deck; // 0 land, 1 other.
		vector<int> hand; // 0 land, 1 other.

		
		for(int i = 0 ; i < cards - lands; i++)
		{
			deck.push_back(1);
		}
		for(; i < cards; i++)
		{
			deck.push_back(0);
		}

		if(deck.size() != cards)
		{
			console<< "Invalid deck size." << endln;
			return -1;
		}

		// Prev Start. Get 6 cards.

		for(i = 0 ; i < 6 ; i++)
		{
			int selected = randomGen(0,deck.size() - 1);
			int data = deck[selected];

			hand.push_back(data);

			deck.erase(deck.begin() + selected);
		}


		// Get card and throw a land until no lands.
		bool salir = false;
		bool land = false;
		int turn = 0;
		while(!salir)
		{
			turn ++;
			int selected = randomGen(0,deck.size() -1 );
			int data = deck[selected];

			hand.push_back(data);

			deck.erase(deck.begin() + selected);

			for(i = 0 ; i < hand.size() ; i++ )
			{
				if(hand[i] == 0)
				{
					hand.erase(hand.begin() + i);
					land = true;
					break;
				}
				else
				{
					land = false;
				}
			}
			if(!land)
				salir = true;

			if(deck.size() == 0)
			{
				salir = true;
			}
		}
				
		actualTest++;
		mediaTurnos = (mediaTurnos * (actualTest -1) + (turn - 1)) / actualTest;

		if(turn < 15)
			lands_vec[turn]++;
	

	}	
	long accumulated = 0;
	console<< mediaTurnos << endln;
	
	accumulated += lands_vec[14];
	console<< "14: " << (lands_vec[14] / 100)<< "% - " << (accumulated/100) <<  "%" << endln;
	accumulated += lands_vec[13];
	console<< "13: " << (lands_vec[13] / 100)<< "% - " << (accumulated/100) <<  "%" << endln;
	accumulated += lands_vec[12];
	console<< "12: " << (lands_vec[12] / 100)<< "% - " << (accumulated/100) <<  "%" << endln;
	accumulated += lands_vec[11];
	console<< "11: " << (lands_vec[11] / 100)<< "% - " << (accumulated/100) <<  "%" << endln;
	accumulated += lands_vec[10];
	console<< "10: " << (lands_vec[10] / 100)<< "% - " << (accumulated/100) <<  "%" << endln;
	accumulated += lands_vec[9];
	console<< "9: " << (lands_vec[9] / 100)<< "% - " << (accumulated/100) <<  "%" << endln;
	accumulated += lands_vec[8];
	console<< "8: " << (lands_vec[8] / 100)<< "% - " << (accumulated/100) <<  "%" << endln;
	accumulated += lands_vec[7];
	console<< "7: " << (lands_vec[7] / 100)<< "% - " << (accumulated/100) <<  "%" << endln;
	accumulated += lands_vec[6];
	console<< "6: " << (lands_vec[6] / 100)<< "% - " << (accumulated/100) <<  "%" << endln;
	accumulated += lands_vec[5];
	console<< "5: " << (lands_vec[5] / 100)<< "% - " << (accumulated/100) <<  "%" << endln;
	accumulated += lands_vec[4];
	console<< "4: " << (lands_vec[4] / 100)<< "% - " << (accumulated/100) <<  "%" << endln;
	accumulated += lands_vec[3];
	console<< "3: " << (lands_vec[3] / 100)<< "% - " << (accumulated/100) <<  "%" << endln;
	accumulated += lands_vec[2];
	console<< "2: " << (lands_vec[2] / 100)<< "% - " << (accumulated/100) <<  "%" << endln;
	accumulated += lands_vec[1];
	console<< "1: " << (lands_vec[1] / 100)<< "% - " << (accumulated/100) <<  "%" << endln;
	
	

	return 0;
}

