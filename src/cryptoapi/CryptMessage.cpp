// CryptMessage.cpp: implementation of the CryptMessage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Exceptions.h"
#include "CriticalSection.h"
#include "memory_stream.h"
#include "Blob.h"
#include "CryptMessage.h"

#include "CryptException.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/// namespace stream
namespace stream
{

/// namespace cryptoapi
namespace cryptoapi
{

CryptMessage::CryptMessage()
{

}

CryptMessage::~CryptMessage()
{

}

std::string CryptMessage::getMessageType(unsigned char* content, unsigned long contentLength, bool innerSignedContent)
{
	char* szInnerType = 0;
	HCRYPTMSG hMsg;
	try
	{

		long innerType = 0;
		if(innerSignedContent)
		{
			innerType = CMSG_SIGNED;
		}

		
		if(!(hMsg = CryptMsgOpenToDecode(
			   MY_ENCODING_TYPE,      // Encoding type.
			   0,                     // Flags.
			   innerType,                     // Use the default message type.
									  // The message type is 
									  // listed in the message header.
			   NULL,                  // Cryptographic provider. Use NULL
									  // for the default provider.
			   NULL,                  // Recipient information.
			   NULL)))                    // Stream information (not used)
		{
			throw new exceptions::CryptException(__FILE__,__LINE__);
		}

		if(!CryptMsgUpdate(
			 hMsg,         // Handle to the message
			 content,    // Pointer to the content
			 contentLength,    // Size of the content
			 TRUE))        // Last call
		{
			// SI FALLA AQUÍ ES POR QUE NO ES ASN1.
			DWORD err = GetLastError();
			if(err == 2148086027) // No es ASN1
			{
				CryptMsgClose(hMsg);
				return "";
			}
			else
			{
				throw new exceptions::CryptException(__FILE__,__LINE__);
			}
		}


		unsigned long type = 0;
		unsigned long resultSize = sizeof(unsigned long);
		if(!CryptMsgGetParam(
			hMsg,                      // Handle to the message
			CMSG_TYPE_PARAM,        // Parameter type
			0,                         // Index
			&type,              // Pointer to the blob
			&resultSize))            // Size of the blob
		{
			throw new exceptions::CryptException(__FILE__,__LINE__);
		}

		switch(type)
		{
		case CMSG_DATA:
				szInnerType = szOID_RSA_data;
				break;
		case CMSG_SIGNED:
				szInnerType = szOID_RSA_signedData;
				break;
		case CMSG_ENVELOPED:
				szInnerType = szOID_RSA_envelopedData;
				break;
		case CMSG_HASHED:
				szInnerType = szOID_RSA_digestedData;
				break;
		case CMSG_ENCRYPTED:
				szInnerType = szOID_RSA_encryptedData;
				break;
		default:
				szInnerType = 0;
				break;
		}
	}catch(exceptions::StreamException*)
	{
		CryptMsgClose(hMsg);
		return "";
	}

	CryptMsgClose(hMsg);

	return szInnerType;
}


io::Blob<unsigned char> CryptMessage::createDataPKCS7(unsigned char* data, DWORD dataLength)
{
	io::Blob<unsigned char> pkcs7Data;
	DWORD cbDataBlob = 0;
	if(cbDataBlob = CryptMsgCalculateEncodedLength(
		MY_ENCODING_TYPE,       // Message encoding type
		0,//CMSG_CMS_ENCAPSULATED_CONTENT_FLAG,                      // Flags
		CMSG_DATA,            // Message type
		NULL,   // Pointer to structure
		NULL,                   // Inner content OID
		dataLength))             // Size of content
	{
		
	}
	else
	{
		throw new exceptions::CryptException(__FILE__,__LINE__);
	}
	//--------------------------------------------------------------------
	// Allocate memory for the encoded blob.
	pkcs7Data.resize(dataLength);
	//--------------------------------------------------------------------
	// Open a message to encode.
	HCRYPTMSG hMsg;
	if(hMsg = CryptMsgOpenToEncode(
		MY_ENCODING_TYPE,        // Encoding type
		0,//CMSG_CMS_ENCAPSULATED_CONTENT_FLAG,                       // Flags
		CMSG_DATA,             // Message type
		NULL,    // Pointer to structure
		NULL,                    // Inner content OID
		NULL))                   // Stream information (not used)
	{
		
	}
	else
	{
		throw new exceptions::CryptException(__FILE__,__LINE__);
	}
	//--------------------------------------------------------------------
	// Update the message with the data.

	if(CryptMsgUpdate(
		 hMsg,         // Handle to the message
		 data,    // Pointer to the content
		 dataLength,    // Size of the content
		 TRUE))        // Last call
	{
		
	}
	else
	{
		throw new exceptions::CryptException(__FILE__,__LINE__);
	}
	//--------------------------------------------------------------------
	// Get the resulting message.

	if(CryptMsgGetParam(
		hMsg,                      // Handle to the message
		CMSG_CONTENT_PARAM,        // Parameter type
		0,                         // Index
		pkcs7Data.get(),              // Pointer to the blob
		&cbDataBlob))            // Size of the blob
	{
		
	}
	else
	{
		throw new exceptions::CryptException(__FILE__,__LINE__);
	}

	pkcs7Data.setLength(cbDataBlob);

	CryptMsgClose(hMsg);
	
	return pkcs7Data;	
}


io::Blob<unsigned char> CryptMessage::extractBareContent(unsigned char* data, DWORD dataLength)
{
	DWORD sructLength = 0;

	CRYPT_CONTENT_INFO cci;
	
	if(!CryptDecodeObject(
		  MY_ENCODING_TYPE,
		  PKCS_CONTENT_INFO,
		  data,
		  dataLength,
		  0,
		  0,
		  &sructLength
		))
	{
		throw new exceptions::Win32ErrorException(__FILE__,__LINE__);
	}

	util::auto_array_ptr<unsigned char> buffer(sructLength,new unsigned char[sructLength]);

	if(!CryptDecodeObject(
		  MY_ENCODING_TYPE,
		  PKCS_CONTENT_INFO,
		  data,
		  dataLength,
		  0,
		  buffer.get(),
		  &sructLength
		))
	{
		throw new exceptions::Win32ErrorException(__FILE__,__LINE__);
	}

	memcpy(&cci,buffer.get(),sructLength > sizeof(cci)?sizeof(cci):sructLength);

	io::Blob<unsigned char> bareContent;

	bareContent.attach(cci.Content.pbData,cci.Content.cbData);

	return bareContent;
}

io::Blob<unsigned char> CryptMessage::extractDataContent(unsigned char* data, DWORD dataLength)
{
	HCRYPTMSG hMsg;
	if(!(hMsg = CryptMsgOpenToDecode(
		   MY_ENCODING_TYPE,      
		   0,
		   0,					  
		   0,									  
		   NULL,
		   NULL)))                
	{
		throw new exceptions::Win32ErrorException(__FILE__,__LINE__);
	}

	if(!CryptMsgUpdate(
		 hMsg,         // Handle to the message
		 data,    // Pointer to the content
		 dataLength,    // Size of the content
		 TRUE))        // Last call
	{
		throw new exceptions::Win32ErrorException(__FILE__,__LINE__);
	}

	io::Blob<unsigned char> content;
	unsigned long resultSize = 0;

	if(CryptMsgGetParam(
		hMsg,                      // Handle to the message
		CMSG_CONTENT_PARAM,        // Parameter type
		0,                         // Index
		0,              // Pointer to the blob
		&resultSize))            // Size of the blob
		{
		
			content.resize(resultSize);
			resultSize = content.capacity();
			if(!CryptMsgGetParam(
				hMsg,                      // Handle to the message
				CMSG_CONTENT_PARAM,        // Parameter type
				0,                         // Index
				content.get(),              // Pointer to the blob
				&resultSize))            // Size of the blob
			{
				throw new exceptions::Win32ErrorException(__FILE__,__LINE__);
			}			
	}
	else {
		throw new exceptions::Win32ErrorException(__FILE__,__LINE__);
	}			

	content.setLength(resultSize);

	CryptMsgClose(hMsg);

	return content;
}

} /// namespace cryptoapi

} /// namespace stream
