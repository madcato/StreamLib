// TimerControl1.cpp: implementation of the TimerControl1 class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "TimerControl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/// namespace stream
namespace stream
{

/// namespace sync
namespace sync
{

std::map<int,TimerControl*> TimerControl::m_registeredObjects;


TimerControl::TimerControl()
{
	m_timer = 0;
}

void TimerControl::init(long miliseconds)
{
	m_timer = ::SetTimer(0,   // handle to main window 
				0,               // timer identifier 
				miliseconds,                     // second interval 
				(TIMERPROC) tick_internal); // timer callback

	m_registeredObjects.insert(std::pair<int,TimerControl*>(m_timer,this));
}


void TimerControl::finish()
{
	if(m_timer)
	{
		::KillTimer(0,m_timer);
		m_registeredObjects.erase(m_timer);
	}
}

TimerControl::~TimerControl()
{
	if(m_timer)
	{
		::KillTimer(0,m_timer);
		m_registeredObjects.erase(m_timer);
	}
}

int TimerControl::tick_internal(HWND hwnd,UINT uMsg,UINT_PTR idEvent,DWORD dwTime)
{
	return m_registeredObjects[idEvent]->tick();
}

} // namespace sync

} // namespace stream