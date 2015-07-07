// BolsaPropiedades.h: interface for the CBolsaPropiedades class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOLSAPROPIEDADES_H__2E8656B6_BEFF_40CF_81FB_3B1DF301938A__INCLUDED_)
#define AFX_BOLSAPROPIEDADES_H__2E8656B6_BEFF_40CF_81FB_3B1DF301938A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace Stream
{
namespace Exceptions
{
	class BolsaPropiedadesException : public StreamException
	{
	public:
		BolsaPropiedadesException(const std::string& index):StreamException(-1,"Property not found: " + index)
		{
		}
	};
} // namespace Exceptions

template<class INDEX,class T>
class CBolsaPropiedades  
{
public:
	CBolsaPropiedades();
	virtual ~CBolsaPropiedades();

	void put(const INDEX& index,const T& value);
	T get(const INDEX& index)throw(Exceptions::BolsaPropiedadesException*);

	void remove(const INDEX& index)throw(Exceptions::BolsaPropiedadesException*);
	long size();
private:
	std::map<INDEX,T> m_bolsaCadenas;

	void CheckElementExistence(const INDEX& index)throw(Exceptions::BolsaPropiedadesException*);
};

template<class INDEX,class T>
class CMultiBolsaPropiedades  
{
public:
	CMultiBolsaPropiedades();
	virtual ~CMultiBolsaPropiedades();

	void put(const INDEX& index,const T& value);
	std::list<T> get(const INDEX& index)throw(Exceptions::BolsaPropiedadesException*);

	void remove(const INDEX& index)throw(Exceptions::BolsaPropiedadesException*);
	long size();
private:
	std::multimap<INDEX,T> m_bolsaCadenas;

	void CheckElementExistence(const INDEX& index)throw(Exceptions::BolsaPropiedadesException*);
};

template<class INDEX,class T>
CBolsaPropiedades<INDEX,T>::CBolsaPropiedades()
{

}
template<class INDEX,class T>
CBolsaPropiedades<INDEX,T>::~CBolsaPropiedades()
{
	m_bolsaCadenas.clear();
}

template<class INDEX,class T>
void CBolsaPropiedades<INDEX,T>::put(const INDEX& index,const T& value)
{
	m_bolsaCadenas.insert(std::pair<INDEX,T>(index,value));
}
template<class INDEX,class T>
T CBolsaPropiedades<INDEX,T>::get(const INDEX& index)
{
	CheckElementExistence(index);
	return m_bolsaCadenas[index];
}
template<class INDEX,class T>
void CBolsaPropiedades<INDEX,T>::remove(const INDEX& index)
{
	CheckElementExistence(index);
	m_bolsaCadenas.erase(index);	
}
template<class INDEX,class T>
long CBolsaPropiedades<INDEX,T>::size()
{
	return m_bolsaCadenas.size();
}
template<class INDEX,class T>
void CBolsaPropiedades<INDEX,T>::CheckElementExistence(const INDEX& index)
{
	std::map<INDEX,T>::iterator it = m_bolsaCadenas.find(index);

	if(it == m_bolsaCadenas.end())
		throw Exceptions::BolsaPropiedadesException(index);
}
template<class INDEX,class T>
CMultiBolsaPropiedades<INDEX,T>::CMultiBolsaPropiedades()
{

}
template<class INDEX,class T>
CMultiBolsaPropiedades<INDEX,T>::~CMultiBolsaPropiedades()
{
	m_bolsaCadenas.clear();
}
template<class INDEX,class T>
void CMultiBolsaPropiedades<INDEX,T>::put(const INDEX& index,const T& value)
{
	m_bolsaCadenas.insert(std::pair<INDEX,T>(index,value));
}
template<class INDEX,class T>
std::list<T> CMultiBolsaPropiedades<INDEX,T>::get(const INDEX& index)
{
	CheckElementExistence(index);

	std::list<T> lista;
	std::multimap<INDEX,T>::iterator it = m_bolsaCadenas.find(index);

	while(it != m_bolsaCadenas.end())
	{
		lista.push_back(it->second);
		it++;
	}

	return lista;
}
template<class INDEX,class T>
void CMultiBolsaPropiedades<INDEX,T>::remove(const INDEX& index)
{
	CheckElementExistence(index);
	m_bolsaCadenas.erase(index);	
}
template<class INDEX,class T>
long CMultiBolsaPropiedades<INDEX,T>::size()
{
	return m_bolsaCadenas.size();
}
template<class INDEX,class T>
void CMultiBolsaPropiedades<INDEX,T>::CheckElementExistence(const INDEX& index)
{
	std::multimap<INDEX,T>::iterator it = m_bolsaCadenas.find(index);

	if(it == m_bolsaCadenas.end())
		throw Exceptions::BolsaPropiedadesException(index);
}


} // namespace Stream
#endif // !defined(AFX_BOLSAPROPIEDADES_H__2E8656B6_BEFF_40CF_81FB_3B1DF301938A__INCLUDED_)
