// StreamDoubleRedirector.h: interface for the StreamDoubleRedirector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STREAMDOUBLEREDIRECTOR_H__B9F07200_59AC_4F94_B0E9_49FD89DED275__INCLUDED_)
#define AFX_STREAMDOUBLEREDIRECTOR_H__B9F07200_59AC_4F94_B0E9_49FD89DED275__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace stream
{
namespace io
{
/**
	Double redirector of streams.
	All readed by the istream is write in ostream and the ostream2.
	Onces called method Start, an independent thread will redirect the data.
	This class is usefull to create 'sniffer' applications, to make a backup copy, etc...
*/
class StreamDoubleRedirector : public StreamRedirector
{
public:
	StreamDoubleRedirector(io::IInputStream* istream, io::IOutputStream* ostream,io::IOutputStream* ostream2,unsigned int tam = 1024);
	virtual ~StreamDoubleRedirector();

	void run();

protected:
	io::IOutputStream* m_ostream2;
};

} // namespace io

} // namespace stream
#endif // !defined(AFX_STREAMDOUBLEREDIRECTOR_H__B9F07200_59AC_4F94_B0E9_49FD89DED275__INCLUDED_)
