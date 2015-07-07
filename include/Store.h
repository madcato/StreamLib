// Store.h: interface for the Store class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STORE_H__C5A1DFE1_C49E_43CC_9CB5_58BF9E8C8079__INCLUDED_)
#define AFX_STORE_H__C5A1DFE1_C49E_43CC_9CB5_58BF9E8C8079__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{

/// namespace cryptoapi
namespace cryptoapi
{


const std::string storeMy = "MY";
const std::string storeCA = "CA";
const std::string storeRoot = "ROOT";
const std::string storeSPC = "SPC";


class Store  
{
public:
	Store(const std::string& storeName, HCRYPTPROV provider = 0);
	virtual ~Store();

#if(_WIN32_WINNT >= 0x0500)
	std::auto_ptr<Certificate> findCertificate(CERT_ID* ci);

	std::auto_ptr<Certificate> findCertificate(CERT_INFO* ci);
#endif // (_WIN32_WINNT >= 0x0500)

	std::auto_ptr<Certificate> getNextCertificate();
	std::vector<std::auto_ptr<Certificate> > getCertificatesIssuedBy(const std::string& issuer);
	std::auto_ptr<Certificate> getIssuerOf(Certificate* cert);

private:
	HCERTSTORE m_hCertStore;

	PCCERT_CONTEXT m_prevCert;
};

} /// namespace cryptoapi

} /// namespace stream

#endif // !defined(AFX_STORE_H__C5A1DFE1_C49E_43CC_9CB5_58BF9E8C8079__INCLUDED_)
