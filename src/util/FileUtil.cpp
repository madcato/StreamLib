// FileUtil.cpp: implementation of the FileUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Exceptions.h"
#include "CriticalSection.h"
#include "memory_stream.h"
#include "Blob.h"

#include "FileUtil.h"

#include "IInputStream.h"
#include "IOutputStream.h"
#include "FileInputStream.h"
#include "FileOutputStream.h"
#include "Tokenizer.h"
#include "Date.h"
#include "stringUtil.h"
#include "System.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace stream
{
using namespace io;
/// namespace util
namespace util
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
bool FileUtil::fileExists(const std::string& path)
{
	if(_access( path.c_str(), 0) == 0)
	{
		return true;
	}

	return false;

}

long FileUtil::FileSize(const std::string& path)
{
	FILE* f = fopen(path.c_str(),"rb");

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

long FileUtil::createDirectory(const std::string& path,bool failOnExistence)
{
	if(!::CreateDirectory(path.c_str(),0))
	{
		DWORD err = GetLastError();
		if((err == ERROR_ALREADY_EXISTS) && (failOnExistence))
			return -1;

		if(err != ERROR_ALREADY_EXISTS)
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


std::string FileUtil::getDatedFileName(const std::string& path, const std::string& extension)
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
	
	
	int count = _snprintf(buffer,MAX_PATH,"%s%4.4u%2.2u%2.2u%2.2u%2.2u%2.2u%s",path.c_str()
			,newtime->tm_year + 1900,newtime->tm_mon + 1,newtime->tm_mday
			,newtime->tm_hour,newtime->tm_min,newtime->tm_sec,ext.c_str());

	if(count < 0)
	{
		throw new exceptions::FileUtilException(-1,"Fail making 'getDatedFileName'");
	}

	return buffer;


}

std::string FileUtil::getDailyDatedFileName(const std::string& path, const std::string& extension)
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
	
	
	int count = _snprintf(buffer,MAX_PATH,"%s%4.4u%2.2u%2.2u%s",path.c_str()
			,newtime->tm_year + 1900,newtime->tm_mon + 1,newtime->tm_mday
			,ext.c_str());

	if(count < 0)
	{
		throw new exceptions::FileUtilException(-1,"Fail making 'getDailyDatedFileName'");
	}


	return buffer;
}

long FileUtil::getDirectorySize(const std::string& directory)
{
	std::string path = directory;
	PutFinalSlashInPath(path);
	
	std::string path2 = path;

	path += "*";

	long size = 0;
	WIN32_FIND_DATA FileData;
	HANDLE h = FindFirstFile(path.c_str(), &FileData);

	do
	{
		if(FileData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)
		{
			struct _stat Stat;
			_stat((path2 + FileData.cFileName).c_str(),&Stat);
			size += Stat.st_size;
		}

		if(FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if((strcmp(FileData.cFileName,".") != 0)&&(strcmp(FileData.cFileName,"..") != 0))
			size += getDirectorySize(path2 + FileData.cFileName);
		}
		
	}while(FindNextFile(h,&FileData));
	
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

bool FileUtil::isSpecialFolderChar(char newChar)
{

	switch(newChar)
	{
	case '\\':
	case '/':
	case '*':
	case ':':
	case '"':
	case '<':
	case '>':
	case '|':
		return true;
		break;
	}

	return false;
}

bool FileUtil::isValidFileName(std::string& name)
{
	for(int i = 0 ; i < name.length() ; i++)
	{
		if(isSpecialFolderChar(name[i]))
			return false;
	}

	return true;
}

io::Blob<char> FileUtil::File2Buffer(const std::string& filePath)
{
	FileInputStream fileIn(filePath.c_str());

	long fileLength = fileIn.available();

	io::Blob<char> blob;

	blob.setData(auto_array_ptr<char>(fileLength,new char[fileLength]),fileLength);

	fileIn.read((unsigned char*)blob.get(),fileLength);

	fileIn.close();

	return blob;
}

void FileUtil::Buffer2File(const io::Blob<char>& blob,const std::string& filePath)
{
	FileOutputStream fileOut(filePath.c_str());

	fileOut.write((unsigned char*)blob.get(),blob.length());

	fileOut.close();
}

void FileUtil::replaceSlash(std::string& path)
{
	int length = path.length();
	for(int i = 0 ; i < length ; i++)
	{
		if(path[i] == '/')
			path[i] = '\\';
	}
}

void FileUtil::replaceBackSlash(std::string& path)
{
	int length = path.length();
	for(int i = 0 ; i < length ; i++)
	{
		if(path[i] == '\\')
			path[i] = '/';
	}
}

std::string FileUtil::binToHex(const io::Blob<unsigned char>& blob)
{
	std::string ret = "";
	char cad[5];
	for(int i = 0 ; i < blob.length(); i++)
	{
		sprintf(cad,"%02x",blob[i]);
		ret += cad;
	}

	return ret;
}

io::Blob<unsigned char> FileUtil::hexToBin(const std::string& hex)
{
	

	io::Blob<unsigned char> ret;

	ret.resize(hex.length());

	unsigned char data = 0;
	for(int i = 0 ; i < hex.length(); i+=2)
	{
		sscanf(hex.c_str() + i,"%02x",&data);
		ret[i/2] = data;		
	}

	ret.setLength(hex.length()/2);

	return ret;
}

void FileUtil::deleteFile(const std::string& filename)
{
	if(!::DeleteFile(filename.c_str()))
	{
		throw new exceptions::Win32ErrorException(__FILE__,__LINE__);
	}
}

std::string FileUtil::pathToUri(const std::string& path)
{
	sstring result = path;
	replaceBackSlash(result);

	//result = result.replace(":","");
	
	result = "file:///" + result;
	
	return result;
}

std::string FileUtil::getTempFileName()
{
	std::string tempPath = System::getTempPath();
	
	char path[MAX_PATH + 1];
	GetTempFileName(tempPath.c_str(),"STM",0,path);

	return path;
}

std::vector<std::string> FileUtil::listFiles(const std::string& filesWildcard)
{
	std::vector<std::string> vec;

	long size = 0;
	WIN32_FIND_DATA FileData;
	HANDLE h = FindFirstFile(filesWildcard.c_str(), &FileData);

	do
	{
		if(FileData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)
		{
			vec.push_back(FileData.cFileName);		
		}
	}while(FindNextFile(h,&FileData));
	
	FindClose(h);

	return vec;
}

std::vector<std::string> FileUtil::listDirs(const std::string& dirsWildcard)
{
	std::vector<std::string> vec;

	long size = 0;
	WIN32_FIND_DATA FileData;
	HANDLE h = FindFirstFile(dirsWildcard.c_str(), &FileData);

	do
	{
		if(FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if((strcmp(FileData.cFileName,".") != 0)&&(strcmp(FileData.cFileName,"..") != 0))
				vec.push_back(FileData.cFileName);
		}
		
	}while(FindNextFile(h,&FileData));
	
	FindClose(h);

	return vec;
}


} // namespace util

} //namespace stream