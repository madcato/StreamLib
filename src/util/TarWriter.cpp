// TarWriter.cpp: implementation of the TarWriter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Exceptions.h"
#include "IOutputStream.h"
#include "IInputStream.h"
#include "CriticalSection.h"
#include "memory_stream.h"
#include "Tokenizer.h"
#include "Date.h"
#include "stringUtil.h"
#include "TarHeader.h"
#include "TarHeaderFactory.h"


#include "TarWriter.h"

#include "Blob.h"
#include "FileUtil.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace stream
{

/// namespace util
namespace util
{
using namespace io;
TarWriter::TarWriter(IOutputStream* output)
{
	m_output = output;

	m_buffer = auto_array_ptr<unsigned char>(bufferSize,new unsigned char[bufferSize]);
	m_zeroesBuffer = auto_array_ptr<unsigned char>(blockSize,new unsigned char[bufferSize]);
	memset(m_zeroesBuffer.get(),0,blockSize);
}

TarWriter::~TarWriter()
{

}

void TarWriter::close()
{
	


	m_output->write(m_zeroesBuffer.get(),blockSize);
	m_output->write(m_zeroesBuffer.get(),blockSize);
	
	m_output->close();
}

void TarWriter::write(std::auto_ptr<IInputStream> data,const std::string& path)
{

	TarHeader tarHeader;

	unsigned long dataLength = data->available();

	std::string finalPath = path;
#ifdef WIN32
	FileUtil::replaceBackSlash(finalPath);
#endif // WIN32

	if(path.length() >= sizeof(tarHeader.name))
	{
		// Se crea un registro LongLink
		writeLongLink(path);
	}


	TarHeaderFactory::CreateFileTarHeader(tarHeader,finalPath,dataLength);


	m_output->write((unsigned char*)&tarHeader,sizeof(TarHeader));
	
	unsigned long numberOfZeros = blockSize - (sizeof(TarHeader) % blockSize);

	

	
	m_output->write(m_zeroesBuffer.get(),numberOfZeros);
	
	while(data->available() != 0)
	{
		long readed = data->read(m_buffer.get(),bufferSize);
		m_output->write(m_buffer.get(),readed);
	}
	
	numberOfZeros = blockSize - (dataLength % blockSize);

	if(numberOfZeros < blockSize)
	{
		
		m_output->write(m_zeroesBuffer.get(),numberOfZeros);
	}


	data->close();
}


void TarWriter::writeDirectory(const std::string& path)
{
	TarHeader tarHeader;

	std::string finalPath = path;
#ifdef WIN32
	FileUtil::replaceBackSlash(finalPath);
#endif // WIN32

	if(path.length() >= sizeof(tarHeader.name))
	{
		// Se crea un registro LongLink
		writeLongLink(path);
	}


	TarHeaderFactory::CreateDirectoryTarHeader(tarHeader,finalPath);


	m_output->write((unsigned char*)&tarHeader,sizeof(TarHeader));
	
	unsigned long numberOfZeros = blockSize - (sizeof(TarHeader) % blockSize);

	

	
	m_output->write(m_zeroesBuffer.get(),numberOfZeros);

}

void TarWriter::writeLongLink(const std::string& path)
{
	TarHeader tarHeader;

	TarHeaderFactory::CreateLongLinkTarHeader(tarHeader,path.length());

	m_output->write((unsigned char*)&tarHeader,sizeof(TarHeader));

	unsigned long numberOfZeros = blockSize - (sizeof(TarHeader) % blockSize);

	

	
	m_output->write(m_zeroesBuffer.get(),numberOfZeros);

	// Escribimos el path completo del fichero
	m_output->write((unsigned char*)path.c_str(),path.length()+1);

	numberOfZeros = blockSize - ((path.length()+1) % blockSize);

	if(numberOfZeros < blockSize)
	{		
		m_output->write(m_zeroesBuffer.get(),numberOfZeros);
	}
}

} // namespace util

} // namespace stream