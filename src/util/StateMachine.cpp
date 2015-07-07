// StateMachine.cpp: implementation of the StateMachine class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "IInputStream.h"
#include "Exceptions.h"

#include "StateMachine.h"

#include "IOutputStream.h"
#include "PropertyBag.h"
#include "Properties.h"
#include "PersistentProperties.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/// namespace stream
namespace stream
{

/// namespace util
namespace util
{

StateMachine::StateMachine(std::auto_ptr<io::IInputStream> configurationStream)
{

	m_currentState = "";


	util::PersistentProperties prop;

	prop.load(configurationStream);

	m_mapaTransiciones = prop.getMap();

	m_currentState = m_mapaTransiciones["ini"];
}

StateMachine::~StateMachine()
{

}

void StateMachine::event(const std::string& eventStr)
{

	doEvent(eventStr);

	std::string index = m_currentState + "+" + eventStr;

	std::string newState = m_mapaTransiciones[index];

	if(newState != "")
	{
		doError(m_currentState, eventStr);
		//throw new exceptions::StateMachineException(-1,"invalid state or event" + index);
	}

	doTran(index);
	m_currentState = newState;


	doNotification();
}

} // namespace util

} // namespace stream