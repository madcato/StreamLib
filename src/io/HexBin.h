// HexBin.h: interface for the HexBin class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HEXBIN_H__9CD77170_02E6_4C13_8021_6C2C23FF86EE__INCLUDED_)
#define AFX_HEXBIN_H__9CD77170_02E6_4C13_8021_6C2C23FF86EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace stream
{

/// namespace io
namespace io
{

/**
	Converts binary data in haxadecimal strings.
*/
class HexBin : public IDataProcessor
{
public:
	HexBin(EProcessType type, bool makeUpper = false);
	virtual ~HexBin();

	virtual io::Blob<unsigned char> Update(unsigned char* buffer,unsigned long size);
	virtual io::Blob<unsigned char> Finish() ;
	virtual size_t available() ;


private:
	EProcessType m_type;

	long lastChar;

	char* m_format;
};

} // io

} // namespace stream

#endif // !defined(AFX_HEXBIN_H__9CD77170_02E6_4C13_8021_6C2C23FF86EE__INCLUDED_)
