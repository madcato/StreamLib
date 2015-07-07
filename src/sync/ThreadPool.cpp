// ThreadPool.cpp: implementation of the CThreadPool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Exceptions.h"
#include "Thread.h"

#include "ThreadPool.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CThreadPool::CThreadPool()
{

}

CThreadPool::~CThreadPool()
{
	m_vectorThreads.clear();
}


void CThreadPool::Start()
{
	std::vector<stream::sync::Thread*>::iterator it = m_vectorThreads.begin();

	while(it != m_vectorThreads.end())
	{
		(*it)->start();
		it++;
	}

}

int CThreadPool::ActiveCount()
{
	return m_vectorThreads.size();
}

void CThreadPool::Destroy()
{
	std::vector<stream::sync::Thread*>::iterator it = m_vectorThreads.begin();

	while(it != m_vectorThreads.end())
	{
		(*it)->destroy();
		it++;
	}
}
void CThreadPool::Join()throw(char*)
{
	Join(INFINITE);
}
void CThreadPool::Join(long millis)throw(char*)
{
	std::vector<stream::sync::Thread*> pool;

	
	std::vector<stream::sync::Thread*>::iterator it = m_vectorThreads.begin();
	int i = 0;
	while(it != m_vectorThreads.end())
	{
		pool.push_back(*it);
		it++;
	}


	Thread::multipleJoin(m_vectorThreads.size(),             // number of handles in array
					pool,  // object-handle array
					true,            // wait option
					INFINITE// time-out interval
					);

}


void CThreadPool::Suspend()
{
	std::vector<stream::sync::Thread*>::iterator it = m_vectorThreads.begin();

	while(it != m_vectorThreads.end())
	{
		(*it)->suspend();
		it++;
	}
}
void CThreadPool::Resume()
{
	std::vector<stream::sync::Thread*>::iterator it = m_vectorThreads.begin();

	while(it != m_vectorThreads.end())
	{
		(*it)->resume();
		it++;
	}
}

void CThreadPool::Run()
{
}
