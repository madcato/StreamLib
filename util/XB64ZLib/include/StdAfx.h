
#if !defined(AFX_STDAFX_H__F4DADA3B_EAD3_4BD2_B018_F1AE4AF7AEC1__INCLUDED_)
#define AFX_STDAFX_H__F4DADA3B_EAD3_4BD2_B018_F1AE4AF7AEC1__INCLUDED_

#pragma warning(disable: 4786)	// stl warning

// Windows Standard Includes
#define _WIN32_WINNT 0x0400


#include <windows.h>
#include <winsock2.h>


#include <wincrypt.h>
#include <tchar.h>
#include <Schnlsp.h>
#define SECURITY_WIN32
#include <Sspi.h>
#include <Winldap.h>
//#include <Winber.h>

// C++ Standard Includes
#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>
#include <list>



// C Standard Includes
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <time.h>
#include <conio.h>
#include <process.h>
#include <assert.h>



#include <zlib.h>

#define MY_ENCODING_TYPE  (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)
#define MAX_NAME 256
#define RC4_KEYLEN 128

/**
	unsigned long definition.
*/
typedef unsigned long ulong;

/**
	unsigned char definition.
*/
typedef unsigned char uchar;


#endif // AFX_STDAFX_H__F4DADA3B_EAD3_4BD2_B018_F1AE4AF7AEC1__INCLUDED_