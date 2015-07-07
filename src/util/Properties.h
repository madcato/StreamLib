// Properties.h: interface for the Properties class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROPERTIES_H__4670637E_F646_41D5_B122_6CE0779EDCEB__INCLUDED_)
#define AFX_PROPERTIES_H__4670637E_F646_41D5_B122_6CE0779EDCEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/// namespace stream
namespace stream
{

/// namespace util
namespace util
{

/**
	The Properties class represents a persistent set of properties. The Properties can be saved to a stream or loaded from a stream. Each key and its corresponding value in the property list is a string. 
*/
class Properties : public PropertyBag<std::string,std::string>
{
public:
	Properties();
	virtual ~Properties();

	/**
		Add the properties of the 'param' object to this object.		
	*/
	Properties& add(const Properties& param);

	/**
		Searches for the property with the specified key in this property list. If the key is not found in this property list, returns the defaulValue param.
		@param key the property key. 
		@param defaulValue a default value.
		@return the value in this property list with the specified key value.
	*/
	std::string getProperty(const std::string& key,const std::string& defaultValue = "") const;

	/**
		Inserts a new key/value pair in the property list.
		@param key the key to be placed into this property list.
		@param value the value corresponding to key.
	*/
	void setProperty(const std::string& key,const std::string& value);

	/**
		@return Returns an enumeration of all the keys in this property list.
	*/
	std::vector<std::string> propertyNames() const;

	/**
		Removes a property.
	*/
	void removeProperty(const std::string& param);

	/**
		Converts this Property object in a map<string,string> object.
		@return a map object with a copy of the properties.
	*/
	std::map<std::string,std::string> getMap();

	/**
		Sets the values of this Property object.
		@param values a map object with the new pair values.
	*/
	void setMap(const std::map<std::string,std::string>& values);


};

} // namespace util

} // namespace stream

#endif // !defined(AFX_PROPERTIES_H__4670637E_F646_41D5_B122_6CE0779EDCEB__INCLUDED_)
