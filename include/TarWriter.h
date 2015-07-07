// TarWriter.h: interface for the TarWriter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TARWRITER_H__E553BD25_2F79_4D16_8124_25C485542EAA__INCLUDED_)
#define AFX_TARWRITER_H__E553BD25_2F79_4D16_8124_25C485542EAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{

/// namespace util
namespace util
{

const unsigned long bufferSize = 4194304;

class TarWriter  
{
public:
	/**
		Constructor.
		Writes the output tar data to IOutputStream object.
		@param output Object for output.
		@param basePath Base directory of the files. When a file or directory is add to the tar, the basePath is removed if exists.
	*/
	TarWriter(io::IOutputStream* output);
	virtual ~TarWriter();
	
	/**
		Close the tar output stream.
	*/
	void close();

	/**
		Insert a file in the tar.
	*/
	void write(std::auto_ptr<io::IInputStream> data,const std::string& path);
	/**
		Insert a directory in the tar.
	*/
	void writeDirectory(const std::string& path);

private:
	io::IOutputStream* m_output;

	void writeLongLink(const std::string& path);

	util::auto_array_ptr<unsigned char> m_buffer;
	util::auto_array_ptr<unsigned char> m_zeroesBuffer;
};

} // namespace util

} // namespace stream

#endif // !defined(AFX_TARWRITER_H__E553BD25_2F79_4D16_8124_25C485542EAA__INCLUDED_)
