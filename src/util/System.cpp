// System.cpp: implementation of the System class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "System.h"

#include "Exceptions.h"
#include "Tokenizer.h"
#include "Date.h"
#include "StringUtil.h"
#include "CriticalSection.h"
#include "memory_stream.h"
#include "BLOB.h"
#include "FileUtil.h"

// Estis códigos han sido extraidos de las siguientes URL's:
// http://msdn.microsoft.com/library/default.asp?url=/library/en-us/sysinfo/base/getting_the_system_version.asp
// http://msdn.microsoft.com/library/en-us/sysinfo/base/getting_the_system_version.asp

#define BUFSIZE 80

#define VER_SUITE_PERSONAL                  0x00000200
#define VER_SUITE_BLADE                     0x00000400

#define VER_NT_WORKSTATION              0x0000001
#define VER_NT_DOMAIN_CONTROLLER        0x0000002
#define VER_NT_SERVER                   0x0000003

#define VER_SUITE_ENTERPRISE                0x00000002
#define VER_SUITE_DATACENTER                0x00000080

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace stream
{

/// namespace util
namespace util
{

// Extraido del Platform SDK
	typedef struct OSVERSIONINFO_STREAM {
    DWORD dwOSVersionInfoSize;
    DWORD dwMajorVersion;
    DWORD dwMinorVersion;
    DWORD dwBuildNumber;
    DWORD dwPlatformId;
    CHAR   szCSDVersion[ 128 ];     // Maintenance string for PSS usage
    WORD   wServicePackMajor;
    WORD   wServicePackMinor;
    WORD   wSuiteMask;
    BYTE  wProductType;
    BYTE  wReserved;
} OSVERSIONINFOEXA_STREAM;

System::System()
{

}

System::~System()
{

}

std::string System::getOperatingSystemId()
{
	std::string retvalue = "";
   OSVERSIONINFOEXA_STREAM osvi;
   BOOL bOsVersionInfoEx;

   // Try calling GetVersionEx using the OSVERSIONINFOEX structure.
   // If that fails, try using the OSVERSIONINFO structure.

   ZeroMemory(&osvi, sizeof(OSVERSIONINFOEXA_STREAM));
   osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXA_STREAM);

   if( (bOsVersionInfoEx = GetVersionEx ((OSVERSIONINFO *) &osvi)) == 0)
   {
      osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
      if (! GetVersionEx ( (OSVERSIONINFO *) &osvi) ) 
         return "";
   }

   switch (osvi.dwPlatformId)
   {
      // Test for the Windows NT product family.
      case VER_PLATFORM_WIN32_NT:

         // Test for the specific product.
         if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2 )
            retvalue += "Microsoft Windows Server 2003, ";

         if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1 )
            retvalue += "Microsoft Windows XP ";

         if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0 )
            retvalue += "Microsoft Windows 2000 ";

         if ( osvi.dwMajorVersion <= 4 )
            retvalue += "Microsoft Windows NT ";

         // Test for specific product on Windows NT 4.0 SP6 and later.
         if( bOsVersionInfoEx )
         {
            // Test for the workstation type.
//#if(WINVER >= 0x0500)
            if ( osvi.wProductType == VER_NT_WORKSTATION )
            {
               if( osvi.dwMajorVersion == 4 )
                  retvalue += "Workstation 4.0 ";
               else if( osvi.wSuiteMask & VER_SUITE_PERSONAL )
                  retvalue += "Home Edition ";
               else
                  retvalue += "Professional ";
            }
            
            // Test for the server type.
            else if ( osvi.wProductType == VER_NT_SERVER || 
                      osvi.wProductType == VER_NT_DOMAIN_CONTROLLER )
            {
               if( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2 )
               {
                  if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
                     retvalue += "Datacenter Edition ";
                  else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
                     retvalue += "Enterprise Edition ";
                  else if ( osvi.wSuiteMask == VER_SUITE_BLADE )
                     retvalue += "Web Edition ";
                  else
                     retvalue += "Standard Edition ";
               }

               else if( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0 )
               {
                  if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
                     retvalue += "Datacenter Server ";
                  else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
                     retvalue += "Advanced Server ";
                  else
                     retvalue += "Server ";
               }

               else  // Windows NT 4.0 
               {
                  if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
                     retvalue += "Server 4.0, Enterprise Edition ";
                  else
                     retvalue += "Server 4.0 ";
               }
            }
//#endif // WINVER >= 0x0500
         }
         else  // Test for specific product on Windows NT 4.0 SP5 and earlier
         {
            HKEY hKey;
            char szProductType[BUFSIZE];
            DWORD dwBufLen=BUFSIZE;
            LONG lRet;

            lRet = RegOpenKeyEx( HKEY_LOCAL_MACHINE,
               "SYSTEM\\CurrentControlSet\\Control\\ProductOptions",
               0, KEY_QUERY_VALUE, &hKey );
            if( lRet != ERROR_SUCCESS )
               return "";

            lRet = RegQueryValueEx( hKey, "ProductType", NULL, NULL,
               (LPBYTE) szProductType, &dwBufLen);
            if( (lRet != ERROR_SUCCESS) || (dwBufLen > BUFSIZE) )
               return "";

            RegCloseKey( hKey );

            if ( lstrcmpi( "WINNT", szProductType) == 0 )
               retvalue += "Workstation ";
            if ( lstrcmpi( "LANMANNT", szProductType) == 0 )
               retvalue += "Server ";
            if ( lstrcmpi( "SERVERNT", szProductType) == 0 )
               retvalue += "Advanced Server ";

			retvalue += StringUtil::toString(osvi.dwMajorVersion);
			retvalue += ".";
			retvalue +=  StringUtil::toString(osvi.dwMinorVersion);
			retvalue += " ";

         }

      // Display service pack (if any) and build number.

         if( osvi.dwMajorVersion == 4 && 
             lstrcmpi( osvi.szCSDVersion, "Service Pack 6" ) == 0 )
         {
            HKEY hKey;
            LONG lRet;

            // Test for SP6 versus SP6a.
            lRet = RegOpenKeyEx( HKEY_LOCAL_MACHINE,
               "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Hotfix\\Q246009",
               0, KEY_QUERY_VALUE, &hKey );
            if( lRet == ERROR_SUCCESS )
			{
				retvalue += "Service Pack 6a (Build " + StringUtil::toString(osvi.dwBuildNumber & 0xFFFF) + ")";               
			}
            else // Windows NT 4.0 prior to SP6a
            {
				retvalue += osvi.szCSDVersion;
				retvalue += " (Build " + StringUtil::toString(osvi.dwBuildNumber & 0xFFFF) + ")";
            }

            RegCloseKey( hKey );
         }
         else // not Windows NT 4.0 
         {
			 retvalue += osvi.szCSDVersion;
			 retvalue += " (Build " + StringUtil::toString(osvi.dwBuildNumber & 0xFFFF) + ")";
            
         }


         break;

      // Test for the Windows Me/98/95.
      case VER_PLATFORM_WIN32_WINDOWS:

         if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 0)
         {
             retvalue += "Microsoft Windows 95 ";
             if ( osvi.szCSDVersion[1] == 'C' || osvi.szCSDVersion[1] == 'B' )
                retvalue += "OSR2 ";
         } 

         if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 10)
         {
             retvalue += "Microsoft Windows 98 ";
             if ( osvi.szCSDVersion[1] == 'A' )
                retvalue += "SE ";
         } 

         if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 90)
         {
             retvalue += "Microsoft Windows Millennium Edition";
         } 
         break;

      case VER_PLATFORM_WIN32s:

         retvalue += "Microsoft Win32s";
         break;
   }

   return retvalue;

}


std::string System::getIEAgent()
{
	char buffer[1000];
	DWORD buffSize = 1000;
	
	if(ObtainUserAgentString(0,buffer,&buffSize) == NOERROR)
	{
		return buffer;
    }

	return "";
}

std::string System::getComputerName()
{
	unsigned long len = MAX_COMPUTERNAME_LENGTH + 1;
	char buffer[MAX_COMPUTERNAME_LENGTH + 1];
	
	if(!GetComputerName(buffer,&len))
	{
		throw new exceptions::Win32ErrorException(__FILE__,__LINE__);
	}


	return buffer;
}

std::string System::getFileVersion(const std::string& path)
{

	DWORD dwHandle = 0;
	DWORD versionInfoSize = 0;
	if((versionInfoSize = GetFileVersionInfoSize(const_cast<char*>(path.c_str()),&dwHandle)) != 0)
	{
		auto_array_ptr<char> versionInfo(versionInfoSize);
		if(!GetFileVersionInfo(const_cast<char*>(path.c_str()),0,versionInfoSize,versionInfo.get()))
			throw new exceptions::Win32ErrorException(__FILE__,__LINE__);

		VS_FIXEDFILEINFO vs_fileInfo;

		long* data;
		long length;
		if(!VerQueryValue(versionInfo.get(),"\\",(void**)&data,(unsigned int*)&length))
			throw new exceptions::Win32ErrorException(__FILE__,__LINE__);


		int a = 0;
		memcpy(&vs_fileInfo,data,length > sizeof(VS_FIXEDFILEINFO) ? sizeof(VS_FIXEDFILEINFO) : length);

		char version[1000];
		_snprintf(version,1000,"%d.%d.%d.%d",vs_fileInfo.dwFileVersionMS >> 16,
											vs_fileInfo.dwFileVersionMS & 0xFFFF,
											vs_fileInfo.dwFileVersionLS >> 16,
											vs_fileInfo.dwFileVersionLS & 0xFFFF);

		return version;
	}

	//throw new exceptions::Win32ErrorException(__FILE__,__LINE__); // Si el fichero no tiene recursos, se devuelve cadena vacía.
	return "";
}

std::string System::getTempPath()
{
	std::string result;
	char path[_MAX_PATH];

	if(::GetTempPath(_MAX_PATH,path) == 0)
	{
		throw new exceptions::Win32ErrorException(__FILE__,__LINE__);
	}
	else
	{
		result = path;
	}

	return result;
}

std::string System::getExecutablePath()
{
	std::string result;
	char path[_MAX_PATH];

	::GetModuleFileName(0,path,_MAX_PATH);

	result = path;

	return result;
}


HKEY HKEYFromString(const std::string& str)
{
	static std::map<std::string,HKEY> m_map;


	if(m_map.size() == 0)
	{
		m_map["HKCR"] = HKEY_CLASSES_ROOT;
		m_map["HKCU"] = HKEY_CURRENT_USER;
		m_map["HKLM"] = HKEY_LOCAL_MACHINE;
		m_map["HKU"] =  HKEY_USERS;
		m_map["HKPD"] = HKEY_PERFORMANCE_DATA;
		m_map["HKDD"] = HKEY_DYN_DATA;
		m_map["HKCC"] = HKEY_CURRENT_CONFIG;
		m_map["HKEY_CLASSES_ROOT"] = HKEY_CLASSES_ROOT;
		m_map["HKEY_CURRENT_USER"] = HKEY_CURRENT_USER;
		m_map["HKEY_LOCAL_MACHINE"] = HKEY_LOCAL_MACHINE;
		m_map["HKEY_USERS"] = HKEY_USERS;
		m_map["HKEY_PERFORMANCE_DATA"] = HKEY_PERFORMANCE_DATA;
		m_map["HKEY_DYN_DATA"] = HKEY_DYN_DATA;
		m_map["HKEY_CURRENT_CONFIG"] = HKEY_CURRENT_CONFIG;
	}


	return m_map[str];
}
std::string System::readRegistryString(const std::string& path)
{

	std::vector<std::string> vec = StringUtil::split(path,"\\",Tokenizer::MODE_ZERO);

	
	HKEY hKey = HKEYFromString(vec[0]);

	for(int i = 1 ; i < vec.size() - 1 ; i++)
	{
		HKEY hKey2;
		if(!RegOpenKeyEx(hKey,vec[i].c_str(),0,KEY_QUERY_VALUE,&hKey2))
		{
		}

		RegCloseKey(hKey);
		hKey = hKey2;
	}

	
	unsigned long bufferLength = 100;
	auto_array_ptr<unsigned char> buffer(bufferLength,new unsigned char[bufferLength]);
	
	unsigned long type = REG_SZ;
	long result = RegQueryValueEx(hKey,vec[vec.size() - 1].c_str(),NULL,&type,buffer.get(),&bufferLength);
  

	if(result == ERROR_MORE_DATA)
	{
		buffer = auto_array_ptr<unsigned char>(bufferLength,new unsigned char[bufferLength]);

		result = RegQueryValueEx(hKey,vec[vec.size() - 1].c_str(),NULL,&type,buffer.get(),&bufferLength);
	}


	RegCloseKey(hKey);

	if(result == 2)
	{
		// No existe 

		return "";
	}

	if(result != ERROR_SUCCESS)
	{
		SetLastError(result);
		throw new exceptions::Win32ErrorException(__FILE__,__LINE__);
	}

	return (char*)buffer.get();
}

std::string System::getIEVersion()
{
	std::string iePath = readRegistryString("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\IEXPLORE.EXE\\");

	if(iePath != "")
	{
		return getFileVersion(iePath);
	}

	return "";
}

void System::openShell(const std::string& command)
{
	ShellExecute(NULL,"open",command.c_str(),NULL,NULL,SW_SHOW);
}

long System::getProcessId()
{
	return ::GetCurrentProcessId();
}

void System::alert(const std::string& message)
{
	::MessageBox(0,message.c_str(),FileUtil::ExtractFileNameFromPath(getExecutablePath()).c_str(),MB_OK | MB_ICONWARNING);
}

bool System::question(const std::string& message)
{
	if(::MessageBox(0,message.c_str(),FileUtil::ExtractFileNameFromPath(getExecutablePath()).c_str(),MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		return true;
	}

	return false;
}

std::string System::getEnvironmentalVariable(const std::string& name)
{
	return getenv(name.c_str());
}

} // namespace util

} // namespace stream