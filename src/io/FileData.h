// FileData.h: interface for the FileData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEDATA_H__8817C75A_CEE8_4B33_8AF7_8AFDC842FE6B__INCLUDED_)
#define AFX_FILEDATA_H__8817C75A_CEE8_4B33_8AF7_8AFDC842FE6B__INCLUDED_

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
This class represents a file data acces.
*/
class FileData : public IData  
{
public:
	FileData(const std::string& fileName,long ini_position = 0, long end_position = -1);
	virtual ~FileData();

	/**
		@return A FileInputStream object.
	*/
	virtual std::auto_ptr<IInputStream> getInputStream();

	/**
		@return A FileOutputStream object.
	*/
	virtual std::auto_ptr<IOutputStream> getOutputStream();

private:
	std::string m_fileName;

	long m_ini_position;
	long m_end_position;
};

} // namespace io

} // namespace stream


#endif // !defined(AFX_FILEDATA_H__8817C75A_CEE8_4B33_8AF7_8AFDC842FE6B__INCLUDED_)
