// IData.h: interface for the IData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IDATA_H__526180D6_BBA5_431C_A71F_5EF6D88AAF9B__INCLUDED_)
#define AFX_IDATA_H__526180D6_BBA5_431C_A71F_5EF6D88AAF9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{

/// namespace io
namespace io
{

/**
This class represents an object that holds any type of data storage.
Implementer classes must provide two methods to acces the input and output 
streams that provida access to hat data.
*/
class IData  
{
public:
	IData();
	virtual ~IData();

	/**
		@return The input stream.
	*/
	virtual std::auto_ptr<IInputStream> getInputStream() = 0;

	/**
		@return The output stream.
	*/
	virtual std::auto_ptr<IOutputStream> getOutputStream() = 0;
};

} // namespace io

} // namespace stream

#endif // !defined(AFX_IDATA_H__526180D6_BBA5_431C_A71F_5EF6D88AAF9B__INCLUDED_)
