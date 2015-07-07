// XB64ZLibObj.cpp : Implementation of CXB64ZLibObj
#include "stdafx.h"
#include "XB64ZLib.h"
#include "XB64ZLibObj.h"

/////////////////////////////////////////////////////////////////////////////
// CXB64ZLibObj

STDMETHODIMP CXB64ZLibObj::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IXB64ZLibObj
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CXB64ZLibObj::Uncompress(BSTR fileIn, BSTR fileOut, long *result)
{
	if(!result)
		return S_FAIL;

	USES_CONVERSION;

	*result = 0:

	try
	{
		Blob<char> blob = FileUtil::File2Buffer(OLE2A(fileIn));

		Base64Code b64;

		b64.DecodeMessage(((string)blob).c_str());

		GZIP gz(OPEN_FOR_UNCOMPRESS);

		Blob<char> decompressed;

		decompressed = gz.Update(b64.m_pDBuffer,b64.m_nDDataLen);

		decompressed.attach(gz.Finish());

		FileUtil::Buffer2File(OLE2A(fileOut),decompressed);
		


	}catch(exceptions::StreamException* e)
	{
		*result = -1;

		return Error(e->what());
	}

	return S_OK;
}
