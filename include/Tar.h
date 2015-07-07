// Tar.h: interface for the Tar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TAR_H__50B495E2_9921_4DB6_A06C_3FD2230221AF__INCLUDED_)
#define AFX_TAR_H__50B495E2_9921_4DB6_A06C_3FD2230221AF__INCLUDED_

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
Simple class to create tar from directories and make directories from tars.
*/
class Tar  
{
public:
	Tar();
	virtual ~Tar();
	
	/**
		Extract tar.
		@param inputTarFile Tar file.
		@param outputDir Output directory where the files will be extracted.
	*/
	void RunExtract(const std::string& inputTarFile,const std::string& outputDir);

	/**
		Extract tar.
		@param fin Input data .
		@param outputDir Output directory where the files will be extracted.
	*/
	void RunExtract(io::IInputStream* fin,const std::string& outputDir);

	/**
		Create tar.
		@param outputTarFile Tar file.
		@param fileWilcard Input directory.
	*/
	void RunAdd(const std::string& outputTarFile,const std::string& filesWildcard);

	/**
		Create tar.
		@param output Output stream.
		@param fileWilcard Input directory.
	*/
	void RunAdd(io::IOutputStream* output,const std::string& searchBase);

private:
	void RunAdd2(TarWriter& tar,const std::string& filesWildcard,const std::string& baseDir);
};

} // namespace util

} // namespace stream

#endif // !defined(AFX_TAR_H__50B495E2_9921_4DB6_A06C_3FD2230221AF__INCLUDED_)
