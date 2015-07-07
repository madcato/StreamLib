// Izzet.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define THIRST_OF_KNOWLEDGE Card(Card::Draw,3,2,0,0,1,0,0)

class Card
{
public:
	
	enum CardType
	{
		Land = 1,
		Draw,
		Damage
	};

	Card(CardType t,int val,int mana,int manaR,int manaG,int manaU,int manaB,int manaW):type(t),m_X(val),m_mana(mana),m_manaR(manaR),m_manaG(manaG),m_manaU(manaU),m_manaB(manaB),m_manaW(manaW){}
	CardType type;
	int m_mana;
	int m_manaR;
	int m_manaG;
	int m_manaU;
	int m_manaB;
	int m_manaW;
	int m_X;
};
long randomGen(long min,long max)
{
	long r = rand(); // From 0 to RAND_MAX

	long posibles_number = max - min + 1;

	return ((r * posibles_number)/ (RAND_MAX + 1)) + min;
}

Card drawACard(vector<Card>& deck,vector<Card>& hand)
{
	if(deck.size() == 0)
		return Card(Card::Land,0,0,0,0,0,0,0);
	int selected = randomGen(0,deck.size() - 1);
	Card data = deck[selected];

	hand.push_back(data);

	deck.erase(deck.begin() + selected);

	return data;
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
			csout << "Parameter <lands> invalid. Must be a number greater than zero."<< endln;
			showHelp = true;
		}

		if(cards <= 7)
		{
			csout << "Parameter <cards> invalid. Must be a number greater than seven."<< endln;
			showHelp = true;
		}

		
	}
	if(showHelp)
	{
		csout << "Command-line Syntax: Izzet <lands> <deck_cards>" << endln;
		return -1;
	}


	float mediaTurnos = 0;
	int actualTest = 0;

	int playedLands = 0;
	for(int timesTest = 1 ; timesTest < 10000 ; timesTest++)
	{
	
		srand(t*timesTest);
		rand();


		vector<Card> deck; // 0 land, 1 other.
		vector<Card> hand; // 0 land, 1 other.

		
		for(int i = 0 ; i < cards - lands; i++)
		{
			deck.push_back(THIRST_OF_KNOWLEDGE);
		}
		for(; i < cards; i++)
		{
			deck.push_back(Card(Card::Land,0,0,0,0,0,0,0));
		}

		if(deck.size() != cards)
		{
			csout << "Invalid deck size." << endln;
			return -1;
		}

		// Prev Start. Get 6 cards.

		for(i = 0 ; i < 6 ; i++)
		{
			drawACard(deck,hand);
		}


		// Get card and throw a land until no lands.
		bool salir = false;
		bool land = false;
		int turn = 0;
		while(!salir)
		{
			turn ++;
			
			Card data = drawACard(deck,hand);

			// Jugamos tierra
			for(i = 0 ; i < hand.size() ; i++ )
			{
				if(hand[i].type == Card::Land)
				{
					hand.erase(hand.begin() + i);
					playedLands++;
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

			bool noPlayed = false;
			int manaToUse = 0;
			do
			{
				manaToUse = playedLands;
				// Jugamos carta;
				Card cardToPlay(Card::Land,0,0,0,0,0,0,0);
				int iCardToPlay = -1;
				for(i = 0 ; i < hand.size() ; i++ )
				{
					if(hand[i].manaCost <= manaToUse)
					{
						if(hand[i].manaCost >= cardToPlay.manaCost)
						{
							cardToPlay = hand[i];
							iCardToPlay = i;
						}
					}
				}

				switch(cardToPlay.type)
				{
				case Card::Draw:
					{
						manaToUse -= cardToPlay.manaCost;
						hand.erase(hand.begin() + iCardToPlay);
						for(i = 0 ; i < cardToPlay.X ; i++)
						{
							drawACard(deck,hand);
						}
					}
				default:
					noPlayed = true;
				};
			}while((manaToUse > 0)&&(noPlayed == false));





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
	csout << mediaTurnos << endln;
	
	accumulated += lands_vec[14];
	csout << "14: " << (lands_vec[14] / 100)<< "% - " << (accumulated/100) <<  "%" << endln;
	accumulated += lands_vec[13];
	csout << "13: " << (lands_vec[13] / 100)<< "% - " << (accumulated/100) <<  "%" << endln;
	accumulated += lands_vec[12];
	csout << "12: " << (lands_vec[12] / 100)<< "% - " << (accumulated/100) <<  "%" << endln;
	accumulated += lands_vec[11];
	csout << "11: " << (lands_vec[11] / 100)<< "% - " << (accumulated/100) <<  "%" << endln;
	accumulated += lands_vec[10];
	csout << "10: " << (lands_vec[10] / 100)<< "% - " << (accumulated/100) <<  "%" << endln;
	accumulated += lands_vec[9];
	csout << "9: " << (lands_vec[9] / 100)<< "% - " << (accumulated/100) <<  "%" << endln;
	accumulated += lands_vec[8];
	csout << "8: " << (lands_vec[8] / 100)<< "% - " << (accumulated/100) <<  "%" << endln;
	accumulated += lands_vec[7];
	csout << "7: " << (lands_vec[7] / 100)<< "% - " << (accumulated/100) <<  "%" << endln;
	accumulated += lands_vec[6];
	csout << "6: " << (lands_vec[6] / 100)<< "% - " << (accumulated/100) <<  "%" << endln;
	accumulated += lands_vec[5];
	csout << "5: " << (lands_vec[5] / 100)<< "% - " << (accumulated/100) <<  "%" << endln;
	accumulated += lands_vec[4];
	csout << "4: " << (lands_vec[4] / 100)<< "% - " << (accumulated/100) <<  "%" << endln;
	accumulated += lands_vec[3];
	csout << "3: " << (lands_vec[3] / 100)<< "% - " << (accumulated/100) <<  "%" << endln;
	accumulated += lands_vec[2];
	csout << "2: " << (lands_vec[2] / 100)<< "% - " << (accumulated/100) <<  "%" << endln;
	accumulated += lands_vec[1];
	csout << "1: " << (lands_vec[1] / 100)<< "% - " << (accumulated/100) <<  "%" << endln;
	
	

	return 0;
}

