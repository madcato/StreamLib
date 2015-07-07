// TarWriter.cpp: implementation of the TarWriter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "IOutputStream.h"
#include "IInputStream.h"
#include "Exceptions.h"

#include "TarHeader.h"
#include "TarHeaderFactory.h"
#include "TarWriter.h"

#include "memory_stream.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace Stream
{

TarWriter::TarWriter(std::auto_ptr<IOutputStream> output)
{
	m_output = output;
}

TarWriter::~TarWriter()
{

}

void TarWriter::close()
{
	auto_array_ptr<unsigned char> buffer(new unsigned char[blockSize]);

	memset(buffer.get(),0,blockSize);
	m_output->write(buffer.get(),blockSize);
	m_output->write(buffer.get(),blockSize);
	
	m_output->close();
}

void TarWriter::write(std::auto_ptr<IInputStream> data,const std::string& path)
{
	TarHeader tarHeader;

	unsigned long dataLength = data->available();

	std::string finalPath = path;
#ifdef WIN32
	TarHeaderFactory::replaceBackSlash(finalPath);
#endif // WIN32

	if(path.length() >= sizeof(tarHeader.name))
	{
		// Se crea un registro LongLink
		writeLongLink(path);
	}


	TarHeaderFactory::CreateFileTarHeader(tarHeader,finalPath,dataLength);


	m_output->write((unsigned char*)&tarHeader,sizeof(TarHeader));
	
	unsigned long numberOfZeros = blockSize - (sizeof(TarHeader) % blockSize);

	auto_array_ptr<unsigned char> buffer(new unsigned char[bufferSize]);

	memset(buffer.get(),0,blockSize);
	m_output->write(buffer.get(),numberOfZeros);
	
	while(data->available() != 0)
	{
		long readed = data->read(buffer.get(),bufferSize);
		m_output->write(buffer.get(),readed);
	}
	
	numberOfZeros = blockSize - (dataLength % blockSize);

	if(numberOfZeros < blockSize)
	{
		memset(buffer.get(),0,blockSize);
		m_output->write(buffer.get(),numberOfZeros);
	}


	data->close();
}


void TarWriter::writeDirectory(const std::string& path)
{
	TarHeader tarHeader;

	std::string finalPath = path;
#ifdef WIN32
	TarHeaderFactory::replaceBackSlash(finalPath);
#endif // WIN32

	if(path.length() >= sizeof(tarHeader.name))
	{
		// Se crea un registro LongLink
		writeLongLink(path);
	}


	TarHeaderFactory::CreateDirectoryTarHeader(tarHeader,finalPath);


	m_output->write((unsigned char*)&tarHeader,sizeof(TarHeader));
	
	unsigned long numberOfZeros = blockSize - (sizeof(TarHeader) % blockSize);

	auto_array_ptr<unsigned char> buffer(new unsigned char[bufferSize]);

	memset(buffer.get(),0,blockSize);
	m_output->write(buffer.get(),numberOfZeros);

}

void TarWriter::writeLongLink(const std::string& path)
{
	TarHeader tarHeader;

	TarHeaderFactory::CreateLongLinkTarHeader(tarHeader,path.length());

	m_output->write((unsigned char*)&tarHeader,sizeof(TarHeader));

	unsigned long numberOfZeros = blockSize - (sizeof(TarHeader) % blockSize);

	auto_array_ptr<unsigned char> buffer(new unsigned char[bufferSize]);

	memset(buffer.get(),0,blockSize);
	m_output->write(buffer.get(),numberOfZeros);

	// Escribimos el path completo del fichero
	m_output->write((unsigned char*)path.c_str(),path.length()+1);

	numberOfZeros = blockSize - ((path.length()+1) % blockSize);

	if(numberOfZeros < blockSize)
	{
		memset(buffer.get(),0,blockSize);
		m_output->write(buffer.get(),numberOfZeros);
	}
}

} // namespace Stream