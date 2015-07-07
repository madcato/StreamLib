# Microsoft Developer Studio Project File - Name="Stream" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Stream - Win32 DebugMTDLL
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Stream.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Stream.mak" CFG="Stream - Win32 DebugMTDLL"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Stream - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Stream - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "Stream - Win32 ReleaseMT" (based on "Win32 (x86) Static Library")
!MESSAGE "Stream - Win32 DebugMT" (based on "Win32 (x86) Static Library")
!MESSAGE "Stream - Win32 ReleaseMTDLL" (based on "Win32 (x86) Static Library")
!MESSAGE "Stream - Win32 DebugMTDLL" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/dlib/Stream", GQAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Stream - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "output\Release"
# PROP Intermediate_Dir "output\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "." /I ".\zlib" /I ".\src" /I ".\src\io" /I ".\src\net" /I ".\src\sync" /I ".\src\util" /I ".\src\sql" /I ".\src\exceptions" /I ".\src\cryptoapi" /I ".\src\zip" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FR /YX"stdafx.h" /FD /c
# ADD BASE RSC /l 0xc0a /d "NDEBUG"
# ADD RSC /l 0xc0a /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib\Stream.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy *.h ".\include"	copy .\src\cryptoapi\*.h ".\include"	copy .\src\exceptions\*.h ".\include"	copy .\src\io\*.h ".\include"	copy .\src\net\*.h ".\include"	copy .\src\sql\*.h ".\include"	copy .\src\sync\*.h ".\include"	copy .\src\util\*.h ".\include"	copy .\src\zip\*.h ".\include"	copy .\src\mime\*.h ".\include"	copy .\src\*.h ".\include"	MakeDoc.bat	del ".\include\stdafx.h"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Stream - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "output\Debug"
# PROP Intermediate_Dir "output\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "." /I ".\zlib" /I ".\src" /I ".\src\io" /I ".\src\net" /I ".\src\sync" /I ".\src\util" /I ".\src\sql" /I ".\src\exceptions" /I ".\src\cryptoapi" /I ".\src\zip" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0xc0a /d "_DEBUG"
# ADD RSC /l 0xc0a /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib\Streamd.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy *.h ".\include"	copy .\src\cryptoapi\*.h ".\include"	copy .\src\exceptions\*.h ".\include"	copy .\src\io\*.h ".\include"	copy .\src\net\*.h ".\include"	copy .\src\sql\*.h ".\include"	copy .\src\sync\*.h ".\include"	copy .\src\util\*.h ".\include"	copy .\src\zip\*.h ".\include"	copy .\src\mime\*.h ".\include"	copy .\src\*.h ".\include"	MakeDoc.bat	del  ".\include\stdafx.h"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Stream - Win32 ReleaseMT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Stream___Win32_ReleaseMT"
# PROP BASE Intermediate_Dir "Stream___Win32_ReleaseMT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "output\ReleaseMT"
# PROP Intermediate_Dir "output\ReleaseMT"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "." /I ".\zlib" /I ".\src" /I ".\src\io" /I ".\src\net" /I ".\src\sync" /I ".\src\util" /I ".\src\sql" /I ".\src\exceptions" /I ".\src\cryptoapi" /I ".\src\zip" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0xc0a /d "NDEBUG"
# ADD RSC /l 0xc0a /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib\StreamMT.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy *.h ".\include"	copy .\src\cryptoapi\*.h ".\include"	copy .\src\exceptions\*.h ".\include"	copy .\src\io\*.h ".\include"	copy .\src\net\*.h ".\include"	copy .\src\sql\*.h ".\include"	copy .\src\sync\*.h ".\include"	copy .\src\util\*.h ".\include"	copy .\src\zip\*.h ".\include"	copy .\src\mime\*.h ".\include"	copy .\src\*.h ".\include"	MakeDoc.bat	del ".\include\stdafx.h"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Stream - Win32 DebugMT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Stream___Win32_DebugMT"
# PROP BASE Intermediate_Dir "Stream___Win32_DebugMT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "output\DebugMT"
# PROP Intermediate_Dir "output\DebugMT"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "." /I ".\zlib" /I ".\src" /I ".\src\io" /I ".\src\net" /I ".\src\sync" /I ".\src\util" /I ".\src\sql" /I ".\src\exceptions" /I ".\src\cryptoapi" /I ".\src\zip" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0xc0a /d "_DEBUG"
# ADD RSC /l 0xc0a /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib\StreamMTd.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy *.h ".\include"	copy .\src\cryptoapi\*.h ".\include"	copy .\src\exceptions\*.h ".\include"	copy .\src\io\*.h ".\include"	copy .\src\net\*.h ".\include"	copy .\src\sql\*.h ".\include"	copy .\src\sync\*.h ".\include"	copy .\src\util\*.h ".\include"	copy .\src\zip\*.h ".\include"	copy .\src\mime\*.h ".\include"	copy .\src\*.h ".\include"	MakeDoc.bat	del ".\include\stdafx.h"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Stream - Win32 ReleaseMTDLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Stream___Win32_ReleaseMTDLL"
# PROP BASE Intermediate_Dir "Stream___Win32_ReleaseMTDLL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "output\ReleaseMTDLL"
# PROP Intermediate_Dir "output\ReleaseMTDLL"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "." /I ".\zlib" /I ".\src" /I ".\src\io" /I ".\src\net" /I ".\src\sync" /I ".\src\util" /I ".\src\sql" /I ".\src\exceptions" /I ".\src\cryptoapi" /I ".\src\zip" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FR /YX"stdafx.h" /FD /c
# ADD BASE RSC /l 0xc0a /d "NDEBUG"
# ADD RSC /l 0xc0a /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib\StreamMTDLL.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy *.h ".\include"	copy .\src\cryptoapi\*.h ".\include"	copy .\src\exceptions\*.h ".\include"	copy .\src\io\*.h ".\include"	copy .\src\net\*.h ".\include"	copy .\src\sql\*.h ".\include"	copy .\src\sync\*.h ".\include"	copy .\src\util\*.h ".\include"	copy .\src\zip\*.h ".\include"	copy .\src\mime\*.h ".\include"	copy .\src\*.h ".\include"	MakeDoc.bat	del ".\include\stdafx.h"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Stream - Win32 DebugMTDLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Stream___Win32_DebugMTDLL"
# PROP BASE Intermediate_Dir "Stream___Win32_DebugMTDLL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "output\DebugMTDLL"
# PROP Intermediate_Dir "output\DebugMTDLL"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I ".\zlib" /I ".\src" /I ".\src\io" /I ".\src\net" /I ".\src\sync" /I ".\src\util" /I ".\src\sql" /I ".\src\exceptions" /I ".\src\cryptoapi" /I ".\src\zip" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0xc0a /d "_DEBUG"
# ADD RSC /l 0xc0a /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib\StreamMTDLLd.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy *.h ".\Include"	copy .\src\cryptoapi\*.h ".\Include"	copy .\src\exceptions\*.h ".\include"	copy .\src\io\*.h ".\include"	copy .\src\net\*.h ".\include"	copy .\src\sql\*.h ".\include"	copy .\src\sync\*.h ".\include"	copy .\src\util\*.h ".\include"	copy .\src\zip\*.h ".\include"	copy .\src\mime\*.h ".\include"	copy .\src\mime\*.h ".\include"	copy .\src\*.h ".\include"	MakeDoc.bat	del ".\include\stdafx.h"
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "Stream - Win32 Release"
# Name "Stream - Win32 Debug"
# Name "Stream - Win32 ReleaseMT"
# Name "Stream - Win32 DebugMT"
# Name "Stream - Win32 ReleaseMTDLL"
# Name "Stream - Win32 DebugMTDLL"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\util\Application.cpp
# End Source File
# Begin Source File

SOURCE=.\src\io\B64.cpp
# End Source File
# Begin Source File

SOURCE=.\src\io\B64InputStream.cpp
# End Source File
# Begin Source File

SOURCE=.\src\io\B64OutputStream.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Base64Coder.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\BigInteger.cpp
# End Source File
# Begin Source File

SOURCE=.\src\io\BLOBData.cpp
# End Source File
# Begin Source File

SOURCE=.\src\io\BLOBInputStream.cpp
# End Source File
# Begin Source File

SOURCE=.\src\io\BLOBOutputStream.cpp
# End Source File
# Begin Source File

SOURCE=.\src\io\BufferedReader.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\Caesar.cpp
# End Source File
# Begin Source File

SOURCE=.\src\cryptoapi\Certificate.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\ClassFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeBar.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\CommandProcessor.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sql\Connection.cpp
# End Source File
# Begin Source File

SOURCE=.\src\io\console.cpp
# End Source File
# Begin Source File

SOURCE=.\src\io\ConsoleInputStream.cpp
# End Source File
# Begin Source File

SOURCE=.\src\io\ConsoleOutputStream.cpp
# End Source File
# Begin Source File

SOURCE=.\src\cryptoapi\CryptContext.cpp
# End Source File
# Begin Source File

SOURCE=.\src\cryptoapi\CryptException.cpp
# End Source File
# Begin Source File

SOURCE=.\src\cryptoapi\CryptMessage.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\CW3CLog.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\Date.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sql\DB.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\DiffTime.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\DynamicClass.cpp
# End Source File
# Begin Source File

SOURCE=.\src\io\EncryptedInputStream.cpp
# End Source File
# Begin Source File

SOURCE=.\src\io\EncryptedOutputStream.cpp
# End Source File
# Begin Source File

SOURCE=.\src\exceptions\Exceptions.cpp
# End Source File
# Begin Source File

SOURCE=.\src\io\FileData.cpp
# End Source File
# Begin Source File

SOURCE=.\src\io\FileInputStream.cpp
# End Source File
# Begin Source File

SOURCE=.\src\io\FileOutputStream.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\FileUtil.cpp
# End Source File
# Begin Source File

SOURCE=.\src\io\FilterInputStream.cpp
# End Source File
# Begin Source File

SOURCE=.\src\io\FilterOutputStream.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\FLineParser.cpp
# End Source File
# Begin Source File

SOURCE=.\src\zip\GZInputStream.cpp
# End Source File
# Begin Source File

SOURCE=.\src\zip\GZIP.cpp
# End Source File
# Begin Source File

SOURCE=.\src\zip\GZIPInputStream.cpp
# End Source File
# Begin Source File

SOURCE=.\src\zip\GZIPOutputStream.cpp
# End Source File
# Begin Source File

SOURCE=.\src\zip\GZOutputStream.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\HashObj.cpp
# End Source File
# Begin Source File

SOURCE=.\src\io\HexBin.cpp
# End Source File
# Begin Source File

SOURCE=.\src\net\HTMLIncluder.cpp
# End Source File
# Begin Source File

SOURCE=.\src\net\HTMLTPage.cpp
# End Source File
# Begin Source File

SOURCE=.\src\net\HTTPConnection.cpp
# End Source File
# Begin Source File

SOURCE=.\src\net\HTTPControllerManager.cpp
# End Source File
# Begin Source File

SOURCE=.\src\net\HTTPServerConnection.cpp
# End Source File
# Begin Source File

SOURCE=.\src\io\IData.cpp
# End Source File
# Begin Source File

SOURCE=.\src\io\IFilterInputStream.cpp
# End Source File
# Begin Source File

SOURCE=.\src\io\IFilterOutputStream.cpp
# End Source File
# Begin Source File

SOURCE=.\src\io\IStreamRedirector.cpp
# End Source File
# Begin Source File

SOURCE=.\src\net\LdapConnection.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\LiteLog.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\Log.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\LogFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\MD5.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mime\Mime.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mime\MimeChar.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mime\MimeCode.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mime\MimeType.cpp
# End Source File
# Begin Source File

SOURCE=.\src\net\NetCommandServer.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\PacketSorter.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\Parseador2.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\PersistentProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\PrepareCommand.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sql\PreparedStatement.cpp
# End Source File
# Begin Source File

SOURCE=.\src\io\PrintWriter.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\Properties.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\PropertyBag.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sync\ProtectedFIFO.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\ReplaceVariables.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\ResourceManager.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sql\ResultSet.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sync\Semaphore.cpp
# End Source File
# Begin Source File

SOURCE=.\src\net\ServerSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\Service.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\SimpleHash.cpp
# End Source File
# Begin Source File

SOURCE=.\src\net\SMTPSender.cpp
# End Source File
# Begin Source File

SOURCE=.\src\net\Socket.cpp
# End Source File
# Begin Source File

SOURCE=.\src\net\SocketBase.cpp
# End Source File
# Begin Source File

SOURCE=.\src\net\SocketServerUDP.cpp
# End Source File
# Begin Source File

SOURCE=.\src\net\SocksifiedSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\StateMachine.cpp
# End Source File
# Begin Source File

SOURCE=.\src\cryptoapi\Store.cpp
# End Source File
# Begin Source File

SOURCE=.\src\io\StreamDoubleRedirector.cpp
# End Source File
# Begin Source File

SOURCE=.\src\io\StreamRedirector.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\StringUtil.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\System.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\Tar.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\TarHeaderFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\TarReader.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\TarWriter.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sync\Thread.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sync\ThreadPool.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\Time_s.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sync\TimerControl.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\Tokenizer.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\UniqueID.cpp
# End Source File
# Begin Source File

SOURCE=.\src\net\WebApp.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\Wildcard.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\src\sql\ADOimpl.inl
# End Source File
# Begin Source File

SOURCE=.\src\util\Application.h
# End Source File
# Begin Source File

SOURCE=.\src\io\B64.h
# End Source File
# Begin Source File

SOURCE=.\src\io\B64InputStream.h
# End Source File
# Begin Source File

SOURCE=.\src\io\B64OutputStream.h
# End Source File
# Begin Source File

SOURCE=.\src\Base64Coder.h
# End Source File
# Begin Source File

SOURCE=.\src\util\BigInteger.h
# End Source File
# Begin Source File

SOURCE=.\src\io\Blob.h
# End Source File
# Begin Source File

SOURCE=.\src\io\BLOBData.h
# End Source File
# Begin Source File

SOURCE=.\src\io\BLOBInputStream.h
# End Source File
# Begin Source File

SOURCE=.\src\io\BLOBOutputStream.h
# End Source File
# Begin Source File

SOURCE=.\src\io\BufferedReader.h
# End Source File
# Begin Source File

SOURCE=.\src\util\Caesar.h
# End Source File
# Begin Source File

SOURCE=.\src\cryptoapi\Certificate.h
# End Source File
# Begin Source File

SOURCE=.\src\util\ClassFactory.h
# End Source File
# Begin Source File

SOURCE=.\CodeBar.h
# End Source File
# Begin Source File

SOURCE=.\src\util\CommandProcessor.h
# End Source File
# Begin Source File

SOURCE=.\src\sql\Connection.h
# End Source File
# Begin Source File

SOURCE=.\src\io\console.h
# End Source File
# Begin Source File

SOURCE=.\src\io\ConsoleInputStream.h
# End Source File
# Begin Source File

SOURCE=.\src\io\ConsoleOutputStream.h
# End Source File
# Begin Source File

SOURCE=.\src\io\CountReferencedBlob.h
# End Source File
# Begin Source File

SOURCE=.\src\sync\CriticalSection.h
# End Source File
# Begin Source File

SOURCE=.\src\cryptoapi\CryptContext.h
# End Source File
# Begin Source File

SOURCE=.\src\cryptoapi\CryptException.h
# End Source File
# Begin Source File

SOURCE=.\src\cryptoapi\CryptMessage.h
# End Source File
# Begin Source File

SOURCE=.\src\util\CW3CLog.h
# End Source File
# Begin Source File

SOURCE=.\src\util\Date.h
# End Source File
# Begin Source File

SOURCE=.\src\sql\DB.h
# End Source File
# Begin Source File

SOURCE=.\src\util\DiffTime.h
# End Source File
# Begin Source File

SOURCE=.\src\util\DynamicClass.h
# End Source File
# Begin Source File

SOURCE=.\src\io\EncryptedInputStream.h
# End Source File
# Begin Source File

SOURCE=.\src\io\EncryptedOutputStream.h
# End Source File
# Begin Source File

SOURCE=.\src\util\Entry2.h
# End Source File
# Begin Source File

SOURCE=.\src\exceptions\Exceptions.h
# End Source File
# Begin Source File

SOURCE=.\src\io\FileData.h
# End Source File
# Begin Source File

SOURCE=.\src\io\FileInputStream.h
# End Source File
# Begin Source File

SOURCE=.\src\io\FileOutputStream.h
# End Source File
# Begin Source File

SOURCE=.\src\util\FileUtil.h
# End Source File
# Begin Source File

SOURCE=.\src\io\FilterInputStream.h
# End Source File
# Begin Source File

SOURCE=.\src\io\FilterOutputStream.h
# End Source File
# Begin Source File

SOURCE=.\src\util\FLineParser.h
# End Source File
# Begin Source File

SOURCE=.\src\exceptions\gz_exceptions.h
# End Source File
# Begin Source File

SOURCE=.\src\zip\GZInputStream.h
# End Source File
# Begin Source File

SOURCE=.\src\zip\GZIP.h
# End Source File
# Begin Source File

SOURCE=.\src\zip\GZIPInputStream.h
# End Source File
# Begin Source File

SOURCE=.\src\zip\GZIPOutputStream.h
# End Source File
# Begin Source File

SOURCE=.\src\zip\GZOutputStream.h
# End Source File
# Begin Source File

SOURCE=.\src\util\HashObj.h
# End Source File
# Begin Source File

SOURCE=.\src\io\HexBin.h
# End Source File
# Begin Source File

SOURCE=.\src\net\HTMLIncluder.h
# End Source File
# Begin Source File

SOURCE=.\src\net\HTMLTPage.h
# End Source File
# Begin Source File

SOURCE=.\src\net\HTTPConnection.h
# End Source File
# Begin Source File

SOURCE=.\src\net\HTTPControllerManager.h
# End Source File
# Begin Source File

SOURCE=.\src\net\HTTPServerConnection.h
# End Source File
# Begin Source File

SOURCE=.\src\io\IData.h
# End Source File
# Begin Source File

SOURCE=.\src\io\IDataProcessor.h
# End Source File
# Begin Source File

SOURCE=.\src\io\IFilterInputStream.h
# End Source File
# Begin Source File

SOURCE=.\src\io\IFilterOutputStream.h
# End Source File
# Begin Source File

SOURCE=.\src\io\IInputStream.h
# End Source File
# Begin Source File

SOURCE=.\src\io\IOutputStream.h
# End Source File
# Begin Source File

SOURCE=.\src\io\IStreamRedirector.h
# End Source File
# Begin Source File

SOURCE=.\src\net\LdapConnection.h
# End Source File
# Begin Source File

SOURCE=.\src\util\LiteLog.h
# End Source File
# Begin Source File

SOURCE=.\src\util\Log.h
# End Source File
# Begin Source File

SOURCE=.\src\util\LogFactory.h
# End Source File
# Begin Source File

SOURCE=.\src\util\MD5.h
# End Source File
# Begin Source File

SOURCE=.\src\util\memory_stream.h
# End Source File
# Begin Source File

SOURCE=.\src\mime\Mime.h
# End Source File
# Begin Source File

SOURCE=.\src\mime\MimeChar.h
# End Source File
# Begin Source File

SOURCE=.\src\mime\MimeCode.h
# End Source File
# Begin Source File

SOURCE=.\src\net\NetCommandServer.h
# End Source File
# Begin Source File

SOURCE=.\src\util\PacketSorter.h
# End Source File
# Begin Source File

SOURCE=.\src\util\Parseador2.h
# End Source File
# Begin Source File

SOURCE=.\src\util\PersistentProperties.h
# End Source File
# Begin Source File

SOURCE=.\src\util\PrepareCommand.h
# End Source File
# Begin Source File

SOURCE=.\src\sql\PreparedStatement.h
# End Source File
# Begin Source File

SOURCE=.\src\io\PrintWriter.h
# End Source File
# Begin Source File

SOURCE=.\src\util\Properties.h
# End Source File
# Begin Source File

SOURCE=.\src\util\PropertyBag.h
# End Source File
# Begin Source File

SOURCE=.\src\sync\ProtectedFIFO.h
# End Source File
# Begin Source File

SOURCE=.\src\util\ReplaceVariables.h
# End Source File
# Begin Source File

SOURCE=.\src\util\ResourceManager.h
# End Source File
# Begin Source File

SOURCE=.\src\sql\ResultSet.h
# End Source File
# Begin Source File

SOURCE=.\src\sync\Semaphore.h
# End Source File
# Begin Source File

SOURCE=.\src\net\ServerSocket.h
# End Source File
# Begin Source File

SOURCE=.\src\util\Service.h
# End Source File
# Begin Source File

SOURCE=.\src\util\SimpleHash.h
# End Source File
# Begin Source File

SOURCE=.\src\net\SMTPSender.h
# End Source File
# Begin Source File

SOURCE=.\src\net\Socket.h
# End Source File
# Begin Source File

SOURCE=.\src\net\SocketBase.h
# End Source File
# Begin Source File

SOURCE=.\src\net\SocketServerUDP.h
# End Source File
# Begin Source File

SOURCE=.\src\net\SocksifiedSocket.h
# End Source File
# Begin Source File

SOURCE=.\src\net\sslsocket.h
# End Source File
# Begin Source File

SOURCE=.\src\util\StateMachine.h
# End Source File
# Begin Source File

SOURCE=.\src\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\src\cryptoapi\Store.h
# End Source File
# Begin Source File

SOURCE=.\src\Stream.h
# End Source File
# Begin Source File

SOURCE=.\src\io\StreamDoubleRedirector.h
# End Source File
# Begin Source File

SOURCE=.\src\io\StreamRedirector.h
# End Source File
# Begin Source File

SOURCE=.\src\util\StringUtil.h
# End Source File
# Begin Source File

SOURCE=.\src\util\System.h
# End Source File
# Begin Source File

SOURCE=.\src\util\Tar.h
# End Source File
# Begin Source File

SOURCE=.\src\util\TarHeader.h
# End Source File
# Begin Source File

SOURCE=.\src\util\TarHeaderFactory.h
# End Source File
# Begin Source File

SOURCE=.\src\util\TarReader.h
# End Source File
# Begin Source File

SOURCE=.\src\util\TarWriter.h
# End Source File
# Begin Source File

SOURCE=.\src\sync\Thread.h
# End Source File
# Begin Source File

SOURCE=.\src\sync\ThreadPool.h
# End Source File
# Begin Source File

SOURCE=.\src\util\Time_s.h
# End Source File
# Begin Source File

SOURCE=.\src\sync\TimerControl.h
# End Source File
# Begin Source File

SOURCE=.\src\util\Tokenizer.h
# End Source File
# Begin Source File

SOURCE=.\src\util\UniqueID.h
# End Source File
# Begin Source File

SOURCE=.\src\net\WebApp.h
# End Source File
# Begin Source File

SOURCE=.\src\util\Wildcard.h
# End Source File
# End Group
# End Target
# End Project
