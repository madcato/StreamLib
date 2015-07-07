// CommandProcessor.h: interface for the CCommandProcessor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMANDPROCESSOR_H__AC13D273_4AC2_428D_A6DD_F96A5B69B682__INCLUDED_)
#define AFX_COMMANDPROCESSOR_H__AC13D273_4AC2_428D_A6DD_F96A5B69B682__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace stream
{

	/// namespace util
namespace util
{

class CCommandProcessor  
{
public:
	CCommandProcessor();
	virtual ~CCommandProcessor();

	
	void close();


	io::IOutputStream* getOutputStream();
	io::IInputStream* getInputStream();





private:
	
	
	class Internal_InputStream : public io::IInputStream
	{
	public:
		Internal_InputStream(CCommandProcessor* parent);

		//Returns the number of bytes that can be read (or skipped over) from this input stream without blocking by the next caller of a method for this input stream. 
		virtual int available();
		//Closes this input stream and releases any system resources associated with the stream. 
		virtual void close();
		//Marks the current position in this input stream. 
		virtual void mark(int readlimit);          
		//Tests if this input stream supports the mark and reset methods. 
		virtual bool markSupported();
		//Reads the next byte of data from the input stream. 
		virtual int read()throw(exceptions::SocketStreamException*);
		//Reads some number of bytes from the input stream and stores them into the buffer array b. 
		virtual int read(unsigned char* b,long length)throw(exceptions::SocketStreamException*);
		//Reads up to len bytes of data from the input stream into an array of bytes. 
		virtual int read(unsigned char* b, int off, int len)throw(exceptions::SocketStreamException*);
		//Repositions this stream to the position at the time the mark method was last called on this input stream. 
		virtual void reset();
		//Skips over and discards n bytes of data from this input stream. 
		virtual long skip(long n)throw(exceptions::SocketStreamException*);

	private:
		CCommandProcessor* m_parent;
	};
	class Internal_OutputStream : public io::IOutputStream
	{
	public:
		Internal_OutputStream(CCommandProcessor* parent);

		//Closes this output stream and releases any system resources associated with this stream. 
		virtual void close();
		//Flushes this output stream and forces any buffered output bytes to be written out. 
		virtual void flush();
		//Writes b.length bytes from the specified byte array to this output stream. 
		virtual void write(unsigned char* b,long length)throw(exceptions::SocketStreamException*);
		//Writes len bytes from the specified byte array starting at offset off to this output stream. 
		virtual void write(unsigned char* b, int off, int len)throw(exceptions::SocketStreamException*);
		//Writes the specified byte to this output stream. 
		virtual void write(int b)throw(exceptions::SocketStreamException*);

	private:
		CCommandProcessor* m_parent;
	};


	Internal_InputStream* m_in;
	Internal_OutputStream* m_out;

	friend CCommandProcessor::Internal_InputStream;
	friend CCommandProcessor::Internal_OutputStream;
	
	FILE   *m_pipe;
};

} // namespace util

}

#endif // !defined(AFX_COMMANDPROCESSOR_H__AC13D273_4AC2_428D_A6DD_F96A5B69B682__INCLUDED_)
