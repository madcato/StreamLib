// Caesar.cpp: implementation of the CCaesar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Caesar.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace stream
{

/// namespace util
namespace util
{

CCaesar::CCaesar()
{

}

CCaesar::~CCaesar()
{

}

std::string CCaesar::Ofuscate(const std::string& str)
{

	std::string finalStr = str;

	int l = str.length();

	for(int i = 0 ; i < l ; i++)
	{
		switch(str[i])
		{
			case 'a':
				finalStr[i] = 'e';
				break;
			case 'e':
				finalStr[i] = 'i';
				break;
			case 'i':
				finalStr[i] = 'o';
				break;
			case 'o':
				finalStr[i] = 'u';
				break;
			case 'u':
				finalStr[i] = 'a';
				break;
			case 'A':
				finalStr[i] = 'E';
				break;
			case 'E':
				finalStr[i] = 'I';
				break;
			case 'I':
				finalStr[i] = 'O';
				break;
			case 'O':
				finalStr[i] = 'U';
				break;
			case 'U':
				finalStr[i] = 'A';
				break;

			case 'z':
				finalStr[i] = 'b';
				break;
			case 'd':
				finalStr[i] = 'f';
				break;
			case 'h':
				finalStr[i] = 'j';
				break;
			case 'ñ':
				finalStr[i] = 'p';
				break;
			case 'n':
				finalStr[i] = 'ñ';
				break;
			case 't':
				finalStr[i] = 'v';
				break;
			case 'Z':
				finalStr[i] = 'B';
				break;
			case 'D':
				finalStr[i] = 'F';
				break;
			case 'H':
				finalStr[i] = 'J';
				break;
			case 'Ñ':
				finalStr[i] = 'P';
				break;
			case 'N':
				finalStr[i] = 'Ñ';
				break;
			case 'T':
				finalStr[i] = 'V';
				break;

			case '9':
				finalStr[i] = '0';
				break;

			default:
				if((str[i] >= 'a')&&(str[i] <= 'z')||(str[i] >= 'A')&&(str[i] <= 'Z')||(str[i] >= '0')&&(str[i] <= '9'))
				{
					finalStr[i] = str[i] + 1;
				}
				break;
		}
	}


	return finalStr;
}

std::string CCaesar::UnOfuscate(const std::string& str)
{
	std::string finalStr = str;

	int l = str.length();

	for(int i = 0 ; i < l ; i++)
	{
		switch(str[i])
		{
			case 'e':
				finalStr[i] = 'a';
				break;
			case 'i':
				finalStr[i] = 'e';
				break;
			case 'o':
				finalStr[i] = 'i';
				break;
			case 'u':
				finalStr[i] = 'o';
				break;
			case 'a':
				finalStr[i] = 'u';
				break;
			case 'E':
				finalStr[i] = 'A';
				break;
			case 'I':
				finalStr[i] = 'E';
				break;
			case 'O':
				finalStr[i] = 'I';
				break;
			case 'U':
				finalStr[i] = 'O';
				break;
			case 'A':
				finalStr[i] = 'U';
				break;

			case 'b':
				finalStr[i] = 'z';
				break;
			case 'f':
				finalStr[i] = 'd';
				break;
			case 'j':
				finalStr[i] = 'h';
				break;
			case 'p':
				finalStr[i] = 'ñ';
				break;
			case 'ñ':
				finalStr[i] = 'n';
				break;
			case 'v':
				finalStr[i] = 't';
				break;
			case 'B':
				finalStr[i] = 'Z';
				break;
			case 'F':
				finalStr[i] = 'D';
				break;
			case 'J':
				finalStr[i] = 'H';
				break;
			case 'P':
				finalStr[i] = 'Ñ';
				break;
			case 'Ñ':
				finalStr[i] = 'N';
				break;
			case 'V':
				finalStr[i] = 'T';
				break;

			case '0':
				finalStr[i] = '9';
				break;

			default:
				if((str[i] >= 'a')&&(str[i] <= 'z')||(str[i] >= 'A')&&(str[i] <= 'Z')||(str[i] >= '0')&&(str[i] <= '9'))
				{
					finalStr[i] = str[i] - 1;
				}
				break;
		}
	}


	return finalStr;
}

} // namespace util

} // namespace stream