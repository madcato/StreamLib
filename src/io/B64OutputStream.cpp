 // B64OutputStream.cpp: implementation of the B64OutputStream class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Exceptions.h"
#include "CriticalSection.h"
#include "memory_stream.h"
#include "Blob.h"
#include "IOutputStream.h"
#include "IDataProcessor.h"
#include "B64.h"

#include "B64OutputStream.h"

#include "BLOBOutputStream.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace stream
{

/// namespace io
namespace io
{

B64OutputStream::B64OutputStream(EProcessType process, std::auto_ptr<IOutputStream> output,int charsPerLine, const std::string& newLineChar):m_processType(process),m_output(output),m_charsPerLine(charsPerLine),m_newLineChar(newLineChar)
{
	m_b64 = std::auto_ptr<B64>(new B64(process));
	m_lastCharOfLine = 0;
}

B64OutputStream::~B64OutputStream()
{

}

///Closes this output stream and releases any system resources associated with this stream. 
void B64OutputStream::close()
{
	Blob<unsigned char> blob = m_b64->Finish();

	push(blob);

	m_output->close();
}
///Flushes this output stream and forces any buffered output bytes to be written out. 
void B64OutputStream::flush()
{
	m_output->flush();
}
///Writes b.length bytes from the specified byte array to this output stream. 
void B64OutputStream::write(unsigned char* b,long length)
{
	write(b,0,length);
}
///Writes len bytes from the specified byte array starting at offset off to this output stream. 
void B64OutputStream::write(unsigned char* b, int off, int len)
{

	Blob<unsigned char> blob = m_b64->Update(b+off,len);

	if(blob.length() > 0)
	{
		push(blob);
	}
		
}
///Writes the specified byte to this output stream. 
void B64OutputStream::write(int b)
{
	write((unsigned char*)&b,1);
}

void B64OutputStream::push(Blob<unsigned char>& blob)
{
	int length = blob.length();
	int index = 0;
	int toWrite = 0;
	
	while(length > 0)
	{
		
		toWrite = m_charsPerLine > length?length:m_charsPerLine;
		
		toWrite -= m_lastCharOfLine;
		
		if(toWrite <=0)
		{
			if(m_charsPerLine != -1)
			{
				toWrite = m_charsPerLine > length?length:m_charsPerLine;
			}
			else
			{
				toWrite = length;
			}
		}

		m_output->write(blob.get() + index,toWrite);
		
		m_lastCharOfLine += toWrite;
		if((m_lastCharOfLine == m_charsPerLine)&&(m_charsPerLine != -1))
			m_output->write((unsigned char*)m_newLineChar.c_str(),m_newLineChar.length());

		index += toWrite;
		length -= toWrite;

		

		if(m_lastCharOfLine >= m_charsPerLine)
		{
			m_lastCharOfLine -= m_charsPerLine;
		}
		
	}
}

std::auto_ptr<io::Blob<char> > B64OutputStream::encode(unsigned char* buffer,unsigned long length,int charsPerLine, const std::string& newLineChar)
{
	std::auto_ptr<io::Blob<char> > result(new io::Blob<char>());
	
	std::auto_ptr<IOutputStream> input(new BLOBOutputStream(result));
	B64OutputStream output(OPEN_FOR_ENCODING,input,charsPerLine,newLineChar);

	output.write(buffer,length);
	output.close();
	char b[1];
	b[0] = '\0';
	result->attach(b,1);

	return result;
}

std::auto_ptr<io::Blob<char> > B64OutputStream::decode(unsigned char* buffer,unsigned long length)
{
	std::auto_ptr<io::Blob<char> > result(new io::Blob<char>());
	
	std::auto_ptr<IOutputStream> input(new BLOBOutputStream(result));
	B64OutputStream output(OPEN_FOR_DECODING,input,-1);

	output.write(buffer,length);
	output.close();
	
	return result;
}

} // namespace io

} // namespace stream