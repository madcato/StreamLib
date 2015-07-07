// PrintWriter.h: interface for the PrintWriter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRINTWRITER_H__947287FB_9F81_44BD_BCD1_96462227BBDE__INCLUDED_)
#define AFX_PRINTWRITER_H__947287FB_9F81_44BD_BCD1_96462227BBDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{
/// namespace io
namespace io
{

class PrintWriter : public IOutputStream
{
public:
	PrintWriter(IOutputStream* output, std::string endline = "\x00D\x00A");
	virtual ~PrintWriter();

	//Closes this output stream and releases any system resources associated with this stream. 
	virtual void close();
	//Flushes this output stream and forces any buffered output bytes to be written out. 
	virtual void flush();
	//Writes b.length bytes from the specified byte array to this output stream. 
	virtual void write(unsigned char* b,long length);
	//Writes len bytes from the specified byte array starting at offset off to this output stream. 
	virtual void write(unsigned char* b, int off, int len);
	//Writes the specified byte to this output stream. 
	virtual void write(int b);
	//Writes a line.
	virtual void println(std::string cad);

protected:
	unsigned char* m_endline;
	int m_enlinelen;
	IOutputStream* m_output;
};

} // namespace io

} // namespace stream

#endif // !defined(AFX_PRINTWRITER_H__947287FB_9F81_44BD_BCD1_96462227BBDE__INCLUDED_)
