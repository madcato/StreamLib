// Semaphore.h: interface for the Semaphore class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEMAPHORE_H__E9ACA9CB_4B15_42E3_B0CB_7D60380FF7AB__INCLUDED_)
#define AFX_SEMAPHORE_H__E9ACA9CB_4B15_42E3_B0CB_7D60380FF7AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{
/// namespace sync
namespace sync
{
/**
	Semaphore section ready to be used in multithreading applications.
*/

class Semaphore  
{
public:
	Semaphore(long lInitialCount, long lMaximumCount ,std::string name);
	virtual ~Semaphore();

	void release(long lReleaseCount = 1,long* lpPreviousCount = 0);
	unsigned long enter(unsigned long dwMilliseconds = INFINITE);

private:
	HANDLE m_handle;
};

} // namespace sync

} // namespace stream
#endif // !defined(AFX_SEMAPHORE_H__E9ACA9CB_4B15_42E3_B0CB_7D60380FF7AB__INCLUDED_)
