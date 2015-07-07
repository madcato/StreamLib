// TarReader.h: interface for the TarReader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TARREADER_H__57AA75EC_27A5_4092_AF63_FED21E8E1D10__INCLUDED_)
#define AFX_TARREADER_H__57AA75EC_27A5_4092_AF63_FED21E8E1D10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{

/// namespace util
namespace util
{

class TarReader  
{
public:
	TarReader(io::IInputStream* input);
	virtual ~TarReader();

	void close();
	bool getNextItem(std::string& path,bool& directory,std::auto_ptr<io::IInputStream>& data);

private:
	io::IInputStream* m_input;
	

	class TarReaderStream : public io::IInputStream
	{
	public:
		TarReaderStream(unsigned long size,io::IInputStream* input);
		virtual ~TarReaderStream();

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
		unsigned long m_size;
		unsigned long m_readed;
		io::IInputStream* m_input;
	};
};

} // namespace util

} // namespace stream

#endif // !defined(AFX_TARREADER_H__57AA75EC_27A5_4092_AF63_FED21E8E1D10__INCLUDED_)
