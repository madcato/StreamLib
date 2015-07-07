// HTMLIncluder.h: interface for the HTMLIncluder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTMLINCLUDER_H__9BE7087D_63C5_4F7C_81CB_E4AEC0DED472__INCLUDED_)
#define AFX_HTMLINCLUDER_H__9BE7087D_63C5_4F7C_81CB_E4AEC0DED472__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{
		/// namespace exceptions
	namespace exceptions
	{
	class HMTLException : public StreamException
	{
	public:
		HMTLException(long result, const std::string& message):StreamException(result,message){}
		virtual ~HMTLException()
		{
			
		}
	};
	} // namespace exceptions


/// namespace exceptions
namespace net
{

/**
	This class provides a method to insert htmlt files into another htmlt file.
*/
class HTMLIncluder  
{
public:HTMLIncluder();
public:virtual ~HTMLIncluder();

/**
	This method searhs for the string '#include ""', then it loads the file using <b>pathBase</b>
	as the base path to load the file and inserts this file into the position que the '#include was found.
*/
public:static std::string makeIncludes(const std::string& pageData,const std::string& pathBase);

};

} // namespace net

} // namespace stream

#endif // !defined(AFX_HTMLINCLUDER_H__9BE7087D_63C5_4F7C_81CB_E4AEC0DED472__INCLUDED_)
