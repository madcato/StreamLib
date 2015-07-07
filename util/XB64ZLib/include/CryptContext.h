// CryptContext.h: interface for the CryptContext class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRYPTCONTEXT_H__C8081548_F8D9_4A84_8289_A4A9A5217B01__INCLUDED_)
#define AFX_CRYPTCONTEXT_H__C8081548_F8D9_4A84_8289_A4A9A5217B01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{

/// namespace cryptoapi
namespace cryptoapi
{

class CryptContext  
{
public:
	CryptContext(bool useEnhancedCsp = false);
	CryptContext(const std::string& csp,const std::string& container, unsigned long type,
		unsigned long flags,bool useEnhancedCsp = false,bool deleteContainerOnExit = false,bool createNewContainer = false, bool needPrivateKey = true);

	virtual ~CryptContext();

	HCRYPTPROV get() const;
	
private:
	HCRYPTPROV m_hKeyProv;

	bool checkEnhancedInstalled();

	bool m_deleteContainer;
};

} /// namespace cryptoapi

} /// namespace stream


#endif // !defined(AFX_CRYPTCONTEXT_H__C8081548_F8D9_4A84_8289_A4A9A5217B01__INCLUDED_)
