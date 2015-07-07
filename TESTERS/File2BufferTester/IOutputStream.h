// IOutputStream.h: interface for the IOutputStream class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IOUTPUTSTREAM_H__A1CD64F5_FE64_11D4_ADF9_00105AF120EC__INCLUDED_)
#define AFX_IOUTPUTSTREAM_H__A1CD64F5_FE64_11D4_ADF9_00105AF120EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace Stream
{

/**
	Output stream interface.
*/
class IOutputStream  
{
public:
	IOutputStream(){}
	virtual ~IOutputStream(){}

	///Closes this output stream and releases any system resources associated with this stream. 
	virtual void close() = 0;
	///Flushes this output stream and forces any buffered output bytes to be written out. 
	virtual void flush() = 0;
	///Writes b.length bytes from the specified byte array to this output stream. 
	virtual void write(unsigned char* b,long length) = 0;
	///Writes len bytes from the specified byte array starting at offset off to this output stream. 
	virtual void write(unsigned char* b, int off, int len) = 0;
	///Writes the specified byte to this output stream. 
	virtual void write(int b) = 0;
};
}
#endif // !defined(AFX_IOUTPUTSTREAM_H__A1CD64F5_FE64_11D4_ADF9_00105AF120EC__INCLUDED_)
