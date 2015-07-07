// FileUtil.cpp: implementation of the FileUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Exceptions.h"
#include "memory_stream.h"
#include "Blob.h"

#include "FileUtil.h"

#include "IInputStream.h"
#include "IOutputStream.h"
#include "FileInputStream.h"
#include "FileOutputStream.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace Stream
{
FileUtil::FileUtil()
{

}

FileUtil::~FileUtil()
{

}

long FileUtil::PutFinalSlashInPath(std::string& path)
{
	size_t pos = path.find_last_of('\\');

	if(path == "")
		return -1;
	
	

	if((pos == std::string::npos)||(pos != path.length() - 1))
	{
		// no existe \ o no está al final, la pongo al final
		path += "\\";
	}	

	return 0;	
}
bool FileUtil::FileExists(const std::string& path)
{
	if(_access( path.c_str(), 0) == 0)
	{
		return true;
	}

	return false;

}

long FileUtil::FileSize(const std::string& path)
{
	FILE* f = fopen(path.c_str(),"");

	if(f == 0)
		return -1;

	fseek(f,0,SEEK_END);
	unsigned long size = ftell(f);
	fseek(f,0,SEEK_SET);
	fclose(f);

	return size;
}


bool FileUtil::RecursiveRemoveDirectory(const std::string p)
{
	bool ret;
	
	WIN32_FIND_DATA info;
    HANDLE hp;
    char *cp;

	std::string path = p;
	
	ret = false;

	if(path[path.length()-1] == '\\')
	{
		path.erase(path.length()-1,1);
	}

	std::string name1;
	name1 = path + "\\*";

	
    hp = FindFirstFile(name1.c_str(),&info);
    if(!hp || hp==INVALID_HANDLE_VALUE)
	{		
        return(ret);
	}
    do
    {
		cp = info.cFileName;
        if(cp[1]==0 && *cp=='.')
            continue;
        else if(cp[2]==0 && *cp=='.' && cp[1]=='.')
            continue;
        
		name1 = path + "\\" + info.cFileName;
		if(info.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		{
			RecursiveRemoveDirectory(std::string(name1));
		}
		else
		{
			DeleteFile(name1.c_str());
		}

    }
    while(FindNextFile(hp,&info));
	FindClose(hp);
	if(RemoveDirectory(path.c_str()))
	{
		ret = true;
	}	
	return(ret);
}

long FileUtil::CreateDirectory(const std::string& path,bool failOnExistence)
{
	if(!::CreateDirectory(path.c_str(),0))
	{
		DWORD err = GetLastError();
		if((err != ERROR_ALREADY_EXISTS) || (failOnExistence))
			return -1;
	}

	return 0;
}

long FileUtil::DeleteOldFiles(const std::string& path, long miliseconds_old, enum FILE_TIME_TYPE ftt)
{
	std::string path_with_final_slash = path;
	PutFinalSlashInPath(path_with_final_slash);
	
	

		
		
	WIN32_FIND_DATA FileData;
	HANDLE h = FindFirstFile(path_with_final_slash.c_str(), &FileData);
	if(h == INVALID_HANDLE_VALUE)
		return -1;
	
	SYSTEMTIME SystemTime;
	GetSystemTime(&SystemTime);

	FILETIME Today;
	SystemTimeToFileTime(&SystemTime,&Today);

	_ULARGE_INTEGER a1,a2;
	memcpy(&a1,&Today,sizeof(_ULARGE_INTEGER));

	a2.QuadPart = miliseconds_old * 10000;
	a1.QuadPart  = a1.QuadPart  - a2.QuadPart ;
	
	
	do 
	{
		if(FileData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)
		{
			switch(ftt)
			{
			case CREATION_TIME:				
				memcpy(&a2,&FileData.ftCreationTime,sizeof(_ULARGE_INTEGER));
				break;
			case LAST_ACCESS_TIME:				
				memcpy(&a2,&FileData.ftLastAccessTime,sizeof(_ULARGE_INTEGER));
				break;
			case LAST_WRITE_TIME:				
				memcpy(&a2,&FileData.ftLastWriteTime,sizeof(_ULARGE_INTEGER));
				break;
			}			

			if(a2.QuadPart < a1.QuadPart)
			{
				// Borro el fichero
				DeleteFile((path_with_final_slash + FileData.cFileName).c_str());
			}
					
		}

	}while(FindNextFile(h,&FileData));
	FindClose(h);
	return 0;
}


long FileUtil::GetDatedFileName(std::string& path, const std::string& extension)
{
	struct tm *newtime;
	time_t aclock;
	time( &aclock );                 /* Obtener el tiempo en segundos */

	newtime = localtime( &aclock );  /* Convertir el tiempo a struct tm */
	char buffer[MAX_PATH];
	std::string ext = extension;
	if(ext != "")
	{
		ext = "." + ext;
	}
	
	
	int count = _snprintf(buffer,MAX_PATH,"%s\\%4.4u%2.2u%2.2u%2.2u%2.2u%2.2u%s",path.c_str()
			,newtime->tm_year + 1900,newtime->tm_mon + 1,newtime->tm_mday
			,newtime->tm_hour,newtime->tm_min,newtime->tm_sec,ext.c_str());

	if(count < 0)
		return -1;

	path = buffer;

	return 0;
}

long FileUtil::GetDirectorySize(const std::string& directory)
{
	std::string path = directory;
	PutFinalSlashInPath(path);
	
	std::string path2 = path;

	path += "*";

	long size = 0;
	WIN32_FIND_DATA FileData;
	HANDLE h = FindFirstFile(path.c_str(), &FileData);
	if(FileData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)
	{		
		struct _stat Stat;
		_stat((path2 + FileData.cFileName).c_str(),&Stat);
		size += Stat.st_size;
		
	}
	while(FindNextFile(h,&FileData))
	{
		if(FileData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)
		{
			struct _stat Stat;
			_stat((path2 + FileData.cFileName).c_str(),&Stat);
			size += Stat.st_size;
		}

	}
	FindClose(h);

	return size;
}

std::string FileUtil::ExtractFileNameFromPath(std::string path)
{
	std::string::size_type pos = path.rfind('\\');

	if(pos == std::string::npos)
	{
		pos = path.find('/');
	}
	

	if(pos != std::string::npos)
	{
		return path.substr(pos+1);
	}
	
	return path;
}

std::string FileUtil::RemoveFileNameFromPath(std::string path)
{
	std::string::size_type pos = path.rfind('\\');

	if(pos == std::string::npos)
	{
		pos = path.find('/');
	}
	

	if(pos != std::string::npos)
	{
		return path.substr(0,pos);
	}
	
	return path;

}

std::string FileUtil::ReplaceSpecialFolderChars(const std::string& str,char newChar)
{
	std::string newStr = str;

	for(int index = 0 ; index < str.length() ; index++)
	{
		switch(str[index])
		{
		case '\\':
		case '/':
		case '*':
		case ':':
		case '"':
		case '<':
		case '>':
		case '|':
			newStr[index] = newChar;
			break;
		default:
			break;
		}
	}

	return newStr;
}

Blob<char> FileUtil::File2Buffer(const std::string& filePath)
{
	CFileInputStream fileIn(filePath.c_str());

	long fileLength = fileIn.available();

	Blob<char> blob;

	blob.setData(auto_array_ptr<char>(new char[fileLength]),fileLength);

	fileIn.read((unsigned char*)blob.get(),fileLength);

	fileIn.close();

	return blob;
}

void FileUtil::Buffer2File(const Blob<char>& blob,const std::string& filePath)
{
	CFileOutputStream fileOut(filePath.c_str());

	fileOut.write((unsigned char*)blob.get(),blob.size());

	fileOut.close();
}

std::string FileUtil::GetTempPath()
{
	std::string result;
	char path[_MAX_PATH];

	if(::GetTempPath(_MAX_PATH,path) == 0)
	{
		throw Exceptions::Win32ErrorException(__FILE__,__LINE__);
	}
	else
	{
		result = path;
	}

	return result;
}


std::string FileUtil::GetFileVersion(const std::string& path)
{

	DWORD dwHandle = 0;
	DWORD versionInfoSize = 0;
	if((versionInfoSize = GetFileVersionInfoSize(const_cast<char*>(path.c_str()),&dwHandle)) != 0)
	{
		char* versionInfo = new char[versionInfoSize];
		if(!GetFileVersionInfo(const_cast<char*>(path.c_str()),0,versionInfoSize,versionInfo))
			throw Exceptions::Win32ErrorException(__FILE__,__LINE__);

		VS_FIXEDFILEINFO vs_fileInfo;

		long* data;
		long length;
		if(!VerQueryValue(versionInfo,"\\",(void**)&data,(unsigned int*)&length))
			throw Exceptions::Win32ErrorException(__FILE__,__LINE__);


		int a = 0;
		memcpy(&vs_fileInfo,data,length > sizeof(VS_FIXEDFILEINFO) ? sizeof(VS_FIXEDFILEINFO) : length);

		char version[1000];
		_snprintf(version,1000,"%d.%d.%d.%d",vs_fileInfo.dwFileVersionMS >> 16,
											vs_fileInfo.dwFileVersionMS & 0xFFFF,
											vs_fileInfo.dwFileVersionLS >> 16,
											vs_fileInfo.dwFileVersionLS & 0xFFFF);

		return version;
	}

	throw Exceptions::Win32ErrorException(__FILE__,__LINE__);
	return "";
}



} //namespace Stream