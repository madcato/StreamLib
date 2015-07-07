// Time.cpp: implementation of the Time class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Time_s.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace stream
{

/// namespace util
namespace util
{

Time::Time()
{
	time(&m_time);
}

Time::~Time()
{

}

void Time::addDays(ulong days)
{
	m_time += days * 24 * 60 * 60;
}

void Time::addHours(ulong hours)
{
	m_time += hours * 60 * 60;
}

void Time::addMinutes(ulong minutes)
{
	m_time += minutes * 60;
}

void Time::addSeconds(ulong seconds)
{
	m_time += seconds;
}

ulong Time::operator-(const Time& t2)
{	
	return difftime(m_time,t2.m_time);
}

std::string Time::today()
{
	time_t t;
	time(&t);
	char buffer[1000];
	strftime(buffer,1000,"%d/%m/%Y %H:%M:%S",localtime(&t));

	return buffer;
}

ulong Time::getYear()
{
	tm* t;
	t = localtime(&m_time);

	if(!t) return -1;

	return t->tm_year + 1900;
}

ulong Time::getMonth()
{
	tm* t;
	t = localtime(&m_time);

	if(!t) return -1;

	return t->tm_mon + 1;
}

ulong Time::getDay()
{
	tm* t;
	t = localtime(&m_time);

	if(!t) return -1;

	return t->tm_mday;
}

ulong Time::getHour()
{
	tm* t;
	t = localtime(&m_time);

	if(!t) return -1;

	return t->tm_hour;
}

ulong Time::getMinute()
{
	tm* t;
	t = localtime(&m_time);

	if(!t) return -1;

	return t->tm_min;
}

ulong Time::getSecond()
{
	tm* t;
	t = localtime(&m_time);

	if(!t) return -1;

	return t->tm_sec;
}

} // namespace util

} // namespace stream