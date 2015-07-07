// SimpleHash.h: interface for the SimpleHash class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMPLEHASH_H__6CA6F913_B363_43D5_8964_32A84F80CC8E__INCLUDED_)
#define AFX_SIMPLEHASH_H__6CA6F913_B363_43D5_8964_32A84F80CC8E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace stream
{
namespace util
{

/**
	This class calculates hashes of data buffers.
	Uses CRC algorithm from 'zlib'.
*/

class SimpleHash : public io::IDataProcessor
{
public:
	SimpleHash();
	virtual ~SimpleHash();

	virtual io::Blob<unsigned char> Update(unsigned char* buffer,unsigned long size);
	virtual io::Blob<unsigned char> Finish();
	virtual size_t available();

private:
	ulong m_crc;

};

} // namespace util

} // namespace stream

#endif // !defined(AFX_SIMPLEHASH_H__6CA6F913_B363_43D5_8964_32A84F80CC8E__INCLUDED_)
