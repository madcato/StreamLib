// TarWriter.h: interface for the TarWriter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TARWRITER_H__E553BD25_2F79_4D16_8124_25C485542EAA__INCLUDED_)
#define AFX_TARWRITER_H__E553BD25_2F79_4D16_8124_25C485542EAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace Stream
{

const unsigned long bufferSize = 65536;

class TarWriter  
{
public:
	
	TarWriter(std::auto_ptr<IOutputStream> output);	
	virtual ~TarWriter();
	
	void close();
	void write(std::auto_ptr<IInputStream> data,const std::string& path);
	void writeDirectory(const std::string& path);

private:
	std::auto_ptr<IOutputStream> m_output;

	void writeLongLink(const std::string& path);
};

} // namespace Stream

#endif // !defined(AFX_TARWRITER_H__E553BD25_2F79_4D16_8124_25C485542EAA__INCLUDED_)
