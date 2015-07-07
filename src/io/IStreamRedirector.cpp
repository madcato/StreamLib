// IStreamRedirector.cpp: implementation of the IStreamRedirector class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "IInputStream.h"
#include "IOutputStream.h"
#include "IStreamRedirector.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace stream
{
///namespace io
namespace io
{
IStreamRedirector::IStreamRedirector(IInputStream* istream, IOutputStream* ostream,unsigned int tam)
{
	if(tam == 0)
		tam = -1;
	m_redirLen = tam;
	m_istream = istream;
	m_ostream = ostream;

}

IStreamRedirector::~IStreamRedirector()
{

}

} // namespace io


} // namespace stream