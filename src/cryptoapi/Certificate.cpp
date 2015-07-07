// Certificate.cpp: implementation of the Certificate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Certificate.h"

#include "Exceptions.h"
#include "CriticalSection.h"
#include "memory_stream.h"
#include "CryptException.h"

#include "atlbase.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/// namespace stream
namespace stream
{

/// namespace cryptoapi
namespace cryptoapi
{

Certificate::Certificate(PCCERT_CONTEXT cert)
{
	m_cert = cert;
}

Certificate::~Certificate()
{

}

std::string Certificate::getCspName()
{
	if(!loadProperties())
	{
		return "";
	}

	return m_certProperties->m_csp;	
}

std::string Certificate::getKeyContainer()
{
	if(!loadProperties())
	{
		return "";
	}

	return m_certProperties->m_container;	
}

unsigned long Certificate::getCspType()
{
	if(!loadProperties())
	{
		return 0;
	}

	return m_certProperties->m_cspType;	
}

unsigned long Certificate::getCspFlags()
{
	if(!loadProperties())
	{
		return 0;
	}

	return m_certProperties->m_cspFlags;	
}

unsigned long Certificate::getKeySpec()
{
	if(!loadProperties())
	{
		return 0;
	}

	return m_certProperties->m_keySpec;	
}

std::string Certificate::getNotBefore()
{
	// NotBefore

	return timeToStr(&(m_cert->pCertInfo->NotBefore));
}

std::string Certificate::getNotAfter()
{
	// NotAfter
	return timeToStr(&(m_cert->pCertInfo->NotAfter));
}

std::string Certificate::getSubject()
{
	return nameToStr(&(m_cert->pCertInfo->Subject));
}

std::string Certificate::getIssuer()
{
	return nameToStr(&(m_cert->pCertInfo->Issuer));
}

PCCERT_CONTEXT Certificate::getContext()
{
	return m_cert;
}

bool Certificate::loadProperties()
{	
	if(m_certProperties.get() != 0)
	{
		// Already loaded
		return true;
	}
	else
	{
		m_certProperties = std::auto_ptr<CertificateProperties>(new CertificateProperties);
	}

	CRYPT_KEY_PROV_INFO  prov;
	DWORD len = 0;
	
	if(!CertGetCertificateContextProperty(m_cert,
			CERT_KEY_PROV_INFO_PROP_ID,
			0,
			&len))
	{
		throw new exceptions::CryptException(__FILE__,__LINE__);
		return false; 
	}

	util::auto_array_ptr<unsigned char> tempBuffer(len);

	if(!CertGetCertificateContextProperty(m_cert,          
			CERT_KEY_PROV_INFO_PROP_ID,                       
			tempBuffer.get(), 
			&len))
	{
		throw new exceptions::CryptException(__FILE__,__LINE__);
		return false;
	}


	memcpy(&prov,tempBuffer.get(),sizeof(prov) > len ? len:sizeof(prov));


	USES_CONVERSION;
	m_certProperties->m_csp = W2A(prov.pwszProvName);
	m_certProperties->m_container = W2A(prov.pwszContainerName);
	m_certProperties->m_cspType = prov.dwProvType;
	m_certProperties->m_cspFlags = prov.dwFlags;
	m_certProperties->m_keySpec = prov.dwKeySpec;

	/*
	// COMPROBAMOS SI EXISTE EL ENHANCED. SI ES ASÍ Y EL CSP ACTUAL ES EL BASE O EL STRONG, LO SUBSTITUIMOS POR EL ENHANCED.
	if((strcmp(csp,MS_DEF_PROV) == 0)||(strcmp(csp,MS_STRONG_PROV) == 0))
	{
		string message = string("Found MSCSP: ") + csp;
		trace(LOG_INFO,message);	
		CRegKey reg;
		if(reg.Open(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Cryptography\\Defaults\\Provider\\Microsoft Enhanced Cryptographic Provider v1.0",KEY_READ) == ERROR_SUCCESS)
		{
			trace(LOG_INFO,"ENHANCED CSP activated.");	
			strcpy(csp,MS_ENHANCED_PROV);
			*type = 1;
			reg.Close();
		}
	}
	*/
	
	return true;
}

std::string Certificate::timeToStr(FILETIME* fTime)
{
	SYSTEMTIME t;

	if(!FileTimeToSystemTime(fTime,&t))
	{
		throw new exceptions::CryptException(__FILE__,__LINE__);
	}



	util::auto_array_ptr<char> buffer;

	int length = 0;

	if(!(length = GetDateFormat(LOCALE_SYSTEM_DEFAULT,0,&t,0,0,length)))
	{
		throw new exceptions::Win32ErrorException(__FILE__,__LINE__);
	}

	buffer = util::auto_array_ptr<char>(length,new char[length]);


	if(!GetDateFormat(LOCALE_SYSTEM_DEFAULT,0,&t,0,buffer.get(),length))
	{
		throw new exceptions::Win32ErrorException(__FILE__,__LINE__);
	}


	return buffer.get();
}

std::string Certificate::nameToStr(PCERT_NAME_BLOB name)
{

	util::auto_array_ptr<char> buffer;

	int length = 0;

	if(!(length = CertNameToStr( X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
		name,
		CERT_X500_NAME_STR,
		0,
		0)))
	{
		throw new exceptions::CryptException(__FILE__,__LINE__);
	}

	buffer = util::auto_array_ptr<char>(length,new char[length]);

	if(!CertNameToStr( X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
		name,
		CERT_X500_NAME_STR,
		buffer.get(),
		length))
	{
		throw new exceptions::CryptException(__FILE__,__LINE__);
	}

	return buffer.get();
}

} /// namespace cryptoapi

} /// namespace stream
