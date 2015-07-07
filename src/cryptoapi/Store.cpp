// Store.cpp: implementation of the Store class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Certificate.h"
#include "Store.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/// namespace stream
namespace stream
{

/// namespace cryptoapi
namespace cryptoapi
{

Store::Store(const std::string& storeName, HCRYPTPROV provider)
{
	m_hCertStore = CertOpenSystemStore(provider,storeName.c_str());
	m_prevCert = 0;
}

Store::~Store()
{
	CertCloseStore(m_hCertStore,0);
}

#if(_WIN32_WINNT >= 0x0500)
std::auto_ptr<Certificate> Store::findCertificate(CERT_ID* ci)
{
	PCCERT_CONTEXT cert = CertFindCertificateInStore(m_hCertStore,
							X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
							0,
							CERT_FIND_CERT_ID,
							ci,
							NULL);

	std::auto_ptr<Certificate> certificate = new Certificate(cert);

	return certificate;
}


std::auto_ptr<Certificate> Store::findCertificate(CERT_INFO* ci)
{
	PCCERT_CONTEXT cert = CertFindCertificateInStore(m_hCertStore,
							X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
							0,
							CERT_FIND_SUBJECT_CERT,
							ci,
							NULL);

	std::auto_ptr<Certificate> certificate = new Certificate(cert);

	return certificate;
}

#endif // (_WIN32_WINNT >= 0x0500)

std::auto_ptr<Certificate> Store::getNextCertificate()
{
	PCCERT_CONTEXT cert = CertFindCertificateInStore(m_hCertStore,
							X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
							0,
							CERT_FIND_ANY,
							0,
							m_prevCert);

	m_prevCert = cert;

	if(!cert)
	{
		return std::auto_ptr<Certificate>(0);
	}
	return std::auto_ptr<Certificate>(new Certificate(cert));
}

std::vector<std::auto_ptr<Certificate> > Store::getCertificatesIssuedBy(const std::string& issuer)
{
	std::vector<std::auto_ptr<Certificate> > vector;


	return vector;
}

std::auto_ptr<Certificate> Store::getIssuerOf(Certificate* cert)
{
	PCCERT_CONTEXT c = CertFindCertificateInStore(m_hCertStore,
							X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
							0,
							CERT_FIND_SUBJECT_NAME,
							&(cert->getContext()->pCertInfo->Issuer),
							0);

	if(!c)
	{
		return std::auto_ptr<Certificate>(0);
	}
	return std::auto_ptr<Certificate>(new Certificate(c));
}


} /// namespace cryptoapi

} /// namespace stream
