// Thread.h: interface for the Thread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THREAD_H__D007CEC9_CF3E_11D4_ADBF_00105AF120EC__INCLUDED_)
#define AFX_THREAD_H__D007CEC9_CF3E_11D4_ADBF_00105AF120EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{

	/// namespace exceptions
	namespace exceptions
	{
		/**
			ThreadExcpetion
		*/
		class ThreadException : public StreamException
		{
		public:
			ThreadException(const std::string& str):StreamException(-1,str)
			{
			}
		};
	}
/// namespace sync
namespace sync
{
/**
	This class is a thread of execution in a program.
	To create a new thread of execution must declare a class to be a subclass of Thread.
	This subclass should override the <b>run</b> method of class Thread. 
	An instance of the subclass can then be allocated and started. 
	For example:
<code>
     class PrimeThread : public Thread <br>
	 {<br>
	 public:<br>
         &nbsp;&nbsp;long m_minPrime;<br>
         &nbsp;&nbsp;PrimeThread(long minPrime) {<br>
             &nbsp;&nbsp;&nbsp;&nbsp;m_minPrime = minPrime;<br>
         &nbsp;&nbsp;}<br>
 <br>
         &nbsp;&nbsp;void run() {<br>
             &nbsp;&nbsp;&nbsp;&nbsp;Thread start point here<br>
              . . .<br>
         &nbsp;&nbsp;}<br>
     }<br>
</code><br>
	The following code would then create a thread and start it running: 

<code>
     PrimeThread p = new PrimeThread(143);<br>
     p.start();<br>
</code>
*/
class Thread
{
public:
	/**
		Constructor of a Thread object
	*/
	Thread();
	/**
		Destructor of a Thread object
	*/
	virtual ~Thread();

	/**
		Causes this thread to begin execution and calls the run method of this thread. 
	*/
	void start();
	/**
		Returns the number of active threads in the current thread's thread group
		@return the number of active threads in the current thread's thread group
	*/
	static int activeCount();

	/**
		Returns a reference to the currently executing thread object.
		@return the currently executing thread.
	*/
	static Thread* currentThread();

	/**
		Terminate this thread. The calling thread continues execution, the destroyed one
		is the handled by this object
	*/
	void destroy();
	/**
		This method makes that the calling thread waits for this thread to die.
	*/
	void join();
	/**
		This method makes that the calling thread waits <b>millis</b> miliseconds for this thread to die.
		@param millis Number of miliseconds to wait for the thread end.
		@return true if the thread ends, false if timeout.
	*/
	bool join(long millis);

	/**
		This method makes that the calling thread waits <b>millis</b> miliseconds for all 
		the current created threads by this class to die.
		@param millis Number of miliseconds to wait for the thread end.
	*/
	static void joinAll(long millis);

	/**
		To wait multiple Thread call this method setting <b>lpHandles</b> 
		with the pointers of the thread to wait for end.
		@param nCount Number of pointers in <b>lpHandles</b>,
		@param lpHandles thread pointer array
		@param bWaitAll Set to <b>true</b> to wait for all the threads in <b>lpHandles</b>.
			Set to <b>false</b> to wait for the first ending thread.
		@param dwMilliseconds Number of milliseconds to wait for threads. Set to zero to not exit for time-out.
		@return If the function succeeds, the return value indicates the event that caused the function to return. It can be one of the following values.
	*/
	static int multipleJoin(long nCount,             // number of handles in array
					std::vector<Thread*> lpHandles,  // object-handle array
					bool bWaitAll,            // wait option
					long dwMilliseconds      // time-out interval
					);

	/**
		Suspends the execution of calling thread <b>millis</b> milliseconds.
		@param millis Number of milliseconds to sleep.
	*/
	static void sleep(long millis);

	/**
		Suspends this thread.
	*/
	void suspend();

	/**
		Resume this thread.
	*/
	void resume();
 
 
	CONTEXT* getThreadContext();
protected:

	/**
		This pure virtual method must be implemented by the derived classes to specify the 
		entry point of the thread.
	*/
	virtual void run() = 0;

private:
	static DWORD WINAPI run2(void* obj);
	static int m_countThreads;



	HANDLE m_threadHandle;
	DWORD m_threadId;

	static std::map<DWORD,Thread*> m_map;
};

} // namespace sync

} // namespace stream
#endif // !defined(AFX_THREAD_H__D007CEC9_CF3E_11D4_ADBF_00105AF120EC__INCLUDED_)
