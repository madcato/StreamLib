// GZIPOutputStream.h: interface for the GZIPOutputStream class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GZIPOUTPUTSTREAM_H__523B18B7_E639_41E9_8B37_8FD6BBC57F04__INCLUDED_)
#define AFX_GZIPOUTPUTSTREAM_H__523B18B7_E639_41E9_8B37_8FD6BBC57F04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{
/// namespace zip
namespace zip
{

class GZIPOutputStream : public io::IOutputStream 
{
public:
	GZIPOutputStream(EProcessTypeZip processType,io::IOutputStream* output);
	virtual ~GZIPOutputStream();

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

	std::auto_ptr<io::FilterOutputStream> m_filter;
};

} // namespace zip

} // namespace stream

#endif // !defined(AFX_GZIPOUTPUTSTREAM_H__523B18B7_E639_41E9_8B37_8FD6BBC57F04__INCLUDED_)
