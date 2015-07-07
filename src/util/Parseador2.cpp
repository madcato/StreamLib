

#include "stdafx.h"

#include "Entry2.h"
#include "Parseador2.h"


namespace stream
{

/// namespace util
namespace util
{

void Parseador2::SetDefaultEntry(Entry2* e)
{
	m_defaultEntry = e;
}
void Parseador2::SetEmptyEntry(std::string para,Entry2* e)
{
	m_mapaEmptyEntry[para] = e;
	
}
void Parseador2::SetValueEntry(std::string para,Entry2* e)
{
	m_mapaValueEntry[para] = e;
}
void Parseador2::SetErrorEntry(Entry2* e)
{
	m_errorEntry = e;
}


bool Parseador2::ParseParams(int argn,char* argv[])
{
	bool ToBien = true;
	int i = 1; // El primer parámetro no se trata porque es el path de la aplicación en ejecucion.
	
	while(i < argn )
	{
		
		std::string param = argv[i];

		if(PonBienParametro(param))
		{
			// Busco si no necesita valor
			std::map<std::string,Entry2*>::iterator it = m_mapaValueEntry.find(param);

			if(it != m_mapaValueEntry.end())
			{
				std::string paso = argv[i + 1];
				if(PonBienParametro(paso))
				{
					//Mal, no hay valor
					ToBien &= m_errorEntry->Trata(PARAM_NO_VALUE,param);
					return false;
				}
				else
				{
					ToBien &= it->second->Trata(param,paso);
					i++;
				}
			}
			else
			{
				it = m_mapaEmptyEntry.find(param);
				if(it != m_mapaEmptyEntry.end())
				{
					ToBien &= it->second->Trata(param,"");
				}
				else
				{
					ToBien &= m_errorEntry->Trata(PARAM_NOTRATADO,param);
					return false;
				}

			}	
		}
		else
		{
			// Es valor no parámetro.
			if(m_defaultEntry != 0)
			{
				ToBien &= m_defaultEntry->Trata("",param);
			}
			else
			{
				ToBien &= m_errorEntry->Trata(NO_DEFAULT_ENTRY,param);
				return false;
			}
		}
		i++;
	}
	
	std::string error;
	if(m_defaultEntry)
	{
		error = m_defaultEntry->GetError();
		if(error != "")
		{
			m_errorEntry->Trata(ERROR_TRATAMIENTO,error);
			return false;
		}
	}

	std::map<std::string,Entry2*>::iterator it = m_mapaValueEntry.begin();

	while(it != m_mapaValueEntry.end())
	{
		error = it->second->GetError();
		if(error != "")
		{
			m_errorEntry->Trata(ERROR_TRATAMIENTO,error);
			return false;
		}
		it++;
	}

	std::map<std::string,Entry2*>::iterator it2 = m_mapaEmptyEntry.begin();

	while(it2 != m_mapaEmptyEntry.end())
	{
		error = it2->second->GetError();
		if(error != "")
		{
			m_errorEntry->Trata(ERROR_TRATAMIENTO,error);
			return false;
		}
		it2++;
	}


	return ToBien;// Devuelve false si ha habido error.
}

bool Parseador2::PonBienParametro(std::string& param)
{
	



	switch(param[0])
	{
	case '/':
		param = &(param.c_str()[1]);
		return true;
	case '-':
		if(param[1] == '-')
		{
			param = &(param.c_str()[2]);
		}
		else
		{
			param = &(param.c_str()[1]);
		}
		return true;
	}


	return false;
}

} // namespace util

} // namespace stream