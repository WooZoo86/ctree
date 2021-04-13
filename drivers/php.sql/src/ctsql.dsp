# Microsoft Developer Studio Project File - Name="ctsql" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ctsql - Win32 Release_TS
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ctsql.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ctsql.mak" CFG="ctsql - Win32 Release_TS"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ctsql - Win32 Release_TS" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ctsql - Win32 Debug_TS" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ctsql - Win32 Release_DBG_TS" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ctsql - Win32 Release_TS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release_TS"
# PROP BASE Intermediate_Dir "Release_TS"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release_TS"
# PROP Intermediate_Dir "Release_TS"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I "$(PHPBASE)" /I "$(PHPBASE)\Zend" /I "$(PHPBASE)\TSRM" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "COMPILE_DL_CTSQL" /D ZTS=1 /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "$(PHPBASE)" /I "$(PHPBASE)\Zend" /I "$(PHPBASE)\TSRM" /I "$(PHPBASE)\main" /I "$(CTESQL)\ctreeESQL\include" /I "$(CTESQL)\ctreeESQL\src\public\os\windows" /D "WIN32" /D "CTSQL_EXPORTS" /D "COMPILE_DL_CTSQL" /D ZTS=1 /D HAVE_CTSQL=1 /D ZEND_DEBUG=0 /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ZEND_WIN32" /D "PHP_WIN32" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x406 /d "NDEBUG"
# ADD RSC /l 0x406 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib php4ts.lib /nologo /dll /machine:I386
# ADD LINK32 ws2_32.lib php4ts.lib resolv.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ws2_32.lib libctesql.lib /nologo /dll /machine:I386 /nodefaultlib:"LIBCMT" /out:"Release_TS/php_ctsql.dll" /libpath:"$(PHPBASE)\Release_TS" /libpath:"$(PHPBASE)\Release_TS_Inline" /libpath:"$(CTESQL)\ctreeESQL\lib"
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "ctsql - Win32 Debug_TS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Debug_TS"
# PROP BASE Intermediate_Dir "Debug_TS"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Debug_TS"
# PROP Intermediate_Dir "Debug_TS"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I "$(PHPBASE)" /I "$(PHPBASE)\Zend" /I "$(PHPBASE)\TSRM" /I "mssql-70" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "COMPILE_DL_CTSQL" /D ZTS=1 /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /ZI /Od /I "$(CTESQL)\ctreeESQL\include" /I "$(CTESQL)\ctreeESQL\src\public\os\windows" /D ZEND_DEBUG=1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ctsql_EXPORTS" /D "COMPILE_DL_CTSQL" /D ZTS=1 /D "ZEND_WIN32" /D "PHP_WIN32" /D HAVE_CTSQL=1 /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x406 /d "NDEBUG"
# ADD RSC /l 0x406 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib php4ts.lib /nologo /dll /machine:I386
# ADD LINK32 php4ts_debug.lib resolv.lib gdi32.lib kernel32.lib user32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib ws2_32.lib libctesql.lib /nologo /dll /incremental:yes /debug /machine:I386 /nodefaultlib:"LIBCMT.lib" /out:"Debug_TS/php_ctsql.dll" /libpath:"$(PHPBASE)\Debug_TS" /libpath:"$(CTESQL)\ctreeESQL\lib"

!ELSEIF  "$(CFG)" == "ctsql - Win32 Release_DBG_TS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ctsql___Win32_Release_DBG_TS"
# PROP BASE Intermediate_Dir "ctsql___Win32_Release_DBG_TS"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ctsql___Win32_Release_DBG_TS"
# PROP Intermediate_Dir "ctsql___Win32_Release_DBG_TS"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /Zi /O2 /I "$(PHPBASE)" /I "$(PHPBASE)\Zend" /I "$(PHPBASE)\TSRM" /I "$(PHPBASE)\main" /I "$(CTESQL)\ctreeESQL\include" /I "$(CTESQL)\ctreeESQL\src\public\os\windows" /D "WIN32" /D "CTSQL_EXPORTS" /D "COMPILE_DL_CTSQL" /D ZTS=1 /D HAVE_CTSQL=1 /D ZEND_DEBUG=0 /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ZEND_WIN32" /D "PHP_WIN32" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O2 /I "$(PHPBASE)" /I "$(PHPBASE)\Zend" /I "$(PHPBASE)\TSRM" /I "$(PHPBASE)\main" /I "$(CTESQL)\ctreeESQL\include" /I "$(CTESQL)\ctreeESQL\src\public\os\windows" /D "WIN32" /D "CTSQL_EXPORTS" /D "COMPILE_DL_CTSQL" /D ZTS=1 /D HAVE_CTSQL=1 /D ZEND_DEBUG=0 /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ZEND_WIN32" /D "PHP_WIN32" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x406 /d "NDEBUG"
# ADD RSC /l 0x406 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ws2_32.lib php4ts.lib resolv.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ws2_32.lib libctesql.lib /nologo /dll /machine:I386 /out:"Release_TS/php_ctsql.dll" /libpath:"$(PHPBASE)\Release_TS" /libpath:"$(PHPBASE)\Release_TS_Inline" /libpath:"$(CTESQL)\ctreeESQL\lib"
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 ws2_32.lib php4ts.lib resolv.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ws2_32.lib libctesql.lib /nologo /dll /machine:I386 /nodefaultlib:"LIBCMT" /out:"Release_TS/php_ctsql.dll" /libpath:"$(PHPBASE)\Release_TS" /libpath:"$(PHPBASE)\Release_TS_Inline" /libpath:"$(CTESQL)\ctreeESQL\lib"
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ENDIF 

# Begin Target

# Name "ctsql - Win32 Release_TS"
# Name "ctsql - Win32 Debug_TS"
# Name "ctsql - Win32 Release_DBG_TS"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ctsql.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ctsql.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
