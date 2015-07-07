// B64InputStream.h: interface for the B64InputStream class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_B64INPUTSTREAM_H__BE80832C_5FC9_4B66_8ECE_ED536DB232F9__INCLUDED_)
#define AFX_B64INPUTSTREAM_H__BE80832C_5FC9_4B66_8ECE_ED536DB232F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{

/// namespace io
namespace io
{

class B64InputStream : public IInputStream
{
public:
	B64InputStream(EProcessType process, std::auto_ptr<IInputStream> input);
	virtual ~B64InputStream();

	///Returns the number of bytes that can be read (or skipped over) from this input stream without blocking by the next caller of a method for this input stream. 
	int available();
	///Closes this input stream and releases any system resources associated with the stream. 
	void close();
	///Marks the current position in this input stream. 
	void mark(int readlimit);          
	///Tests if this input stream supports the mark and reset methods. 
	bool markSupported();
	///Reads the next byte of data from the input stream. 
	int read();
	///Reads some number of bytes from the input stream and stores them into the buffer array b. 
	int read(unsigned char* b,long length);
	///Reads up to len bytes of data from the input stream into an array of bytes. 
	int read(unsigned char* b, int off, int len);
	///Repositions this stream to the position at the time the mark method was last called on this input stream. 
	void reset();
	///Skips over and discards n bytes of data from this input stream. 
	long skip(long n);


private:
	size_t calculateSize(size_t size);
	size_t calculateInverseSize(size_t size);

	EProcessType m_processType;
	std::auto_ptr<IInputStream> m_input;

	std::auto_ptr<B64> m_b64;
};

} // namespace io

} // namespace stream

#endif // !defined(AFX_B64INPUTSTREAM_H__BE80832C_5FC9_4B66_8ECE_ED536DB232F9__INCLUDED_)
