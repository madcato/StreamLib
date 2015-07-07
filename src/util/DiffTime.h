// DiffTime.h: interface for the DiffTime class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIFFTIME_H__104FFE07_4E72_433C_B0DC_86B45ECBEC09__INCLUDED_)
#define AFX_DIFFTIME_H__104FFE07_4E72_433C_B0DC_86B45ECBEC09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{

/// namespace util
namespace util
{

/**
	This class provides methods to calculate the elapsed time between two different 
	moments.
*/
class DiffTime  
{
public:
	DiffTime();
	virtual ~DiffTime();

	/**
		Start counting the wall-clock time.
	*/
	void start();

	/**
		Calculates the amount of loop since the previous call to @see start.
		@return the amount of timer ticks.
	*/
	ulong finish();

private:
	ulong m_starting;

};

} // namespace util

} // namespace stream

#endif // !defined(AFX_DIFFTIME_H__104FFE07_4E72_433C_B0DC_86B45ECBEC09__INCLUDED_)
