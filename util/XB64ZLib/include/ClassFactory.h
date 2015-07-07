// ClassFactory.h: interface for the ClassFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLASSFACTORY_H__D73B6F90_F504_4005_93E7_7C4176B3AF37__INCLUDED_)
#define AFX_CLASSFACTORY_H__D73B6F90_F504_4005_93E7_7C4176B3AF37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/// namespace stream
namespace stream
{

/// namespace exceptions
namespace exceptions
{
	class ClassFactoryException : public StreamException
	{
	public:
		ClassFactoryException(int id_code,std::string desc = ""):StreamException(id_code,desc){}
		virtual ~ClassFactoryException(){}
	};
} /// namespace exceptions

/// namespace util
namespace util
{

template<class T>
class ClassFactoryT;

/**
	This class can be used to provide a method to create classes dynamicly.
	To used this feature, implement a new class. It`s not neccesary to implement
	any interface.
	Then use the macro REGISTER_CLASS(className) in the global scope and then
	instances of this new class can be obtained by calling:	
	<code>
	className* obj = ClassFactory::createObject("className");
	</code>
*/
class ClassFactory
{
public:
	ClassFactory();
	virtual ~ClassFactory();

	
	/**
		Call this method to create a new object instance dynamicly.
		@param classId Class identification.
		@return The new object. Make a dynamic_cast to access its methods.
	*/
	static void* createObject(const std::string& classId);

protected:
	virtual void* newObject() = 0;

private:
	static std::map<const std::string,ClassFactory*>* g_mapObjects;
	static registerClass(const std::string& classId,ClassFactory* obj);


	friend class ClassFactoryT;
};


template<class T>
class ClassFactoryT : public ClassFactory
{
public:
	ClassFactoryT();
	virtual ~ClassFactoryT(){}

protected:
	virtual void* newObject();
};

template<class T>
ClassFactoryT<T>::ClassFactoryT()
{
	ClassFactory::registerClass(T::classId(),this);
}

template<class T>
void* ClassFactoryT<T>::newObject()
{
	return new T;
}

#define REGISTER_CLASS(T) ClassFactoryT<##T> g_registeredClass##T;

} // namespace util

} // namespace std

#endif // !defined(AFX_CLASSFACTORY_H__D73B6F90_F504_4005_93E7_7C4176B3AF37__INCLUDED_)
