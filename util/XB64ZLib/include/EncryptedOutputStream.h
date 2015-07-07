// EncryptedOutputStream.h: interface for the EncryptedOutputStream class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENCRYPTEDOUTPUTSTREAM_H__E87EC0C6_81B3_4849_808F_1965D857D98D__INCLUDED_)
#define AFX_ENCRYPTEDOUTPUTSTREAM_H__E87EC0C6_81B3_4849_808F_1965D857D98D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


namespace stream
{

class CEncryptedOutputStream : public io::IOutputStream  
{
public:
	CEncryptedOutputStream(std::string& passphrase,io::IOutputStream* output);
	virtual ~CEncryptedOutputStream();

	//Writes b.length bytes from the specified byte array to this output stream. 
	virtual void write(unsigned char* b,long length);
	//Writes len bytes from the specified byte array starting at offset off to this output stream. 
	virtual void write(unsigned char* b, int off, int len);
	//Writes the specified byte to this output stream. 
	virtual void write(int b);

private:
	HCRYPTPROV m_phProv;
	HCRYPTKEY m_phKey;

	io::IOutputStream* m_output;

};


} // namespace stream
#endif // !defined(AFX_ENCRYPTEDOUTPUTSTREAM_H__E87EC0C6_81B3_4849_808F_1965D857D98D__INCLUDED_)
