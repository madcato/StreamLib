// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__16F2140E_792B_4651_9964_2608508B0B24__INCLUDED_)
#define AFX_STDAFX_H__16F2140E_792B_4651_9964_2608508B0B24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable: 4786)	// stl warning

// Windows Standard Includes
#define _WIN32_WINNT 0x0400

#include <winsock2.h>
#include <windows.h>

#include <wincrypt.h>
#include <tchar.h>
#include <Schnlsp.h>
#define SECURITY_WIN32
#include <Sspi.h>
#include <Winldap.h>
#include <Winber.h>

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



#define MY_ENCODING_TYPE  (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)
#define MAX_NAME 256
#define RC4_KEYLEN 128

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__16F2140E_792B_4651_9964_2608508B0B24__INCLUDED_)
