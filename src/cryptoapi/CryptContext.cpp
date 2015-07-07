// CryptContext.cpp: implementation of the CryptContext class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CryptContext.h"

#include "Exceptions.h"
#include "CriticalSection.h"
#include "memory_stream.h"
#include "CryptException.h"

#include "AtlBase.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/// namespace stream
namespace stream
{

/// namespace cryptoapi
namespace cryptoapi
{

CryptContext::CryptContext(bool useEnhancedCsp)
{
	m_deleteContainer = false;
	
	std::string csp;
	unsigned long type = 0;
	
	if((useEnhancedCsp)&&(checkEnhancedInstalled()))
	{
		csp = MS_ENHANCED_PROV;
		type = PROV_RSA_FULL;
	}

	if(!CryptAcquireContext(
				&m_hKeyProv, 0, 
				0, 
				type,0)) 
	{
		throw new exceptions::CryptException(__FILE__,__LINE__);
	}
}
#ifndef MS_STRONG_PROV
#define MS_STRONG_PROV "Microsoft Strong Cryptographic Provider"
#endif // MS_STRONG_PROV

CryptContext::CryptContext(const std::string& csp,const std::string& container, unsigned long type,unsigned long flags,bool useEnhancedCsp,bool deleteContainerOnExit,bool createNewContainer, bool needPrivateKey)
{
	m_deleteContainer = deleteContainerOnExit;

	std::string internal_csp = csp;
	unsigned long internal_type = type;

	if((csp == MS_DEF_PROV)||(csp == MS_STRONG_PROV))
	{
		if((useEnhancedCsp)&&(checkEnhancedInstalled()))
		{
			internal_csp = MS_ENHANCED_PROV;
			internal_type = PROV_RSA_FULL;
		}
	}

	if(createNewContainer)
	{
		flags |= CRYPT_NEWKEYSET;
	}

	if(!needPrivateKey)
	{
		flags |= CRYPT_VERIFYCONTEXT;
	}
	if(!CryptAcquireContext(
				&m_hKeyProv, container.c_str(), 
				internal_csp.c_str(), 
				internal_type,flags)) 
	{
		throw new exceptions::CryptException(__FILE__,__LINE__);
	}
}

CryptContext::~CryptContext()
{
	unsigned long flag = 0;

	if(m_deleteContainer)
	{
		flag = CRYPT_DELETEKEYSET;
	}

	CryptReleaseContext(m_hKeyProv,flag);
}

HCRYPTPROV CryptContext::get() const
{
	return m_hKeyProv;
}

bool CryptContext::checkEnhancedInstalled()
{
	CRegKey reg;
	if(reg.Open(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Cryptography\\Defaults\\Provider\\Microsoft Enhanced Cryptographic Provider v1.0",KEY_READ) == ERROR_SUCCESS)
	{
		return true;	
	}

	return false;
	
}

} /// namespace cryptoapi

} /// namespace stream
