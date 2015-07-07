// onsoleOutputStream.h: interface for the ConsoleOutputStream class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ONSOLEOUTPUTSTREAM_H__F59E773B_1FBE_4DCD_96A8_1D837340712E__INCLUDED_)
#define AFX_ONSOLEOUTPUTSTREAM_H__F59E773B_1FBE_4DCD_96A8_1D837340712E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace stream
{

/// namespace io
namespace io
{

class ConsoleOutputStream : public IOutputStream 
{
public:
	ConsoleOutputStream();
	virtual ~ConsoleOutputStream();

	///Closes this output stream and releases any system resources associated with this stream. 
	void close();
	///Flushes this output stream and forces any buffered output bytes to be written out. 
	void flush();
	///Writes b.length bytes from the specified byte array to this output stream. 
	void write(unsigned char* b,long length);
	///Writes len bytes from the specified byte array starting at offset off to this output stream. 
	void write(unsigned char* b, int off, int len);
	///Writes the specified byte to this output stream. 
	void write(int b);

	/// Writes a line
	void println(const std::string& str);
	/// Writes a line
	void println(char* str);

};

} // namespace io

} // namespace stream
#endif // !defined(AFX_ONSOLEOUTPUTSTREAM_H__F59E773B_1FBE_4DCD_96A8_1D837340712E__INCLUDED_)
