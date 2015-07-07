// Blob.h: interface for the Blob class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BLOB_H__34908D48_DA1A_4966_A2DF_9924F5C53410__INCLUDED_)
#define AFX_BLOB_H__34908D48_DA1A_4966_A2DF_9924F5C53410__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace Stream
{

namespace Exceptions
{
	class BLOBException : public StreamException
	{
	public:
		BLOBException(int id_code,std::string desc = ""):StreamException(id_code,desc)
		{}
	};
} // namespace Exceptions


template<class _Ty>
class Blob
{
public:
	Blob()
	{
		m_dataLength = 0;
	}

	Blob(const Blob<_Ty>& blob)
	{
		m_dataLength = blob.m_dataLength;
		m_data = blob.m_data;
	}

	Blob<_Ty>& operator=(const Blob<_Ty>& blob)
	{
		m_dataLength = blob.m_dataLength;
		m_data = blob.m_data;
	}
		
	void resize(long capacity)
	{
		if(capacity > m_data.capacity())
		{
			auto_array_ptr<_Ty> paso(capacity);
			memcpy(paso.get(),m_data.get(),m_data.capacity());
			m_data = paso;
		}
		else
		{
			m_dataLength = m_dataLength < capacity ? m_dataLength : capacity;
		}
	}

	_Ty* get() const {return m_data.get();}

	long size() const {return m_dataLength;}

	void setSize(long size){m_dataLength = size;}

	long capacity() const {return m_data.capacity();}
	
	void setData(const auto_array_ptr<_Ty>& data,long dataLength)
	{
		m_data = data;
		m_dataLength = dataLength;
	}

	_Ty& operator[](int index){return m_data[index];}

	_Ty operator[](int index) const {return m_data[index];}

private:
	auto_array_ptr<_Ty> m_data;
	long m_dataLength;
};


} // namespace Stream

#endif // !defined(AFX_BLOB_H__34908D48_DA1A_4966_A2DF_9924F5C53410__INCLUDED_)
