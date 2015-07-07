# Microsoft Developer Studio Project File - Name="zlib32" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=zlib32 - Win32 DebugMTDLL
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "zlib32.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "zlib32.mak" CFG="zlib32 - Win32 DebugMTDLL"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "zlib32 - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "zlib32 - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "zlib32 - Win32 ReleaseMT" (based on "Win32 (x86) Static Library")
!MESSAGE "zlib32 - Win32 DebugMT" (based on "Win32 (x86) Static Library")
!MESSAGE "zlib32 - Win32 DebugMTDLL" (based on "Win32 (x86) Static Library")
!MESSAGE "zlib32 - Win32 ReleaseMTDLL" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "zlib32 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0xc0a /d "NDEBUG"
# ADD RSC /l 0xc0a /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Special Build Tool
TargetPath=.\Release\zlib32.lib
SOURCE="$(InputPath)"
PostBuild_Cmds=copy ..\*.h "d:\include"	copy $(TargetPath) "d:\lib"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "zlib32 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0xc0a /d "_DEBUG"
# ADD RSC /l 0xc0a /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\zlib32d.lib"
# Begin Special Build Tool
TargetPath=.\Debug\zlib32d.lib
SOURCE="$(InputPath)"
PostBuild_Cmds=copy ..\*.h "d:\include"	copy $(TargetPath) "d:\lib"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "zlib32 - Win32 ReleaseMT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "zlib32___Win32_ReleaseMT"
# PROP BASE Intermediate_Dir "zlib32___Win32_ReleaseMT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMT"
# PROP Intermediate_Dir "ReleaseMT"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0xc0a /d "NDEBUG"
# ADD RSC /l 0xc0a /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"ReleaseMT\zlib32MT.lib"
# Begin Special Build Tool
TargetPath=.\ReleaseMT\zlib32MT.lib
SOURCE="$(InputPath)"
PostBuild_Cmds=copy ..\*.h "d:\include"	copy $(TargetPath) "d:\lib"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "zlib32 - Win32 DebugMT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "zlib32___Win32_DebugMT"
# PROP BASE Intermediate_Dir "zlib32___Win32_DebugMT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugMT"
# PROP Intermediate_Dir "DebugMT"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0xc0a /d "_DEBUG"
# ADD RSC /l 0xc0a /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"DebugMT\zlib32MTd.lib"
# Begin Special Build Tool
TargetPath=.\DebugMT\zlib32MTd.lib
SOURCE="$(InputPath)"
PostBuild_Cmds=copy ..\*.h "d:\include"	copy $(TargetPath) "d:\lib"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "zlib32 - Win32 DebugMTDLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "zlib32___Win32_DebugMTDLL"
# PROP BASE Intermediate_Dir "zlib32___Win32_DebugMTDLL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugMTDLL"
# PROP Intermediate_Dir "DebugMTDLL"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0xc0a /d "_DEBUG"
# ADD RSC /l 0xc0a /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"DebugMT\zlib32MTd.lib"
# ADD LIB32 /nologo /out:"DebugMTDLL\zlib32MTDLLd.lib"
# Begin Special Build Tool
TargetPath=.\DebugMTDLL\zlib32MTDLLd.lib
SOURCE="$(InputPath)"
PostBuild_Cmds=copy ..\*.h "d:\include"	copy $(TargetPath) "d:\lib"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "zlib32 - Win32 ReleaseMTDLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "zlib32___Win32_ReleaseMTDLL"
# PROP BASE Intermediate_Dir "zlib32___Win32_ReleaseMTDLL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMTDLL"
# PROP Intermediate_Dir "ReleaseMTDLL"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0xc0a /d "NDEBUG"
# ADD RSC /l 0xc0a /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"ReleaseMT\zlib32MT.lib"
# ADD LIB32 /nologo /out:"ReleaseMTDLL\zlib32MTDLL.lib"
# Begin Special Build Tool
TargetPath=.\ReleaseMTDLL\zlib32MTDLL.lib
SOURCE="$(InputPath)"
PostBuild_Cmds=copy ..\*.h "d:\include"	copy $(TargetPath) "d:\lib"
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "zlib32 - Win32 Release"
# Name "zlib32 - Win32 Debug"
# Name "zlib32 - Win32 ReleaseMT"
# Name "zlib32 - Win32 DebugMT"
# Name "zlib32 - Win32 DebugMTDLL"
# Name "zlib32 - Win32 ReleaseMTDLL"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\adler32.c
# End Source File
# Begin Source File

SOURCE=..\compress.c
# End Source File
# Begin Source File

SOURCE=..\crc32.c
# End Source File
# Begin Source File

SOURCE=..\deflate.c
# End Source File
# Begin Source File

SOURCE=..\gzio.c
# End Source File
# Begin Source File

SOURCE=..\infblock.c
# End Source File
# Begin Source File

SOURCE=..\infcodes.c
# End Source File
# Begin Source File

SOURCE=..\inffast.c
# End Source File
# Begin Source File

SOURCE=..\inflate.c
# End Source File
# Begin Source File

SOURCE=..\inftrees.c
# End Source File
# Begin Source File

SOURCE=..\infutil.c
# End Source File
# Begin Source File

SOURCE=..\trees.c
# End Source File
# Begin Source File

SOURCE=..\uncompr.c
# End Source File
# Begin Source File

SOURCE=..\zutil.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\deflate.h
# End Source File
# Begin Source File

SOURCE=..\infblock.h
# End Source File
# Begin Source File

SOURCE=..\infcodes.h
# End Source File
# Begin Source File

SOURCE=..\inffast.h
# End Source File
# Begin Source File

SOURCE=..\inffixed.h
# End Source File
# Begin Source File

SOURCE=..\inftrees.h
# End Source File
# Begin Source File

SOURCE=..\infutil.h
# End Source File
# Begin Source File

SOURCE=..\trees.h
# End Source File
# Begin Source File

SOURCE=..\zconf.h
# End Source File
# Begin Source File

SOURCE=..\zlib.h
# End Source File
# Begin Source File

SOURCE=..\zutil.h
# End Source File
# End Group
# End Target
# End Project
