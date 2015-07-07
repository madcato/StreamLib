// ResourceManager.h: interface for the ResourceManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESOURCEMANAGER_H__FE0B2B3F_DA8F_43FC_996B_8D55FE29A58A__INCLUDED_)
#define AFX_RESOURCEMANAGER_H__FE0B2B3F_DA8F_43FC_996B_8D55FE29A58A__INCLUDED_

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
	This class provides methods to access the resources included in the current project: like version info, bitmaps, strings, etc.
*/
class ResourceManager  
{
public:
	ResourceManager();
	virtual ~ResourceManager();

	/**
		Return a binary custom resource.
		@param idResource Identification of the resource.
		@return the binary data.
	*/
	static io::Blob<unsigned char> loadBinary(int idResource);

};

} // namespace util

} // namespace stream

#endif // !defined(AFX_RESOURCEMANAGER_H__FE0B2B3F_DA8F_43FC_996B_8D55FE29A58A__INCLUDED_)
