
#ifndef ___STREAMS_____H_
#define ___STREAMS_____H_

#pragma warning(disable: 4786)	// stl warning

// Windows Standard Includes

typedef unsigned long ulong;
typedef unsigned char uchar;

#define _WIN32_WINNT 0x0400

#include <windows.h>
#include <winsock2.h>

#include <wincrypt.h>
#include <tchar.h>
#include <Winldap.h>


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

// stream Includes
#include "CriticalSection.h"
#include "Exceptions.h"
#include "IInputStream.h"
#include "IOutputStream.h"
#include "FileInputStream.h"
#include "FileOutputStream.h"
#include "BufferedReader.h"
#include "ConsoleOutputStream.h"
#include "ConsoleInputStream.h"
#include "thread.h"
#include "Tokenizer.h"
#include "stringUtil.h"
#include "Semaphore.h"
#include "Entry2.h"
#include "Parseador2.h"
#include "base64coder.h"
#include "PrepareCommand.h"
#include "memory_stream.h"
#include "Blob.h"
#include "CountReferencedBlob.h"
#include "IDataProcessor.h"
#include "FilterInputStream.h"
#include "FilterOutputStream.h"
#include "FileUtil.h"
#include "CryptContext.h"
#include "Certificate.h"
#include "HashObj.h"
#include "Socket.h"
#include "ServerSocket.h"
#include "SocksifiedSocket.h"
#include "ReplaceVariables.h"
#include "ProtectedFIFO.h"
#include "IStreamRedirector.h"
#include "StreamRedirector.h"
#include "StreamDoubleRedirector.h"
#include "ILog.h"
#include "Log.h"
#include "LiteLog.h"
#include "entry2.h"
#include "parseador2.h"
#include "BolsaPropiedades.h"
#include "LdapConnection.h"
#include "PrintWriter.h"
#include "TarHeader.h"
#include "TarHeaderFactory.h"
#include "TarReader.h"
#include "TarWriter.h"
#include "Tar.h"
#include "B64.h"
#include "HexBin.h"
#include "B64OutputStream.h"
#include "B64InputStream.h"
#include "BigInteger.h"
#include "Caesar.h"
#include "System.h"
#include "Properties.h"
#include "PersistentProperties.h"
#include "CW3CLog.h"
#include "ResultSet.h"
#include "PreparedStatement.h"
#include "Connection.h"
#include "ResourceManager.h"
#include "Application.h"
#include "CountReferencedBlob.h"
#include "Certificate.h"
#include "CryptContext.h"
#include "Store.h"
#include "CryptException.h"
#include "IData.h"
#include "BLOBInputStream.h"
#include "BLOBOutputStream.h"
#include "BLOBData.h"
#include "HTMLIncluder.h"
#include "HTMLTPage.h"
#include "HTTPConnection.h"
#include "HTTPServerConnection.h"
#include "HTTPControllerManager.h"
#include "ClassFactory.h"
#include "WebApp.h"
#include "DiffTime.h"
#include "DB.h"
#include "NetCommandServer.h"
#include "StateMachine.h"
#include "FLineParser.h"
#include "ConOut.h"
#include "Time_s.h"
#include "Wildcard.h"
#include "DynamicClass.h"

#include <zlib.h>

#include "gz_exceptions.h"
#include "GZInputStream.h"
#include "GZOutputStream.h"
#include "GZIP.h"
#include "GZIPInputStream.h"
#include "GZIPOutputStream.h"

#include "MimeCode.h"
#include "MimeChar.h"
#include "Mime.h"
#include "SMTPSender.h"


//using namespace stream;
//using namespace stream::util;
//using namespace stream::io;
//using namespace stream::net;
//using namespace stream::sync;
//using namespace stream::sql;
//using namespace stream::cryptoapi;
//using namespace stream::zip;
//using namespace stream::mime;

//using namespace std;




#ifdef _DEBUG
#	ifdef _MT
#		ifdef _DLL
#			pragma comment(lib,"streamMTDLLd")
#			pragma comment(lib,"zlib32MTDLLd")
#			pragma message("namespace stream: MT DLL Debug Build")
#		else
#			pragma comment(lib,"streamMTd")
#			pragma comment(lib,"zlib32MTd")
#			pragma message("namespace stream: MT Static Debug Build")
#		endif
#	else
#		pragma comment(lib,"streamd")
#			pragma comment(lib,"zlib32d")
#		pragma message("namespace stream: Single Static Debug Build")
#	endif
#else
#	ifdef _MT
#		ifdef _DLL
#			pragma comment(lib,"streamMTDLL")
#			pragma comment(lib,"zlib32MTDLL")
#			pragma message("namespace stream: MT DLL Build")
#		else
#			pragma comment(lib,"streamMT")
#			pragma comment(lib,"zlib32MT")
#			pragma message("namespace stream: MT Static Build")
#		endif
#	else
#		pragma comment(lib,"stream")
#			pragma comment(lib,"zlib32")
#		pragma message("namespace stream: Single Static Build")
#	endif
#endif

#pragma message("namespace stream: Linking with ws2_32.lib. Winsock2")
#pragma comment(lib,"WS2_32.LIB")
#pragma message("namespace stream: Linking with Wldap32.lib. WinLdap")
#pragma comment(lib,"Wldap32.lib")
#pragma message("namespace stream: Linking with Version.lib. Base Services")
#pragma comment(lib,"version.lib")
#pragma message("namespace stream: Linking with Urlmon.lib. URL Monikers")
#pragma comment(lib,"Urlmon.lib")
#pragma message("namespace stream: Linking with crypt32.lib. CryptoAPI")
#pragma comment(lib,"crypt32.lib")





#endif ___STREAMS_____H_