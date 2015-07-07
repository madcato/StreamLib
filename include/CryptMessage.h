// CryptMessage.h: interface for the CryptMessage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRYPTMESSAGE_H__26F71A35_68CA_46CD_A3D3_8A931AB02EE2__INCLUDED_)
#define AFX_CRYPTMESSAGE_H__26F71A35_68CA_46CD_A3D3_8A931AB02EE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{

/// namespace cryptoapi
namespace cryptoapi
{

class CryptMessage  
{
public:
	CryptMessage();
	virtual ~CryptMessage();

	static std::string getMessageType(unsigned char* content, unsigned long contentLength, bool innerSignedContent);
	static io::Blob<unsigned char> createDataPKCS7(unsigned char* data, DWORD dataLength);
	static io::Blob<unsigned char> extractBareContent(unsigned char* data, DWORD dataLength);
	static io::Blob<unsigned char> extractDataContent(unsigned char* data, DWORD dataLength);
};

} /// namespace cryptoapi

} /// namespace stream

#endif // !defined(AFX_CRYPTMESSAGE_H__26F71A35_68CA_46CD_A3D3_8A931AB02EE2__INCLUDED_)
