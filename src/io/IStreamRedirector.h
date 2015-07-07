// IStreamRedirector.h: interface for the IStreamRedirector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ISTREAMREDIRECTOR_H__426A81BA_E65B_4FB3_8F9F_ABFFFEE0FC9C__INCLUDED_)
#define AFX_ISTREAMREDIRECTOR_H__426A81BA_E65B_4FB3_8F9F_ABFFFEE0FC9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
namespace stream
{
///namespace io
namespace io
{
/**
	Interface redirector of streams.
	All readed by the istream is write in ostream
*/
class IStreamRedirector  
{
public:
	IStreamRedirector(io::IInputStream* istream, io::IOutputStream* ostream,unsigned int tam = 1024);
	virtual ~IStreamRedirector();

protected:
	unsigned int m_redirLen;
	io::IInputStream* m_istream;
	io::IOutputStream* m_ostream;

};

} // namespace io

} // namespace stream
#endif // !defined(AFX_ISTREAMREDIRECTOR_H__426A81BA_E65B_4FB3_8F9F_ABFFFEE0FC9C__INCLUDED_)
