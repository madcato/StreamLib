// PersistentProperties.h: interface for the PersistentProperties class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PERSISTENTPROPERTIES_H__2A450657_7D23_4728_8E6C_C51056375818__INCLUDED_)
#define AFX_PERSISTENTPROPERTIES_H__2A450657_7D23_4728_8E6C_C51056375818__INCLUDED_

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
	This class extends Properties class to supply two methods for reading and writing the properties from/to
	a InputStream/OutputStream.
*/
class PersistentProperties : public Properties
{
public:
	PersistentProperties();
	virtual ~PersistentProperties();

	/**
		Reads a property list (key and element pairs) from the input stream.
	*/
	void load(std::auto_ptr<io::IInputStream> inStream);

	/**
		Writes this property list (key and element pairs) in this Properties table to the output stream.
	*/
	void save(std::auto_ptr<io::IOutputStream> outStream);
};

} // namespace util

} // namespace stream

#endif // !defined(AFX_PERSISTENTPROPERTIES_H__2A450657_7D23_4728_8E6C_C51056375818__INCLUDED_)
