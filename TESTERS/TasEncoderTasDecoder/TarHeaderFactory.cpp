// TarHeaderFactory.cpp: implementation of the TarHeaderFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "TarHeader.h"
#include "TarHeaderFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace Stream
{

TarHeaderFactory::TarHeaderFactory()
{

}

TarHeaderFactory::~TarHeaderFactory()
{

}

void TarHeaderFactory::CreateFileTarHeader(TarHeader& tarHeader, const std::string& path, unsigned long fileSize)
{
	CreateDefaultTarHeader(tarHeader);

	strncpy(tarHeader.name,path.c_str(),sizeof(tarHeader.name));

	char buffer[100];
	_snprintf(buffer,100,"%011o",fileSize);
	memcpy(tarHeader.size,buffer,12);


	tarHeader.typeflag = '0';
	

	_snprintf(buffer,100,"%06o ",CalculateCheckSum(tarHeader));
	memcpy(tarHeader.cksum,buffer,8);

}

void TarHeaderFactory::CreateTarHeaderFromBuffer(unsigned char* buffer, TarHeader& tarHeader)
{
	memcpy(&tarHeader,buffer,sizeof(TarHeader));
}

void TarHeaderFactory::CreateDirectoryTarHeader(TarHeader& tarHeader, const std::string& path)
{
	CreateDefaultTarHeader(tarHeader);

	strncpy(tarHeader.name,path.c_str(),sizeof(tarHeader.name));


	char buffer[100];
	_snprintf(buffer,100,"0000000000000000");
	memcpy(tarHeader.size,buffer,12);


	tarHeader.typeflag = '5';
	

	_snprintf(buffer,100,"%06o",CalculateCheckSum(tarHeader));
	memcpy(tarHeader.cksum,buffer,8);

}

void TarHeaderFactory::CreateLongLinkTarHeader(TarHeader& tarHeader, unsigned long pathSize)
{
	CreateDefaultTarHeader(tarHeader);

	strcpy(tarHeader.name,"././@LongLink");

	char buffer[100];
	_snprintf(buffer,100,"%011o",pathSize + 1);
	memcpy(tarHeader.size,buffer,12);


	tarHeader.typeflag = 'L';
	

	_snprintf(buffer,100,"%06o ",CalculateCheckSum(tarHeader));
	memcpy(tarHeader.cksum,buffer,8);

}

void TarHeaderFactory::replaceSlash(std::string& path)
{
	int length = path.length();
	for(int i = 0 ; i < length ; i++)
	{
		if(path[i] == '/')
			path[i] = '\\';
	}
}

void TarHeaderFactory::replaceBackSlash(std::string& path)
{
	int length = path.length();
	for(int i = 0 ; i < length ; i++)
	{
		if(path[i] == '\\')
			path[i] = '/';
	}
}

int TarHeaderFactory::CalculateCheckSum(TarHeader& tarHeader)
{
	unsigned char buffer[blockSize];

	memset(buffer,0,blockSize);
	memcpy(&buffer,&tarHeader,sizeof(TarHeader));
	
	unsigned int sum = 0;
	
	for(int i = 0;i < blockSize;i++)
	{
		sum += (unsigned char)buffer[i];
	}
	
	for(i = 0;i < sizeof(tarHeader.cksum);i++)
	{
		sum -= tarHeader.cksum[i]; 
		sum += ' ';
	}
	return sum;
}

void TarHeaderFactory::CreateDefaultTarHeader(TarHeader& tarHeader)
{
	memset(&tarHeader,0,sizeof(TarHeader));

	memcpy(tarHeader.mode,"0034567",8);
	memcpy(tarHeader.uid,"0000067",8);
	memcpy(tarHeader.gid,"0000067",8);
	memcpy(tarHeader.mtime,"00000000000",12);
	memset(tarHeader.linkname,0,100);
	memcpy(tarHeader.magic,"ustar\000",6);
	memcpy(tarHeader.version," ",1);
	memcpy(tarHeader.uname,"user",5);
	memcpy(tarHeader.gname,"group",6);
	//memcpy(tarHeader.devmajor,"2 ",2);
	//memcpy(tarHeader.devminor,"1 ",2);
	//memset(tarHeader.prefix,0,155);
}

} // namespace Stream