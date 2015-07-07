// Time.h: interface for the Time class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIME_H__C23BF5E8_612E_443B_A0B5_FC73B8A9529B__INCLUDED_)
#define AFX_TIME_H__C23BF5E8_612E_443B_A0B5_FC73B8A9529B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace stream
{

/// namespace util
namespace util
{

/**
	Time class.
	This class can be used to acces for the current date and time.
*/
class Time
{
public:
	/**
		Cosntructor
		Initializes with the currente date and time.
	*/
	Time();
	/**
		Destructor
	*/
	virtual ~Time();

	/**
		Return current date an time. Format "d/m/Y H:M:S".
		@return The time str.
	*/
	static std::string today();

	/**
		Adds days to the current date
		@param days quantity to add
	*/
	void addDays(ulong days);
	/**
		Adds hours to the current date
		@param hours quantity to add
	*/
	void addHours(ulong hours);
	/**
		Adds minutes to the current date
		@param minutes quantity to add
	*/
	void addMinutes(ulong minutes);
	/**
		Adds seconds to the current date
		@param seconds quantity to add
	*/
	void addSeconds(ulong seconds);
	/**
		Calculates the difference between current date an t2
		@param t2 Time to compare
		@return The difference in seconds.
	*/
	ulong operator-(const Time& t2);

	/**
		@return Year. Above 1970
	*/
	ulong getYear();
	/**
		@return month. 1-12
	*/
	ulong getMonth();
	/**
		@return Days 1-31
	*/
	ulong getDay();
	/**
		@return Hours 0-23
	*/
	ulong getHour();
	/**
		@return Minutes 0-59
	*/
	ulong getMinute();
	/**
		@return Seconds 0-59
	*/
	ulong getSecond();

private:
	time_t m_time;
};

} // namespace util

} // namespace stream

#endif // !defined(AFX_TIME_H__C23BF5E8_612E_443B_A0B5_FC73B8A9529B__INCLUDED_)
