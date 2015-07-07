#ifndef __CRITICALSECTION_H
#define __CRITICALSECTION_H

/// namespace stream
namespace stream
{

/**
 Provides classes that provides multithreading and syncronization.
*/
namespace sync
{
/**
	Critical section ready to be used in multithreading applications.
*/
class CriticalSection
{
public:
	CriticalSection()
	{
		InitializeCriticalSection(&m_csCriticalSection);
			
	}
	~CriticalSection()
	{
		DeleteCriticalSection(&m_csCriticalSection);			
	}

	/**
		Leaves the critical section.
	*/
	void unlock(void) 
	{
		LeaveCriticalSection(&m_csCriticalSection);
	}
	/**
		Enters the critical section.
	*/
	void lock(void) 
	{
		EnterCriticalSection(&m_csCriticalSection);
		if(m_csCriticalSection.LockCount < 0)
		{
			int a = 0;
		}

	}

private:
	CRITICAL_SECTION m_csCriticalSection;

};

} // namespace sync

} //namespace stream
#endif __CRITICALSECTION_H