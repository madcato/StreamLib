// IInputStream.h: interface for the IInputStream class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IINPUTSTREAM_H__A1CD64F6_FE64_11D4_ADF9_00105AF120EC__INCLUDED_)
#define AFX_IINPUTSTREAM_H__A1CD64F6_FE64_11D4_ADF9_00105AF120EC__INCLUDED_

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
	Input stream interface.
*/
class IInputStream  
{
public:
	IInputStream(){}
	virtual ~IInputStream(){}

	///Returns the number of bytes that can be read (or skipped over) from this input stream without blocking by the next caller of a method for this input stream. 
	virtual int available() = 0;
	///Closes this input stream and releases any system resources associated with the stream. 
	virtual void close() = 0;
	///Marks the current position in this input stream. 
	virtual void mark(int readlimit) = 0;          
	///Tests if this input stream supports the mark and reset methods. 
	virtual bool markSupported() = 0;
	///Reads the next byte of data from the input stream. 
	virtual int read() = 0;
	///Reads some number of bytes from the input stream and stores them into the buffer array b. 
	virtual int read(unsigned char* b,long length) = 0;
	///Reads up to len bytes of data from the input stream into an array of bytes. 
	virtual int read(unsigned char* b, int off, int len) = 0;
	///Repositions this stream to the position at the time the mark method was last called on this input stream. 
	virtual void reset() = 0;
	///Skips over and discards n bytes of data from this input stream. 
	virtual long skip(long n) = 0;
};

/**
	IInputStream automatic pointer.
*/
typedef std::auto_ptr<IInputStream> IInputStreamPtr;

} // namespace io

}
#endif // !defined(AFX_IINPUTSTREAM_H__A1CD64F6_FE64_11D4_ADF9_00105AF120EC__INCLUDED_)
