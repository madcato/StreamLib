
#include "stdafx.h"

#include "Exceptions.h"
#include "Tokenizer.h"

/// namespace stream
namespace stream
{

/// namespace util
namespace util
{

Tokenizer::Tokenizer(std::string cad,modes m)
{
	m_mode = m;
	Init(cad,std::string("\t\n\r"));
}


Tokenizer::Tokenizer(std::string cad,std::string delim,modes m)
{
	m_mode = m;
	Init(cad,delim);	
}

void Tokenizer::Init(std::string c,std::string delim)
{
	std::string cad(c.c_str());
	std::string paso;
	std::string delimiter;
	const char* first = cad.c_str();

	char* pos = strpbrk(cad.c_str(),delim.c_str());
	
	while(pos != 0)
	{
		delimiter = pos;
		delimiter = delimiter.substr(0,1);
		*pos = '\0';
		paso = first;
		if(paso == "")
		{
			if((m_mode != WITHOUT_BLANCKS) && (m_mode != FULL))
				m_vectorTokens.push_back(paso);
		}
		else
		{
			m_vectorTokens.push_back(paso);
		}
		if((m_mode == RETURN_DELIMITERS) || (m_mode == FULL))
		{
			m_vectorTokens.push_back(delimiter);
		}
		
		first = pos+1;
		pos = strpbrk(first,delim.c_str());

	}

	// La ultima ocurrencia
	paso = first;
	if(paso == "")
	{
		if((m_mode != WITHOUT_BLANCKS) && (m_mode != FULL))
			m_vectorTokens.push_back(paso);
	}
	else
	{
		m_vectorTokens.push_back(paso);
	}


	m_posActual = m_vectorTokens.begin();
}

Tokenizer::~Tokenizer()
{
	m_vectorTokens.clear();
}

int Tokenizer::CountTokens()
{
	return m_vectorTokens.size();
}

bool Tokenizer::HasMoreTokens()
{
	return (m_posActual != m_vectorTokens.end());
}

std::string Tokenizer::NextToken()
{
	if(m_posActual == m_vectorTokens.end())
		throw new exceptions::TokenizerException(1);
	return *m_posActual++;
}

} // namespace util

} // namespace std