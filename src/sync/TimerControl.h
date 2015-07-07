// TimerControl1.h: interface for the TimerControl1 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIMERCONTROL1_H__82B47317_EE31_4EBA_BD3E_68337263237E__INCLUDED_)
#define AFX_TIMERCONTROL1_H__82B47317_EE31_4EBA_BD3E_68337263237E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/// namespace stream
namespace stream
{

/// namespace sync
namespace sync
{


/*
int MyTimerProc(HWND hwnd,UINT uMsg,UINT_PTR idEvent,DWORD dwTime)
{
	g_events.OnSecond();
	
	return 0;
}*/

/**
	Class TimerControl creates a system timer.

	No funciona en aplicaciones consola.
*/
class TimerControl
{
public:

	/** 
		Constructor.		

	*/
	TimerControl();

	/**
		Starts calling mothod tick each in an interval of miliseconds.
		@param miliseconds Number of miliseconds between each call to 'tick' function.
	*/
	void init(long miliseconds);
	/**
		Finish the timer.
	*/
	void finish();
	/**
		Destructor.
	*/
	~TimerControl();

	/**
		This method is called each time the elapsed time is completed. 
		This method must be implemented by derived classes.
	*/
	virtual int tick() = 0;
	

private:
	int m_timer;

	static std::map<int,TimerControl*> m_registeredObjects;
	static int tick_internal(HWND hwnd,UINT uMsg,UINT_PTR idEvent,DWORD dwTime);
};

} // namespace sync

} // namespace stream

#endif // !defined(AFX_TIMERCONTROL1_H__82B47317_EE31_4EBA_BD3E_68337263237E__INCLUDED_)
