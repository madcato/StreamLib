// Semaphore.cpp: implementation of the Semaphore class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Exceptions.h"

#include "Semaphore.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace stream
{
/// namespace sync
namespace sync
{
Semaphore::Semaphore(long lInitialCount, long lMaximumCount ,std::string name)
{

	m_handle = ::CreateSemaphore(0,lInitialCount,lMaximumCount,name.c_str());

	if(m_handle == 0)
	{
		throw new exceptions::Win32ErrorException(__FILE__,__LINE__);
	}

}

Semaphore::~Semaphore()
{

	::CloseHandle(m_handle);
}


void Semaphore::release(long lReleaseCount,long* lpPreviousCount)
{

	long* pdata;
	long data;
	if(lpPreviousCount == 0)
	{
		pdata = &data;
	}
	else
	{
		pdata = lpPreviousCount;
	}

	int result = ::ReleaseSemaphore(m_handle,lReleaseCount,pdata);

	if(result == 0)
	{
		throw new exceptions::Win32ErrorException(__FILE__,__LINE__);
	}
}


unsigned long Semaphore::enter(unsigned long dwMilliseconds)
{

	return ::WaitForSingleObject(m_handle,dwMilliseconds);

}

} // namespace sync

} // namespace stream