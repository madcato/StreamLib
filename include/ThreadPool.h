// ThreadPool.h: interface for the CThreadPool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THREADPOOL_H__6333F977_5182_4D94_B412_2C358B7D70D7__INCLUDED_)
#define AFX_THREADPOOL_H__6333F977_5182_4D94_B412_2C358B7D70D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CThreadPool : public stream::sync::Thread
{
public:
	CThreadPool();
	virtual ~CThreadPool();

	void Start();

	int ActiveCount();
	
	void Destroy();
	void Join()throw(char*);
	void Join(long millis)throw(char*);
	
	
	void Suspend();
	void Resume();
 
	virtual void Run();

private:
	std::vector<stream::sync::Thread*> m_vectorThreads;
};

#endif // !defined(AFX_THREADPOOL_H__6333F977_5182_4D94_B412_2C358B7D70D7__INCLUDED_)
