// TasHeaderFactory.cpp: implementation of the TasHeaderFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "TarHeader.h"
#include "TarHeaderFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TarHeaderFactory::TarHeaderFactory()
{

}

TarHeaderFactory::~TarHeaderFactory()
{

}


void TarHeaderFactory::CreateFileHeader(TarHeader& tarHeader,const std::string& fileName,unsigned long size)
{
	CreateDefaultHeader(tarHeader);


	char buffer[100];

	_snprintf(buffer,100,"%11o",size);
	memcpy(tarHeader.size,buffer,12);

	memcpy(tarHeader.typeflag,"0",1); // regular file
}

void TarHeaderFactory::CreateDirectoryHeader(TarHeader& tarHeader,const std::string& directoryName)
{
	CreateDefaultHeader(tarHeader);

	memset(tarHeader.size,'0',12);

	memcpy(tarHeader.typeflag,"5",1); // regular file
}

void TarHeaderFactory::CreateDefaultHeader(TarHeader& tarHeader)
{
	memset(&tarHeader,0,sizeof(TarHeader));

	memcpy(tarHeader.mode,"0100664",8);
	memcpy(tarHeader.uid,"0000664",8);
	memcpy(tarHeader.gid,"0000664",8);

	memcpy(tarHeader.mtime,"00000000000",12);


	memcpy(tarHeader.magic,"ustar ",6);
	memcpy(tarHeader.version,"1 ",2);

	memcpy(tarHeader.uname,"none",32);
	memcpy(tarHeader.gname,"none",32);

	memcpy(tarHeader.devmajor,"devmajor",8);
	memcpy(tarHeader.devminor,"devminor",8);

	memcpy(tarHeader.prefix,"/",1);

	
}

void TarHeaderFactory::SetChecksum(TarHeader& tarHeader)
{
	
	char sumatorio[100];
	ltoa(CalculateChecksum(tarHeader), sumatorio, 8);
	sprintf( tarHeader.cksum, "%06s", sumatorio );

}

unsigned long TarHeaderFactory::CalculateChecksum(TarHeader& tarHeader)
{
	unsigned char buffer[512];

	memset(buffer,0,512);
	memcpy(&buffer,&tarHeader,sizeof(TarHeader));
	
	unsigned long sum = 0;
	
	for(int i = 0 ; i < 512 ; i++)
	{
		sum += (unsigned char)buffer[i];
	}
	
	for(i = 0 ; i < sizeof(tarHeader.cksum) ; i++)
	{
		sum -= tarHeader.cksum[i]; 
		sum += ' ';
	}
	return sum;
}