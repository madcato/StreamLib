// StreamDoubleRedirector.cpp: implementation of the StreamDoubleRedirector class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Exceptions.h"
#include "Thread.h"
#include "IInputStream.h"
#include "IOutputStream.h"
#include "IStreamRedirector.h"
#include "StreamRedirector.h"

#include "StreamDoubleRedirector.h"

#include "CriticalSection.h"
#include "memory_stream.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace stream
{
namespace io
{
StreamDoubleRedirector::StreamDoubleRedirector(IInputStream* istream, IOutputStream* ostream,IOutputStream* ostream2,unsigned int tam):StreamRedirector(istream, ostream,tam)
{
	m_ostream2 = ostream2;
}

StreamDoubleRedirector::~StreamDoubleRedirector()
{

}


void StreamDoubleRedirector::run()
{
	util::auto_array_ptr<unsigned char> buffer(m_redirLen,new unsigned char[m_redirLen]);
	try
	{
		
		int readed;
		do
		{
			readed = m_istream->read(buffer.get(),m_redirLen);
			if(readed == 0)
				break;

			m_ostream->write(buffer.get(),readed);
			m_ostream2->write(buffer.get(),readed);
		}while(true);
	}
	catch(exceptions::StreamException* e)
	{
		m_lastEx = e;
	}
	catch(...)
	{
		m_lastEx = new exceptions::StreamException(-1,"Error grave");
	}
}

} // namespace io

} // namespace stream