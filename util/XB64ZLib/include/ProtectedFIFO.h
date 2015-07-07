// ProtectedFIFO.h: interface for the ProtectedFIFO class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROTECTEDFIFO_H__52F473E7_EBAD_4612_AFF2_853A8F55CAA9__INCLUDED_)
#define AFX_PROTECTEDFIFO_H__52F473E7_EBAD_4612_AFF2_853A8F55CAA9__INCLUDED_

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
	Protected FIFO dequeue ready to be used in multithreading applications.
	Must be specified the maximun number of elements that could be stored in the dequeue.
*/
template<class T>
class ProtectedFIFO  
{
public:
	ProtectedFIFO(int max_number_of_elements);
	virtual ~ProtectedFIFO();

	/**
		Pop an element from the top of the dequeue.
		This function is thread-safe. If there isn't any element in the dequeue, the calling thread is blocked until any other thread calls Push function.
		@return an element.
	*/
	T Pop();
	/**
		Push an element to the back of the dequeue.
		This function is thread-safe. If the dequeue is full, the calling thread is blocked until any other thread calls Pop function..
	*/
	void Push(T data);

	/**
		Return the number of elements in the dequeue. This function is thread-safe.
		@return The number of elements in the dequeue.
	*/
	size_t Size();


protected:
	CriticalSection m_criSec;
	HANDLE m_semaphoreReaders;
	HANDLE m_semaphoreWriters;
	
	std::list<T> m_pila;
};


template<class T>
ProtectedFIFO<T>::ProtectedFIFO(int max_number_of_elements)
{

	m_semaphoreReaders = CreateSemaphore(NULL,0,max_number_of_elements,0);
	m_semaphoreWriters = CreateSemaphore(NULL,max_number_of_elements,max_number_of_elements,0);
	

}

template<class T>
ProtectedFIFO<T>::~ProtectedFIFO()
{
	CloseHandle(m_semaphoreReaders);
	CloseHandle(m_semaphoreWriters);	
}



template<class T>
T ProtectedFIFO<T>::Pop()
{
	
	WaitForSingleObject(m_semaphoreReaders,INFINITE);
	
	m_criSec.Lock();

	T data = *(m_pila.begin());
	m_pila.pop_front();
	
	m_criSec.Unlock();

	
	ReleaseSemaphore(m_semaphoreWriters,1,0);
	
	
	return data;
}

template<class T>
void ProtectedFIFO<T>::Push(T data)
{

	WaitForSingleObject(m_semaphoreWriters,INFINITE);

	m_criSec.Lock();

	m_pila.push_back(data);

	m_criSec.Unlock();

	ReleaseSemaphore(m_semaphoreReaders,1,0);
}

template<class T>
size_t ProtectedFIFO<T>::Size()
{
	m_criSec.Lock();
	size_t tam = m_pila.size();
	m_criSec.Unlock();

	return tam;

}

} // namespace sync

} // namespace stream
#endif // !defined(AFX_PROTECTEDFIFO_H__52F473E7_EBAD_4612_AFF2_853A8F55CAA9__INCLUDED_)
