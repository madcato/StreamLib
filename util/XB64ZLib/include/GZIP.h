// GZIP.h: interface for the GZIP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GZIP_H__8101A9F4_674A_4354_9AC8_0E2FBDBEC3BA__INCLUDED_)
#define AFX_GZIP_H__8101A9F4_674A_4354_9AC8_0E2FBDBEC3BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{
/// namespace zip
namespace zip
{

/**
	Type of processing
*/
enum EProcessTypeZip
{
	OPEN_FOR_COMPRESS,
	OPEN_FOR_UNCOMPRESS
};

/**
	Compress/uncompress data using zlib library.
	This class is not compatible with .gz file format, use @see GZOutputStream ot GZInputStream instead.
*/
class GZIP : public io::IDataProcessor
{
public:
	GZIP(EProcessTypeZip type,size_t bufferLength = 4096);
	virtual ~GZIP();

	virtual io::Blob<unsigned char> Update(unsigned char* buffer,unsigned long size);
	virtual io::Blob<unsigned char> Finish();
	virtual size_t available();



private:
	std::auto_ptr<io::IDataProcessor> m_processor;
};

} // namespace zip

} // namespace stream

#endif // !defined(AFX_GZIP_H__8101A9F4_674A_4354_9AC8_0E2FBDBEC3BA__INCLUDED_)
