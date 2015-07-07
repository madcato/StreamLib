// FilterOutputStream.h: interface for the FilterOutputStream class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILTEROUTPUTSTREAM_H__523B18B7_E639_41E9_8B37_8FD6BBC57F04__INCLUDED_)
#define AFX_FILTEROUTPUTSTREAM_H__523B18B7_E639_41E9_8B37_8FD6BBC57F04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{
/// namespace io
namespace io
{

class FilterOutputStream : public io::IOutputStream 
{
public:
	FilterOutputStream(std::auto_ptr<IDataProcessor> processor,io::IOutputStream* ouptut);
	virtual ~FilterOutputStream();

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
	std::auto_ptr<IDataProcessor> m_processor;
	io::IOutputStream* m_output;
};

} // namespace io

} // namespace stream

#endif // !defined(AFX_FILTEROUTPUTSTREAM_H__523B18B7_E639_41E9_8B37_8FD6BBC57F04__INCLUDED_)
