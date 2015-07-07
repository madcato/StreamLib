// FileInputStream.h: interface for the CFileInputStream class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEINPUTSTREAM_H__00417D13_00C0_11D5_ADFA_00105AF120EC__INCLUDED_)
#define AFX_FILEINPUTSTREAM_H__00417D13_00C0_11D5_ADFA_00105AF120EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


namespace Stream
{

namespace Exceptions
{

	/**
	 File exception.
	*/
	class FileStreamException : public StreamException
	{
	public:
		FileStreamException(int id_code,std::string desc):StreamException(id_code,desc)
		{
		}
	};

} // namespace Exceptions


class CFileInputStream : public IInputStream  
{
public:
	CFileInputStream(const char* filename)throw(Exceptions::FileStreamException*);
	virtual ~CFileInputStream();

	//Returns the number of bytes that can be read (or skipped over) from this input stream without blocking by the next caller of a method for this input stream. 
	virtual int available();
	//Closes this input stream and releases any system resources associated with the stream. 
	virtual void close();
	//Marks the current position in this input stream. 
	virtual void mark(int readlimit);          
	//Tests if this input stream supports the mark and reset methods. 
	virtual bool markSupported();
	//Reads the next byte of data from the input stream. 
	virtual int read();
	//Reads some number of bytes from the input stream and stores them into the buffer array b. 
	virtual int read(unsigned char* b,long length);
	//Reads up to len bytes of data from the input stream into an array of bytes. 
	virtual int read(unsigned char* b, int off, int len);
	//Repositions this stream to the position at the time the mark method was last called on this input stream. 
	virtual void reset();
	//Skips over and discards n bytes of data from this input stream. 
	virtual long skip(long n);


private:
	FILE* m_file;


};
}
#endif // !defined(AFX_FILEINPUTSTREAM_H__00417D13_00C0_11D5_ADFA_00105AF120EC__INCLUDED_)
