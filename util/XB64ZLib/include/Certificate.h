// Certificate.h: interface for the Certificate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CERTIFICATE_H__5FFD21D9_1ABB_4B6C_8DAC_EEE9B12CF48C__INCLUDED_)
#define AFX_CERTIFICATE_H__5FFD21D9_1ABB_4B6C_8DAC_EEE9B12CF48C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{

/// namespace cryptoapi
namespace cryptoapi
{


class Certificate  
{
public:
	Certificate(PCCERT_CONTEXT cert);
	
	virtual ~Certificate();

	std::string getCspName();
	std::string getKeyContainer();
	unsigned long getCspType();
	unsigned long getCspFlags();
	unsigned long getKeySpec();

	std::string getNotBefore();
	std::string getNotAfter();

	std::string getSubject();
	std::string getIssuer();

	PCCERT_CONTEXT getContext();

private:
	class CertificateProperties
	{
	public:
		std::string m_csp;
		std::string m_container;
		unsigned long m_cspType;
		unsigned long m_cspFlags;
		unsigned long m_keySpec;
	};

	PCCERT_CONTEXT m_cert;

	
	std::auto_ptr<CertificateProperties> m_certProperties; 

	bool loadProperties();

	std::string timeToStr(FILETIME* fTime);

	std::string nameToStr(PCERT_NAME_BLOB name);
};

} /// namespace cryptoapi

} /// namespace stream

#endif // !defined(AFX_CERTIFICATE_H__5FFD21D9_1ABB_4B6C_8DAC_EEE9B12CF48C__INCLUDED_)
