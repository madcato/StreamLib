// Wildcard.cpp: implementation of the Wildcard class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Wildcard.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/// namespace stream
namespace stream
{

/// namespace util
namespace util
{

Wildcard::Wildcard()
{

}

Wildcard::~Wildcard()
{

}

bool Wildcard::check(const std::string& toSearchText, 
			const std::string& expresionText)
{
	return check_internal(toSearchText,expresionText,0,0);			
}


bool Wildcard::check_internal(const std::string& toSearchText, 
									const std::string& expresionText,
									long toSearchPosition,
									long expresionPosition)
{
	if(expresionPosition == expresionText.length())
	{
		return true;
	}

	if(toSearchPosition == toSearchText.length())
	{
		return true;
	}


	switch(expresionText[expresionPosition])
	{
	case '*':
		{
			// Si es el último caracter de la expresión volvemos
			if((expresionPosition + 1) == expresionText.length())
			{
				return true;
			}

			for(int i = toSearchPosition + 1 ; i < toSearchText.length() ; i++)
			{
				if(check_internal(toSearchText, 
									expresionText,
									i,
									expresionPosition + 1))
				{
					return true;
				}
			}

			break;
		}
	case '?':
			return check_internal(toSearchText, 
								expresionText,
								toSearchPosition + 1,
								expresionPosition + 1);
		break;
	default:
		if(expresionText[expresionPosition] == toSearchText[toSearchPosition])
		{
			return check_internal(toSearchText, 
								expresionText,
								toSearchPosition + 1,
								expresionPosition + 1);
		}
		else
		{
			return false;
		}
	}

	return false;

}

} // namespace util

} // namespace stream