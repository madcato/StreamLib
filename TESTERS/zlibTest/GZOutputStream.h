// GZOutputStream.h: interface for the GZOutputStream class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GZOUTPUTSTREAM_H__41FA816D_48C3_4686_9CD0_754CFE8F6362__INCLUDED_)
#define AFX_GZOUTPUTSTREAM_H__41FA816D_48C3_4686_9CD0_754CFE8F6362__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace Stream
{

class GZOutputStream : public IOutputStream
{
public:
	GZOutputStream(const std::string& fileName);
	virtual ~GZOutputStream();

	///Closes this output stream and releases any system resources associated with this stream. 
	virtual void close();
	///Flushes this output stream and forces any buffered output bytes to be written out. 
	virtual void flush();
	///Writes b.length bytes from the specified byte array to this output stream. 
	virtual void write(unsigned char* b,long length);
	///Writes len bytes from the specified byte array starting at offset off to this output stream. 
	virtual void write(unsigned char* b, int off, int len);
	///Writes the specified byte to this output stream. 
	virtual void write(int b);

private:
	gzFile m_file;
};
} // namespace Stream
#endif // !defined(AFX_GZOUTPUTSTREAM_H__41FA816D_48C3_4686_9CD0_754CFE8F6362__INCLUDED_)
