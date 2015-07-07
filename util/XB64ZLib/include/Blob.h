// Blob.h: interface for the Blob class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BLOB_H__34908D48_DA1A_4966_A2DF_9924F5C53410__INCLUDED_)
#define AFX_BLOB_H__34908D48_DA1A_4966_A2DF_9924F5C53410__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{

/// namespace exceptions
namespace exceptions
{
	class BLOBException : public StreamException
	{
	public:
		BLOBException(int id_code,std::string desc = ""):StreamException(id_code,desc)
		{}
	};
} // namespace exceptions


/**
 Provides for system input and output through data streams, serialization and the file system. 
*/
namespace io
{

/** 
	This class represents a large number of elements.
*/

template<class _Ty>
class Blob
{
public:
	/**
		Constructor
	*/
	Blob()
	{
		m_dataLength = 0;
	}

	/**
		Copy constructor
		@param blob Blob object to copy
	*/
	Blob(const Blob<_Ty>& blob)
	{
		m_dataLength = blob.m_dataLength;
		m_data = blob.m_data;
	}

	/**
		Cast operator for char arrays.
		@return A new Blob obejct
	*/
	operator Blob<char>()
	{
		Blob<char> blob;
		blob.setData((util::auto_array_ptr<char>)m_data,m_dataLength);

		return blob;
	}

	/**
		Assignament operator
		@param blob Blob object to copy
	*/
	Blob<_Ty>& operator=(const Blob<_Ty>& blob)
	{
		m_dataLength = blob.m_dataLength;
		m_data = blob.m_data;
		return *this;
	}

	/** 
		Resizes the capacity of the blob.
		If the actual capacity is less than the new, a new buffer 
		is created an all data is copy.
		If the actual capacity is greater, then the capacity is not modified, 
		only the data length.
	*/
	void resize(long capacity)
	{
		int rest = capacity % 4096;
		if(rest)
		{
			capacity += 4096 - (rest);
		}
		if(capacity > m_data.capacity())
		{
			util::auto_array_ptr<_Ty> paso(capacity);
			memcpy(paso.get(),m_data.get(),m_data.capacity());
			m_data = paso;
		}
		else
		{
			//m_dataLength = m_dataLength < capacity ? m_dataLength : capacity;
		}
	}

	/**
		@return the buffer
	*/
	_Ty* get() const {return m_data.get();}

	/**
		@param offset The offset of the data to retirve
		@return the buffer
	*/
	_Ty* get(size_t offset) const {return m_data.get()+offset;}

	/**
		@return the size of the data.
	*/
	long length() const {return m_dataLength;}

	/**
		Sets the size of the data.
	*/
	void setLength(long size){m_dataLength = size;}

	/**
		@return the capacity of he buffer.
	*/
	long capacity() const {return m_data.capacity();}
	
	/**
		Sets the buffer and the data length of this object.
		@param data the buffer of data
		@param dataLength the data length
	*/
	void setData(const util::auto_array_ptr<_Ty>& data,long dataLength)
	{
		m_data = data;
		m_dataLength = dataLength;
	}

	/**
		Sets the buffer and the data length of this object.
		@param data the buffer of data
		@param dataLength the data length and buffer length.
	*/
	void setData(_Ty* data,long dataLength)
	{
		util::auto_array_ptr<_Ty> dataBuffer(dataLength,data);
		
		m_data = dataBuffer;
		m_dataLength = dataLength;
	}

	/**
		Sets the buffer and the data length of this object with the string passed.
		@param data string where the new data is in.		
	*/
	void setData(const std::string& data)
	{
		util::auto_array_ptr<_Ty> buffer(data.length(),(_Ty*)new char[data.length()]);
		memcpy(buffer.get(),data.c_str(),data.length());

		m_data = buffer;
		m_dataLength = data.length();
	}

	/**
		Index operator
	*/
	_Ty& operator[](int index){return m_data[index];}

	/**
		Constant index operator
	*/
	_Ty operator[](int index) const {return m_data[index];}

	/**
		Attachs the data at the end of this Blob.
	*/
	void attach(_Ty* data,int size)
	{
		resize(m_dataLength + size);

		memcpy(m_data.get() + m_dataLength,data,size);

		setLength(m_dataLength + size);
	}

	/**
		Cuts the blob. The resulting Blob only has the data from 'firstPos' to 'firstPosition' + 'length'.
		If 'firstPosition' is less than actual length, and empty Blob is created. If 'firstPosition' + 'length'
		is greater than the actual size of the Blob, only the existing data will be copied, then the new length of the data
		will be actual 'length' - 'firstPos'.
		@param firstPos First position to cut.
		@param length Number of positions to remain in the blob.
	*/
	Blob<_Ty> cut(long firstPos,long length)
	{
		Blob<_Ty> temporal;
		if(firstPos < m_dataLength)
		{
			temporal.attach(this->get() + firstPos, firstPos + length > m_dataLength? m_dataLength - firstPos : length);
		}

		return temporal;
	}

	/**
		@return The data of this Blob in a string object
	*/
	operator std::string()
	{
		resize(capacity()+1);
		(*this)[m_dataLength] = '\0';

		return (char*)m_data.get();
	}

	/**
		Transpose the order of the bytes: the first byte will be the last one.
	*/
	void transpose()
	{
		util::auto_array_ptr<_Ty> newData(m_data.capacity());
		for(int i = 0 ; i < m_dataLength ; i++)
		{
			newData[i] = m_data[(m_dataLength - i) - 1];
		}

		m_data = newData;
	}


private:
	/**
		The buffer
	*/
	util::auto_array_ptr<_Ty> m_data;
	/**
		The data length
	*/
	long m_dataLength;

	friend class Blob<char>;
};

/**
	Blob automatic pointer.
*/
template<class T>
typedef std::auto_ptr<Blob<T> > BlobPtr;

} // namespace io

} // namespace stream

#endif // !defined(AFX_BLOB_H__34908D48_DA1A_4966_A2DF_9924F5C53410__INCLUDED_)
