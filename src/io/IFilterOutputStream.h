// IFilterOutputStream.h: interface for the IFilterOutputStream class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IFILTEROUTPUTSTREAM_H__5993E3A2_B2B4_4716_A7DE_6E77ABD76DC3__INCLUDED_)
#define AFX_IFILTEROUTPUTSTREAM_H__5993E3A2_B2B4_4716_A7DE_6E77ABD76DC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace stream
{

class IFilterOutputStream : public io::IOutputStream  
{
public:
	IFilterOutputStream(io::IOutputStream* output);
	virtual ~IFilterOutputStream();

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

protected:
	io::IOutputStream* m_output;

};
} // namespace stream
#endif // !defined(AFX_IFILTEROUTPUTSTREAM_H__5993E3A2_B2B4_4716_A7DE_6E77ABD76DC3__INCLUDED_)
