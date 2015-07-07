// StreamRedirector.cpp: implementation of the StreamRedirector class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "IInputStream.h"
#include "IOutputStream.h"
#include "Exceptions.h"
#include "Thread.h"
#include "IStreamRedirector.h"

#include "StreamRedirector.h"

#include "CriticalSection.h"
#include "memory_stream.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace stream
{
namespace io
{
using namespace util;

StreamRedirector::StreamRedirector(IInputStream* istream, IOutputStream* ostream,unsigned int tam):IStreamRedirector(istream,ostream,tam),m_lastEx(0)
{
}

StreamRedirector::~StreamRedirector()
{
}

exceptions::StreamException* StreamRedirector::GetLastException()
{
	return m_lastEx;
}

void StreamRedirector::run()
{
	auto_array_ptr<unsigned char> buffer(m_redirLen);

	try
	{
		
		int readed;
		do
		{
			readed = m_istream->read(buffer.get(),m_redirLen);
			if(readed == 0)
				break;

			m_ostream->write(buffer.get(),readed);
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

}