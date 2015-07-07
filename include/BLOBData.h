// BLOBData.h: interface for the BLOBData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BLOBData_H__8817C75A_CEE8_4B33_8AF7_8AFDC842FE6B__INCLUDED_)
#define AFX_BLOBData_H__8817C75A_CEE8_4B33_8AF7_8AFDC842FE6B__INCLUDED_

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
This class represents a BLOB data acces.
*/
template<class _Ty>
class BLOBData : public IData  
{
public:
	BLOBData(util::ref_count_ptr<Blob<_Ty> > blob);
	virtual ~BLOBData();

	/**
		@return A FileInputStream object.
	*/
	virtual std::auto_ptr<IInputStream> getInputStream();

	/**
		@return A FileOutputStream object.
	*/
	virtual std::auto_ptr<IOutputStream> getOutputStream();

private:
	util::ref_count_ptr<Blob<_Ty> > m_blob;
};

template<class _Ty>
BLOBData<_Ty>::BLOBData(util::ref_count_ptr<Blob<_Ty> > blob):m_blob(blob)
{

}

template<class _Ty>
BLOBData<_Ty>::~BLOBData()
{

}

template<class _Ty>
std::auto_ptr<IInputStream> BLOBData<_Ty>::getInputStream()
{	
	return new BLOBInputStream(m_blob);
}

template<class _Ty>
std::auto_ptr<IOutputStream> BLOBData<_Ty>::getOutputStream()
{
	return new BLOBOutputStream(m_blob);
}

} // namespace io

} // namespace stream


#endif // !defined(AFX_BLOBData_H__8817C75A_CEE8_4B33_8AF7_8AFDC842FE6B__INCLUDED_)
