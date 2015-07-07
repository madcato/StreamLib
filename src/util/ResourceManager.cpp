// ResourceManager.cpp: implementation of the ResourceManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Exceptions.h"
#include "CriticalSection.h"
#include "memory_stream.h"
#include "Blob.h"

#include "ResourceManager.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace stream
{

/// namespace util
namespace util
{

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

io::Blob<unsigned char> ResourceManager::loadBinary(int idResource)
{
	HRSRC hrsrc = FindResource(NULL,MAKEINTRESOURCE(idResource),RT_RCDATA);

	if(!hrsrc)
	{
		throw new exceptions::Win32ErrorException(__FILE__,__LINE__);
	}

	HGLOBAL hglobal = LoadResource(NULL,hrsrc); // No es necesario liberar este recurso.

	if(!hglobal)
	{
		throw new exceptions::Win32ErrorException(__FILE__,__LINE__);
	}

	
	
	unsigned long size = SizeofResource(NULL,hrsrc);

	if(!size)
	{
		throw new exceptions::Win32ErrorException(__FILE__,__LINE__);
	}

	io::Blob<unsigned char> blob;

	blob.attach((unsigned char*)LockResource(hglobal),size);

	return blob;

}

} // namespace util

} // namespace stream