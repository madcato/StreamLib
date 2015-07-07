// EncryptedOutputStream.cpp: implementation of the EncryptedOutputStream class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "IOutputStream.h"
#include "Exceptions.h"
#include "EncryptedOutputStream.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace stream
{
using namespace io;
CEncryptedOutputStream::CEncryptedOutputStream(std::string& passphrase,IOutputStream* output)
{
	m_output = output;

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

CEncryptedOutputStream::~CEncryptedOutputStream()
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

//Writes b.length bytes from the specified byte array to this output stream. 
void CEncryptedOutputStream::write(unsigned char* b,long length)
{

	unsigned long inlen = length;
	if(CryptEncrypt(m_phKey,
			0,    
			TRUE,          
			0,       
			(unsigned char*)b,        
			(unsigned long*)&inlen,   
			inlen))
	{
	}
	else
	{
		throw new exceptions::Win32ErrorException(__FILE__,__LINE__);
	}

	m_output->write(b,length);


}
//Writes len bytes from the specified byte array starting at offset off to this output stream. 
void CEncryptedOutputStream::write(unsigned char* b, int off, int len)
{
	throw "Not implemented";
}
//Writes the specified byte to this output stream. 
void CEncryptedOutputStream::write(int b)
{

	unsigned long inlen = sizeof(char);
	if(CryptEncrypt(m_phKey,
			0,    
			TRUE,          
			0,       
			(unsigned char*)&b,        
			(unsigned long*)&inlen,   
			inlen))
	{
	}
	else
	{
		throw new exceptions::Win32ErrorException(__FILE__,__LINE__);
	}

	m_output->write(b);

}



} // namespace stream