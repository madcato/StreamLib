// Thread.cpp: implementation of the Thread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Exceptions.h"

#include "Thread.h"

#include "CriticalSection.h"
#include "memory_stream.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


namespace stream
{
/// namespace sync
namespace sync
{
std::map<DWORD,Thread*> Thread::m_map;

int Thread::m_countThreads = 0;

Thread::Thread()
{
	m_threadHandle = 0;

}

Thread::~Thread()
{
m_countThreads--;
}


void Thread::start()
{
	
	m_threadHandle = CreateThread(0,0,&run2,this,0,&m_threadId);

	m_map.insert(std::pair<DWORD,Thread*>(m_threadId,this));
	m_countThreads++;
		
}

DWORD WINAPI Thread::run2(void* obj)
{
	((Thread*)obj)->run();
	return 0;
}


int Thread::activeCount()
{
	return m_countThreads;
}
Thread* Thread::currentThread()
{
	return m_map[GetCurrentThreadId()];
}
void Thread::destroy()
{
	TerminateThread(m_threadHandle,-1);
	
}
void Thread::join()
{
	join(INFINITE);
}

void Thread::suspend()
{
	SuspendThread(m_threadHandle);
}

void Thread::resume()
{
	ResumeThread(m_threadHandle);
}

bool Thread::join(long millis)
{
	if(this == currentThread())
	{
		throw exceptions::ThreadException("Un hilo no puede esperar a que se termine el mismo.");
	}
	if(WaitForSingleObject(m_threadHandle,millis) == WAIT_TIMEOUT)
	{
		return false;
	}

	return true;
}

void Thread::joinAll(long millis)
{
	std::map<DWORD,Thread*>::iterator it = m_map.begin();
	
	std::vector<Thread*> vec;

	int i = 0;
	while(it != m_map.end())
	{
		vec.push_back(it->second);

		it++;
	}

	multipleJoin(m_map.size(),vec,true,millis);
}
void Thread::sleep(long millis)
{
	::Sleep(millis);	
}

int Thread::multipleJoin(long nCount,             // number of handles in array
					std::vector<Thread*> lpHandles,  // object-handle array
					bool bWaitAll,            // wait option
					long dwMilliseconds      // time-out interval
					)
{

	util::auto_array_ptr<HANDLE> vec(nCount);
	Thread* t = currentThread();
	for(int i = 0 ; i < nCount ; i++)
	{
		if(lpHandles[i] == t)
		{
			throw exceptions::ThreadException("Un hilo no puede esperar a que se termine el mismo.");
		}

		vec[i] = lpHandles[i]->m_threadHandle;
	}

	
	DWORD ret = WaitForMultipleObjects(
			nCount,             // number of handles in array
			vec.get(),  // object-handle array
			bWaitAll,            // wait option
			dwMilliseconds      // time-out interval
			);

	return ret;

}

CONTEXT* Thread::getThreadContext()
{
	CONTEXT* Context = new CONTEXT;

	suspend();

	if(!GetThreadContext(m_threadHandle,Context))
		throw exceptions::Win32ErrorException(__FILE__,__LINE__);

	resume();
	return Context;
}

} // namespace sync

} // namespace stream