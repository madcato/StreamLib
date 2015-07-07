// CountReferencedBlob.h: interface for the CountReferencedBlob class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COUNT_REF_BLOB_H__34908D48_DA1A_4966_A2DF_9924F5C53410__INCLUDED_)
#define AFX_COUNT_REF_BLOB_H__34908D48_DA1A_4966_A2DF_9924F5C53410__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{

/**
 Provides for system input and output through data streams, serialization and the file system. 
*/
namespace io
{

/** 
	This class represents a large number of elements. The data is referenced counted so if no references exists, is disposed .
*/
template<class _Ty>
class CountReferencedBlob
{
public:
	/**
		Constructor
	*/
	CountReferencedBlob()
	{
		m_data = util::ref_count_ptr<io::Blob<_Ty> >(new io::Blob<_Ty>);
	}

	/**
		Constructor. Initilize de vector
	*/
	CountReferencedBlob(unsigned long dataCapacity)
	{
		m_data = util::ref_count_ptr<io::Blob<_Ty> >(new io::Blob<_Ty>);

		m_data->resize(dataCapacity);
	}

	/**
		Copy constructor
		@param blob CountReferencedBlob object to copy
	*/
	CountReferencedBlob(const CountReferencedBlob<_Ty>& blob)
	{
		m_data = blob.m_data;
	}

	/**
		Cast operator for char arrays.
		@return A new CountReferencedBlob obejct
	*/
	operator CountReferencedBlob<char>()
	{
		CountReferencedBlob<char> blob;
		blob.attach((char*)m_data.get()->get(),m_data->length());


		return blob;
	}

	/**
		Assignament operator
		@param blob CountReferencedBlob object to copy
	*/
	CountReferencedBlob<_Ty>& operator=(const CountReferencedBlob<_Ty>& blob)
	{
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
		m_data->resize(capacity);		
	}

	/**
		@return the buffer
	*/
	_Ty* get() const {return m_data->get();}

	/**
		@param offset The offset of the data to retrive
		@return the buffer
	*/
	_Ty* get(size_t offset) const {return m_data->get(offset);}

	/**
		@return the size of the data.
	*/
	long length() const {return m_data->length();}

	/**
		Sets the size of the data.
	*/
	void setLength(long size){m_data->setLength(size);}

	/**
		@return the capacity of he buffer.
	*/
	long capacity() const {return m_data->capacity();}
	
	/**
		Sets the buffer and the data length of this object.
		@param data the buffer of data
		@param dataLength the data length
	*/
	void setData(const util::auto_array_ptr<_Ty>& data,long dataLength)
	{
		m_data->setData(data,dataLength);		
	}

	/**
		Sets the buffer and the data length of this object with the string passed.
		@param data string where the new data is in.		
	*/
	void setData(const std::string& data)
	{
		m_data->setData(data);
	}

	/**
		Index operator
	*/
	_Ty& operator[](int index){return m_data->operator[](index);}

	/**
		Constant index operator
	*/
	_Ty operator[](int index) const {return (*m_data.get())[index];}

	/**
		Attachs the data at the end of this CountReferencedBlob.
	*/
	void attach(_Ty* data,int size)
	{
		m_data->attach(data,size);
	}

	/**
		Cuts the blob. The resulting CountReferencedBlob only has the data from 'firstPos' to 'firstPosition' + 'length'.
		If 'firstPosition' is less than actual length, and empty CountReferencedBlob is created. If 'firstPosition' + 'length'
		is greater than the actual size of the CountReferencedBlob, only the existing data will be copied, then the new length of the data
		will be actual 'length' - 'firstPos'.
		@param firstPos First position to cut.
		@param length Number of positions to remain in the blob.
	*/
	CountReferencedBlob<_Ty> cut(long firstPos,long length)
	{
		CountReferencedBlob<_Ty> rBLOB;
		(*rBLOB.m_data.get()) = m_data->cut(firstPos,length);

		return rBLOB;
	}

	/**
		@return The data of this CountReferencedBlob in a string object
	*/
	operator std::string()
	{
		return (std::string)(*m_data.get());
	}
private:
	/**
		The buffer
	*/
	util::ref_count_ptr<io::Blob<_Ty> > m_data;

	friend class CountReferencedBlob<char>;
};

} // namespace io

} // namespace stream

#endif // !defined(AFX_COUNT_REF_BLOB_H__34908D48_DA1A_4966_A2DF_9924F5C53410__INCLUDED_)
