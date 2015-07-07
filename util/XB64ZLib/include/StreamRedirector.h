// StreamRedirector.h: interface for the StreamRedirector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STREAMREDIRECTOR_H__01157B91_6C64_48C8_86A3_2EA022D6B3DD__INCLUDED_)
#define AFX_STREAMREDIRECTOR_H__01157B91_6C64_48C8_86A3_2EA022D6B3DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/// namespace stream
namespace stream
{
/**
 namespace io.
 Provides for system input and output through data streams, serialization and the file system. 
*/
namespace io
{
/**
	Redirector of streams.
	All readed by the istream is write in ostream.
	Onces called method Start an independent thread will redirect the data.
*/
class StreamRedirector : public sync::Thread,public io::IStreamRedirector
{
public:
	StreamRedirector(io::IInputStream* istream, io::IOutputStream* ostream,unsigned int tam = 1024);
	virtual ~StreamRedirector();


	void run();
	exceptions::StreamException* GetLastException();

protected:
	
	exceptions::StreamException* m_lastEx;
};

} // namespace io

}
#endif // !defined(AFX_STREAMREDIRECTOR_H__01157B91_6C64_48C8_86A3_2EA022D6B3DD__INCLUDED_)
