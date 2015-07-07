// FileInputStream.h: interface for the FileInputStream class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEINPUTSTREAM_H__00417D13_00C0_11D5_ADFA_00105AF120EC__INCLUDED_)
#define AFX_FILEINPUTSTREAM_H__00417D13_00C0_11D5_ADFA_00105AF120EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{

/**
	Group of exception classes used by the stream classes
*/
namespace exceptions
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

} // namespace exceptions

/// namespace io
namespace io
{

/**
	Input stream for files
*/
class FileInputStream : public IInputStream  
{
public:
	FileInputStream(const char* filename,long ini_position = 0, long end_position = -1)throw(exceptions::FileStreamException*);
	FileInputStream(const std::string& filename,long ini_position = 0, long end_position = -1)throw(exceptions::FileStreamException*);

	virtual ~FileInputStream();

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
	HANDLE m_file;

	void init(const std::string& filename);

	ulong m_available;

};

/**
	FileInputStream automatic pointer.
*/
typedef std::auto_ptr<FileInputStream> FileInputStreamPtr;
} // namespace io

}
#endif // !defined(AFX_FILEINPUTSTREAM_H__00417D13_00C0_11D5_ADFA_00105AF120EC__INCLUDED_)
