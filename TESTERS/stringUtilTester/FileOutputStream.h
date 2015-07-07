// FileOutputStream.h: interface for the CFileOutputStream class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEOUTPUTSTREAM_H__00417D14_00C0_11D5_ADFA_00105AF120EC__INCLUDED_)
#define AFX_FILEOUTPUTSTREAM_H__00417D14_00C0_11D5_ADFA_00105AF120EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


namespace Stream
{
class CFileOutputStream : public IOutputStream  
{
public:
	CFileOutputStream(const char* filename);
	virtual ~CFileOutputStream();

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

private:
	FILE* m_file;

};
}

#endif // !defined(AFX_FILEOUTPUTSTREAM_H__00417D14_00C0_11D5_ADFA_00105AF120EC__INCLUDED_)
