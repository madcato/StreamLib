// XB64ZLibObj.h : Declaration of the CXB64ZLibObj

#ifndef __XB64ZLIBOBJ_H_
#define __XB64ZLIBOBJ_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CXB64ZLibObj
class ATL_NO_VTABLE CXB64ZLibObj : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CXB64ZLibObj, &CLSID_XB64ZLibObj>,
	public ISupportErrorInfo,
	public IDispatchImpl<IXB64ZLibObj, &IID_IXB64ZLibObj, &LIBID_XB64ZLIBLib>
{
public:
	CXB64ZLibObj()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_XB64ZLIBOBJ)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CXB64ZLibObj)
	COM_INTERFACE_ENTRY(IXB64ZLibObj)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IXB64ZLibObj
public:
	STDMETHOD(Uncompress)(/*[in]*/BSTR fileIn,/*[in]*/BSTR fileOut,/*[out,retval]*/long* result);
};

#endif //__XB64ZLIBOBJ_H_
