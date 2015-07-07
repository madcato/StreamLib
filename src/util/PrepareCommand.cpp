// PrepareCommand.cpp: implementation of the PrepareCommand class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PrepareCommand.h"

#include "exceptions.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/// namespace stream
namespace stream
{
/// namespace util
namespace util
{


PrepareCommand::PrepareCommand(std::string key_caracter):m_key_carac(key_caracter)
{

}



PrepareCommand::~PrepareCommand()
{

}

std::string PrepareCommand::getFinalCommand() const
{

	std::string final = "";
	std::string command = m_command;
	bool salir;
	int i = 0;

	salir = false;

	std::string paso;

	do
	{
		int pos = command.find(m_key_carac);
		if(pos != std::string::npos)
		{
			if(m_vValores.size() <= i)
			{
				throw new exceptions::StreamException(-1,"Too few key characters: " + m_command);
			}
			final.append(command,0,pos);
			command.erase(0,pos + m_key_carac.length());
			final.append(m_vValores[i++]);		
		}
		else
		{
			salir = true;
		}
	}while(!salir);

	if(m_vValores.size() != i)
	{
		throw new exceptions::StreamException(-1,"Too many key characters: " + m_command);
	}

	final.append(command);

	
	return final;

}

void PrepareCommand::set(int index, std::string valor)
{
	if(index+1 >= m_vValores.capacity())
	{
		m_vValores.resize(index+1);
	}
	m_vValores[index] = valor;
}

void PrepareCommand::setCommand(std::string command)
{
	m_command = command;
	m_vValores.clear();
}

} // namespace util

} // namespace stream
