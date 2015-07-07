// BufferedReader.h: interface for the BufferedReader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BUFFEREDREADER_H__EEAF796F_4613_4471_93B7_509A0540A3D0__INCLUDED_)
#define AFX_BUFFEREDREADER_H__EEAF796F_4613_4471_93B7_509A0540A3D0__INCLUDED_

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
This class is used like a reader of formated inputs with carriage returns.
*/
class BufferedReader : public IInputStream  
{
public:
	/**
		Constructor
		@param input IInputStream from where this class retrive the data.
	*/
	BufferedReader(IInputStream* input);
	virtual ~BufferedReader();
	///Returns the number of bytes that can be read (or skipped over) from this input stream without blocking by the next caller of a method for this input stream. 
	virtual int available();
	///Closes this input stream and releases any system resources associated with the stream. 
	virtual void close();
	///Marks the current position in this input stream. 
	virtual void mark(int readlimit);          
	///Tests if this input stream supports the mark and reset methods. 
	virtual bool markSupported();
	///Reads the next byte of data from the input stream. 
	virtual int read();
	///Reads some number of bytes from the input stream and stores them into the buffer array b. 
	virtual int read(unsigned char* b,long length);
	///Reads up to len bytes of data from the input stream into an array of bytes. 
	virtual int read(unsigned char* b, int off, int len);
	///Reads a line of text.
	virtual std::string readLine();
	///Repositions this stream to the position at the time the mark method was last called on this input stream. 
	virtual void reset();
	///Skips over and discards n bytes of data from this input stream. 
	virtual long skip(long n);

protected:
	IInputStream* m_input;

	uchar m_buffer[4096];
	long m_bufferIni;
	long m_bufferFin;
};

} // namespace io

} //namespace stream

#endif // !defined(AFX_BUFFEREDREADER_H__EEAF796F_4613_4471_93B7_509A0540A3D0__INCLUDED_)
