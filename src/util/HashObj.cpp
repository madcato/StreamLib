// HashObj.cpp: implementation of the HashObj class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "IOutputStream.h"
#include "Exceptions.h"
#include "CriticalSection.h"
#include "memory_stream.h"
#include "Blob.h"
#include "IDataProcessor.h"
#include "CryptContext.h"

#include "HashObj.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace stream
{
namespace util
{
using namespace io;

HashObj::HashObj(HASH_TYPE a)
{
	m_type = a;

		GUID g;
	CoCreateGuid(&g);

	
	_snprintf(m_nombreCont,100,"%u-%u-%u-%u",g.Data1,g.Data2,g.Data3,g.Data4);


	m_context = std::auto_ptr<cryptoapi::CryptContext>(new cryptoapi::CryptContext(MS_DEF_PROV,m_nombreCont,PROV_RSA_FULL,CRYPT_NEWKEYSET,false,true));

	ALG_ID alg = 0;

	switch(m_type)
	{
	case MD5:
		alg = CALG_MD5;
		break;
	case SHA1:
		alg = CALG_SHA1;
		break;
	}

		
	if(CryptCreateHash(
			m_context->get(),
			alg,
			0,
			0,
			&phHash))
		{
		}
		else
		{
			throw new exceptions::Win32ErrorException(__FILE__,__LINE__);
		}
}

HashObj::~HashObj()
{


}


io::Blob<unsigned char> HashObj::Update(unsigned char* buffer,unsigned long size)
{
	if(CryptHashData(
					phHash,
					buffer,
					size,
					0
				))
		{
		}
		else
		{
			throw new exceptions::Win32ErrorException(__FILE__,__LINE__);
		}

	io::Blob<unsigned char> blob;
	return blob;

}

io::Blob<unsigned char> HashObj::Finish()
{
	io::Blob<unsigned char> blob;

	unsigned long pdwDataLen = 100;
	blob.resize(pdwDataLen);
	

	if(!CryptGetHashParam(
				  phHash,
				  HP_HASHVAL,
				  blob.get(),
				  &pdwDataLen,
				  0
				))
	{
		throw new exceptions::Win32ErrorException(__FILE__,__LINE__);
	}

	blob.setLength(pdwDataLen);
	return blob;

}

size_t HashObj::available()
{
	return 0;
}

} // namespace util

} // namespace stream