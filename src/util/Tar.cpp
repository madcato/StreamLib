// Tar.cpp: implementation of the Tar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"


#include "Exceptions.h"
#include "IInputStream.h"
#include "IOutputStream.h"
#include "FileInputStream.h"
#include "FileOutputStream.h"
#include "CriticalSection.h"
#include "memory_stream.h"

#include "TarHeader.h"
#include "TarHeaderFactory.h"
#include "TarReader.h"
#include "TarWriter.h"

#include "Tar.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace stream
{

/// namespace util
namespace util
{
using namespace io;
Tar::Tar()
{

}

Tar::~Tar()
{

}

void Tar::RunExtract(const std::string& inputTarFile,const std::string& outputDir)
{

	std::auto_ptr<io::IInputStream> fin(new FileInputStream(inputTarFile.c_str()));
	RunExtract(fin.get(),outputDir);
}

void Tar::RunExtract(io::IInputStream* fin,const std::string& outputDir)
{
	TarReader tar(fin);

	unsigned char buffer[1001];

	std::auto_ptr<IInputStream> data;
	std::string path = "";
	std::string finalPath = "";
	bool directory;
	while(tar.getNextItem(path,directory,data))
	{
		finalPath = outputDir + "\\" + path;
		if(!directory)
		{
			FileOutputStream fout(finalPath.c_str());

			while(data->available())
			{
				int readed = data->read(buffer,1000);
				fout.write(buffer,readed);
			}
			data->close();
		}
		else
		{
			CreateDirectory(finalPath.c_str(),NULL);
		}

	}

	tar.close();
}


void Tar::RunAdd(const std::string& outputTarFile,const std::string& searchBase)
{
	std::auto_ptr<IOutputStream> fout = std::auto_ptr<IOutputStream>(new FileOutputStream(outputTarFile.c_str()));
	RunAdd(fout.get(),searchBase);
}

void Tar::RunAdd(io::IOutputStream* output,const std::string& searchBase)
{

	TarWriter tar(output);



	RunAdd2(tar,searchBase,std::string(""));

	
	tar.close();
}

void Tar::RunAdd2(TarWriter& tar,const std::string& searchBase,const std::string& baseDir)
{

	std::string wildcard = searchBase + "\\*";

	std::string finalPath = "";

	WIN32_FIND_DATA wfd;
	HANDLE searchHandle = ::FindFirstFile(wildcard.c_str(),&wfd);

	if(searchHandle == INVALID_HANDLE_VALUE)
	{
		throw new exceptions::Win32ErrorException(__FILE__,__LINE__);
	}
	do
	{
		finalPath = baseDir + wfd.cFileName;
		std::string filePath = searchBase + "\\" + wfd.cFileName;
		if(wfd.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)
		{
			FileInputStream* input = new FileInputStream(filePath.c_str());

			tar.write(std::auto_ptr<IInputStream>(input),finalPath);


		}
		if(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			std::string path = wfd.cFileName;
			if((path != ".")&&(path != ".."))
			{
				tar.writeDirectory(finalPath);
				finalPath += "\\";
				
				RunAdd2(tar,filePath,finalPath);
			}


		}

	}while(::FindNextFile(searchHandle,&wfd));

	::FindClose(searchHandle);
}

} // namespace util

} // namespace stream