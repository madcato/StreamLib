// DCiphEncriptor.h: interface for the CDCiphEncriptor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DCIPHENCRIPTOR_H__C95E9798_7B17_4E71_BB6E_365E97329EF6__INCLUDED_)
#define AFX_DCIPHENCRIPTOR_H__C95E9798_7B17_4E71_BB6E_365E97329EF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace stream
{

class CDCiphEncriptor : public io::IOutputStream 
{
public:
	CDCiphEncriptor(io::IOutputStream* out,char* password,int plen);
	virtual ~CDCiphEncriptor();

	//Writes b.length bytes from the specified byte array to this output stream. 
	virtual void write(unsigned char* b,long length);
	//Writes len bytes from the specified byte array starting at offset off to this output stream. 
	virtual void write(unsigned char* b, int off, int len);
	//Writes the specified byte to this output stream. 
	virtual void write(int b);


private:
	io::IOutputStream* m_out;

	Dciph* cipher;
};
}
#endif // !defined(AFX_DCIPHENCRIPTOR_H__C95E9798_7B17_4E71_BB6E_365E97329EF6__INCLUDED_)
