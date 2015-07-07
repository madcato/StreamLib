// B64OutputStream.h: interface for the B64OutputStream class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_B64OutputStream_H__EF37D240_44C3_4979_BFDC_6E7F6179C909__INCLUDED_)
#define AFX_B64OutputStream_H__EF37D240_44C3_4979_BFDC_6E7F6179C909__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{

/// namespace io
namespace io
{

class B64OutputStream : public IOutputStream
{
public:
	B64OutputStream(EProcessType process, std::auto_ptr<IOutputStream> input,int charsPerLine = 64, const std::string& newLineChar = std::string("\r\n"));
	virtual ~B64OutputStream();

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

	/**
		Encodes a buffer. 
		@return The Base64 encoded data.
	*/
	static std::auto_ptr<io::Blob<char> > encode(unsigned char* buffer,unsigned long length,int charsPerLine = 64, const std::string& newLineChar = std::string("\r\n"));

	/**
		Decodes a buffer.
		@return The Base64 decoded data.
	*/
	static std::auto_ptr<io::Blob<char> > decode(unsigned char* buffer,unsigned long length);
private:
	std::auto_ptr<IOutputStream> m_output;
	EProcessType m_processType;
	int m_charsPerLine;
	std::string m_newLineChar;

	std::auto_ptr<B64> m_b64;

	int m_lastCharOfLine;

	void push(stream::io::Blob<unsigned char>& blob);
};

} // namespace io

} // namespace stream
#endif // !defined(AFX_B64OutputStream_H__EF37D240_44C3_4979_BFDC_6E7F6179C909__INCLUDED_)
