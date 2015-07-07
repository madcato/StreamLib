// EncriptedInputStream.cpp: implementation of the EncriptedInputStream class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"


#include "IInputStream.h"
#include "Exceptions.h"
#include "EncryptedInputStream.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace stream
{
using namespace io;
CEncryptedInputStream::CEncryptedInputStream(std::string& passphrase,IInputStream* input)
{

	m_input = input;

	CryptAcquireContext(&m_phProv,
		"CONTENEDOR_DE_PASO",
		MS_DEF_PROV,
		PROV_RSA_FULL ,
		CRYPT_DELETEKEYSET);
	if(CryptAcquireContext(&m_phProv,
		"CONTENEDOR_DE_PASO",
		MS_DEF_PROV,
		PROV_RSA_FULL ,
		/*CRYPT_DELETEKEYSET*/CRYPT_NEWKEYSET))
	{
		//printf("CryptAcquireContext OK");
	}
	else
	{
		throw new exceptions::Win32ErrorException(__FILE__,__LINE__);
	}


	HCRYPTHASH phHash;
	if(CryptCreateHash(m_phProv,
			CALG_MD5,        
			0,      
			0,       
			&phHash))
	{
	}
	else
	{
		throw new exceptions::Win32ErrorException(__FILE__,__LINE__);
	}

	
	if(CryptHashData(phHash,  
		(const unsigned char*)passphrase.c_str(),      
		passphrase.length(),
		0))
	{
	}
	else
	{
		throw new exceptions::Win32ErrorException(__FILE__,__LINE__);
	}



	if(CryptDeriveKey(m_phProv,      
			CALG_RC4,
			phHash,  
			0x00380000,
			&m_phKey))
	{
	}
	else
	{
		throw new exceptions::Win32ErrorException(__FILE__,__LINE__);
	}
	CryptDestroyHash(phHash);

	



}

CEncryptedInputStream::~CEncryptedInputStream()
{
	CryptReleaseContext(m_phProv,0);
	if(CryptAcquireContext(&m_phProv,
		"CONTENEDOR_DE_PASO",
		MS_DEF_PROV,
		PROV_RSA_FULL ,
		CRYPT_DELETEKEYSET))
	{
		//printf("CryptAcquireContext OK");
	}
	else
	{
		throw new exceptions::Win32ErrorException(__FILE__,__LINE__);
	}
}


//Returns the number of bytes that can be read (or skipped over) from this input stream without blocking by the next caller of a method for this input stream. 
int CEncryptedInputStream::available()
{
	return m_input->available();
}

//Marks the current position in this input stream. 
void CEncryptedInputStream::mark(int readlimit)
{
	m_input->mark(readlimit);
}
//Tests if this input stream supports the mark and reset methods. 
bool CEncryptedInputStream::markSupported()
{
	return 0;	
}

void CEncryptedInputStream::close()
{
	m_input->close();
}
//Reads the next byte of data from the input stream. 
int CEncryptedInputStream::read()
{

	int c = m_input->read();

	unsigned long inlen = sizeof(char);
	if(CryptDecrypt(m_phKey,
			0,    
			TRUE,          
			0,       
			(unsigned char*)&c,
			&inlen))
	{
	}
	else
	{
		throw new exceptions::Win32ErrorException(__FILE__,__LINE__);
	}

	


	return c;
}
//Reads some number of bytes from the input stream and stores them into the buffer array b. 
int CEncryptedInputStream::read(unsigned char* b,long length)
{
	unsigned long readed = m_input->read(b,length);

	
	if(CryptDecrypt(m_phKey,
			0,    
			TRUE,          
			0,       
			(unsigned char*)b,
			&readed))
	{
	}
	else
	{
		throw new exceptions::Win32ErrorException(__FILE__,__LINE__);
	}

	



	return readed;
}
//Reads up to len bytes of data from the input stream into an array of bytes. 
int CEncryptedInputStream::read(unsigned char* b, int off, int len)
{
	throw "not implemented";
	return 0;	
}
//Repositions this stream to the position at the time the mark method was last called on this input stream. 
void CEncryptedInputStream::reset()
{
	m_input->reset();	
}
//Skips over and discards n bytes of data from this input stream. 
long CEncryptedInputStream::skip(long n)
{

	return m_input->skip(n);	
}



} // namespace stream