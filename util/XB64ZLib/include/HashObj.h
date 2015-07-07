// HashObj.h: interface for the HashObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HASHOBJ_H__B684C4F8_0D95_43DB_AE06_6BFC82CF8420__INCLUDED_)
#define AFX_HASHOBJ_H__B684C4F8_0D95_43DB_AE06_6BFC82CF8420__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{
/// namespace util
namespace util
{

/**
	Types of hash algorithms.
*/
enum HASH_TYPE
{
	/// MD5 algorithm
	MD5,
	/// SHA1 algorithm
	SHA1
};


/**
	This class calculates hashes of data buffers.
	Supported algorithms:
		Hash: MD5, SHA1. 
*/
class HashObj : public io::IDataProcessor
{
public:
	
	HashObj(HASH_TYPE a);
	

	virtual ~HashObj();


	virtual io::Blob<unsigned char> Update(unsigned char* buffer,unsigned long size);
	virtual io::Blob<unsigned char> Finish();
	virtual size_t available();
	
private:
	HASH_TYPE m_type;
	
	HCRYPTHASH phHash;
	
	char m_nombreCont[100];

	std::auto_ptr<cryptoapi::CryptContext> m_context;
};

} // namespace util

} // End namespace stream
#endif // !defined(AFX_HASHOBJ_H__B684C4F8_0D95_43DB_AE06_6BFC82CF8420__INCLUDED_)
