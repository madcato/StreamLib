// BolsaPropiedades.h: interface for the PropertyBag class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOLSAPROPIEDADES_H__2E8656B6_BEFF_40CF_81FB_3B1DF301938A__INCLUDED_)
#define AFX_BOLSAPROPIEDADES_H__2E8656B6_BEFF_40CF_81FB_3B1DF301938A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{
namespace exceptions
{
	/**
		Exception thrown by the class BolsaPropiedades
	*/
	class PropertyBagException : public StreamException
	{
	public:
		PropertyBagException(const std::string& index):StreamException(-1,"Property not found: " + index)
		{
		}
	};
} // namespace exceptions

/// namespace util
namespace util
{

/**
	Use this class to store named properties. Each property has a name an a value. 
	Its name is use as index.
*/
template<class INDEX,class T>
class PropertyBag  
{
public:
	PropertyBag();
	virtual ~PropertyBag();

	/**
		Puts a new element.
		@param index name of the element.
		@param value value of the element.
	*/
	void put(const INDEX& index,const T& value);
	/**
		Returns an element. If there is no element that match the index specified an exception is thrown.
		@param index name of the element to retrive
		@return the element.
	*/
	T get(const INDEX& index)const throw(exceptions::PropertyBagException*);

	/**
		Const index operator.
		@return The element. If this element is not found an exception is thrown.
	*/
	const T& operator[](const INDEX& index) const;

	/**
		Index operator.
		@return The element. If this element is not found a new empty element is created.
	*/
	T& operator[](const INDEX& index);



	/**
		Removes an element
		@param index name of the element to remove
	*/
	void remove(const INDEX& index)throw(exceptions::PropertyBagException*);
	/**
		@return the number of elements stored
	*/
	long size() const;
protected:
	/// map of the elements
	std::map<INDEX,T> m_properties;

	/**
		Checks if the element exists. If doesn't, an exception is thrown
		@param index element to search
	*/
	void CheckElementExistence(const INDEX& index)throw(exceptions::PropertyBagException*);
};

/**
	Use this class to store named properties. Each property has a name an a value. 
	Its name is use as index. Each index can be used to store multiple values
*/
template<class INDEX,class T>
class MultiPropertyBag  
{
public:
	MultiPropertyBag();
	virtual ~MultiPropertyBag();

	/**
		Puts a new element.
		@param index name of the element.
		@param value value of the element.
	*/
	void put(const INDEX& index,const T& value);
	/**
		Returns an element. If there is no element that match the index specified an exception is thrown.
		@param index name of the element to retrive
		@return the list of elements.
	*/
	std::list<T> get(const INDEX& index)throw(exceptions::PropertyBagException*);

	/**
		Removes an element
		@param index name of the element to remove
	*/
	void remove(const INDEX& index)throw(exceptions::PropertyBagException*);
	/**
		@return the number of elements stored
	*/
	long size();
private:
	/// map of the elements
	std::multimap<INDEX,T> m_properties;

	/**
		Checks if the element exists. If doesn't, an exception is thrown
		@param index element to search
	*/
	void CheckElementExistence(const INDEX& index)throw(exceptions::PropertyBagException*);
};

template<class INDEX,class T>
PropertyBag<INDEX,T>::PropertyBag()
{

}
template<class INDEX,class T>
PropertyBag<INDEX,T>::~PropertyBag()
{
	m_properties.clear();
}

template<class INDEX,class T>
void PropertyBag<INDEX,T>::put(const INDEX& index,const T& value)
{
	m_properties.insert(std::pair<INDEX,T>(index,value));
}
template<class INDEX,class T>
T PropertyBag<INDEX,T>::get(const INDEX& index) const
{
	CheckElementExistence(index);
	return m_properties[index];
}
template<class INDEX,class T>
const T& PropertyBag<INDEX,T>::operator[](const INDEX& index) const
{
	CheckElementExistence(index);
	return m_properties[index];
}
template<class INDEX,class T>
T& PropertyBag<INDEX,T>::operator[](const INDEX& index)
{
	return m_properties[index];
}
template<class INDEX,class T>
void PropertyBag<INDEX,T>::remove(const INDEX& index)
{
	CheckElementExistence(index);
	m_properties.erase(index);	
}
template<class INDEX,class T>
long PropertyBag<INDEX,T>::size() const
{
	return m_properties.size();
}
template<class INDEX,class T>
void PropertyBag<INDEX,T>::CheckElementExistence(const INDEX& index)
{
	std::map<INDEX,T>::iterator it = m_properties.find(index);

	if(it == m_properties.end())
		throw new exceptions::PropertyBagException(index);
}
template<class INDEX,class T>
MultiPropertyBag<INDEX,T>::MultiPropertyBag()
{

}
template<class INDEX,class T>
MultiPropertyBag<INDEX,T>::~MultiPropertyBag()
{
	m_properties.clear();
}
template<class INDEX,class T>
void MultiPropertyBag<INDEX,T>::put(const INDEX& index,const T& value)
{
	m_properties.insert(std::pair<INDEX,T>(index,value));
}
template<class INDEX,class T>
std::list<T> MultiPropertyBag<INDEX,T>::get(const INDEX& index)
{
	CheckElementExistence(index);

	std::list<T> lista;
	std::multimap<INDEX,T>::iterator it = m_properties.find(index);

	while(it != m_properties.end())
	{
		lista.push_back(it->second);
		it++;
	}

	return lista;
}
template<class INDEX,class T>
void MultiPropertyBag<INDEX,T>::remove(const INDEX& index)
{
	CheckElementExistence(index);
	m_properties.erase(index);	
}
template<class INDEX,class T>
long MultiPropertyBag<INDEX,T>::size()
{
	return m_properties.size();
}
template<class INDEX,class T>
void MultiPropertyBag<INDEX,T>::CheckElementExistence(const INDEX& index)
{
	std::multimap<INDEX,T>::iterator it = m_properties.find(index);

	if(it == m_properties.end())
		throw new exceptions::PropertyBagException(index);
}

} // namespace util

} // namespace stream
#endif // !defined(AFX_BOLSAPROPIEDADES_H__2E8656B6_BEFF_40CF_81FB_3B1DF301938A__INCLUDED_)
