# Microsoft Developer Studio Generated NMAKE File, Based on ctsql.dsp
!IF "$(CFG)" == ""
CFG=ctsql - Win32 Release_TS
!MESSAGE No configuration specified. Defaulting to ctsql - Win32 Release_TS.
!ENDIF 

!IF "$(CTESQL)" == ""
CTESQL=..
!MESSAGE No CTESQL environment variable specified. Defaulting to $(CTESQL)
!ENDIF

!IF "$(PHPBASE)" == ""
!MESSAGE No PHPBASE environment variable specified.
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(WIN32BUILD)" == ""
WIN32BUILD=$(PHPBASE)\..\win32build
!MESSAGE No WIN32BUILD environment variable specified. Defaulting to $(WIN32BUILD)
!ENDIF 

#identify PHP version
!IF EXISTS("$(PHPBASE)\Release_TS\php4ts.lib") || EXISTS("$(PHPBASE)\Release_TS_Inline\php4ts.lib") || EXISTS("$(PHPBASE)\Debug_TS\php4ts_debug.lib")
PHPVER=4
!ELSE
!IF EXISTS("$(PHPBASE)\Release_TS\php5ts.lib") || EXISTS("$(PHPBASE)\Release_TS_Inline\php5ts.lib") || EXISTS("$(PHPBASE)\Debug_TS\php5ts_debug.lib")
PHPVER=5
!ENDIF
!ENDIF

!IF "$(PHPVER)" == ""
!ERROR  cannot identify PHP version (php?ts.lib not found)
!ELSE
!MESSAGE Identified PHP version $(PHPVER)
!ENDIF 

!IF "$(CFG)" != "ctsql - Win32 Release_TS" && "$(CFG)" != "ctsql - Win32 Debug_TS" && "$(CFG)" != "ctsql - Win32 Release_DBG_TS"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ctsql - Win32 Release_TS"

OUTDIR=.\Release_TS
INTDIR=.\Release_TS
# Begin Custom Macros
OutDir=.\Release_TS
# End Custom Macros

ALL : "$(OUTDIR)\php_ctsql.dll"


CLEAN :
	-@erase "$(INTDIR)\ctsql.obj"
	-@erase "$(INTDIR)\*.idb"
	-@erase "$(INTDIR)\*.pch"
	-@erase "$(OUTDIR)\php_ctsql.dll"
	-@erase "$(OUTDIR)\php_ctsql.exp"
	-@erase "$(OUTDIR)\php_ctsql.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "$(PHPBASE)" /I "$(PHPBASE)\Zend" /I "$(PHPBASE)\TSRM" /I "$(PHPBASE)\main" /I "$(CTESQL)\ctreeESQL\include\\" /I "$(CTESQL)\ctreeESQL\src\public\os\windows" /D "WIN32" /D "CTSQL_EXPORTS" /D "COMPILE_DL_CTSQL" /D ZTS=1 /D HAVE_CTSQL=1 /D ZEND_DEBUG=0 /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ZEND_WIN32" /D "PHP_WIN32" /Fp"$(INTDIR)\ctsql.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ctsql.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=ws2_32.lib php$(PHPVER)ts.lib resolv.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ws2_32.lib libctesql.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\php_ctsql.pdb" /machine:I386 /nodefaultlib:"LIBCMT" /out:"$(OUTDIR)\php_ctsql.dll" /implib:"$(OUTDIR)\php_ctsql.lib" /libpath:"$(PHPBASE)\Release_TS" /libpath:"$(PHPBASE)\Release_TS_Inline" /libpath:"$(CTESQL)\ctreeESQL\lib" /libpath:"$(WIN32BUILD)\lib" 
LINK32_OBJS= \
	"$(INTDIR)\ctsql.obj"

"$(OUTDIR)\php_ctsql.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ctsql - Win32 Debug_TS"

OUTDIR=.\Debug_TS
INTDIR=.\Debug_TS
# Begin Custom Macros
OutDir=.\Debug_TS
# End Custom Macros

ALL : "$(OUTDIR)\php_ctsql.dll" "$(OUTDIR)\ctsql.bsc"


CLEAN :
	-@erase "$(INTDIR)\ctsql.obj"
	-@erase "$(INTDIR)\ctsql.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ctsql.bsc"
	-@erase "$(OUTDIR)\php_ctsql.dll"
	-@erase "$(OUTDIR)\php_ctsql.exp"
	-@erase "$(OUTDIR)\php_ctsql.ilk"
	-@erase "$(OUTDIR)\php_ctsql.lib"
	-@erase "$(OUTDIR)\php_ctsql.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /GX /ZI /Od /I "$(PHPBASE)" /I "$(PHPBASE)\Zend" /I "$(PHPBASE)\TSRM" /I "$(PHPBASE)\main" /I "$(CTESQL)\ctreeESQL\include\\" /I "$(CTESQL)\ctreeESQL\src\public\os\windows" /D "WIN32" /D "CTSQL_EXPORTS" /D "COMPILE_DL_CTSQL" /D ZTS=1 /D HAVE_CTSQL=1 /D ZEND_DEBUG=1 /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ZEND_WIN32" /D "PHP_WIN32" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ctsql.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ctsql.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ctsql.sbr"

"$(OUTDIR)\ctsql.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=php$(PHPVER)ts_debug.lib resolv.lib gdi32.lib kernel32.lib user32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib ws2_32.lib libctesql.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\php_ctsql.pdb" /debug /machine:I386 /nodefaultlib:"LIBCMT.lib" /out:"$(OUTDIR)\php_ctsql.dll" /implib:"$(OUTDIR)\php_ctsql.lib" /libpath:"$(PHPBASE)\Debug_TS" /libpath:"$(CTESQL)\ctreeESQL\lib" /libpath:"$(WIN32BUILD)\lib" 
LINK32_OBJS= \
	"$(INTDIR)\ctsql.obj"

"$(OUTDIR)\php_ctsql.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ctsql - Win32 Release_DBG_TS"

OUTDIR=.\ctsql___Win32_Release_DBG_TS
INTDIR=.\ctsql___Win32_Release_DBG_TS

ALL : ".\Release_TS\php_ctsql.dll"


CLEAN :
	-@erase "$(INTDIR)\ctsql.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\php_ctsql.exp"
	-@erase "$(OUTDIR)\php_ctsql.lib"
	-@erase ".\Release_TS\php_ctsql.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /Zi /O2 /I "$(PHPBASE)" /I "$(PHPBASE)\Zend" /I "$(PHPBASE)\TSRM" /I "$(PHPBASE)\main" /I "$(CTESQL)\ctreeESQL\include\\" /I "$(CTESQL)\ctreeESQL\src\public\os\windows" /D "WIN32" /D "CTSQL_EXPORTS" /D "COMPILE_DL_CTSQL" /D ZTS=1 /D HAVE_CTSQL=1 /D ZEND_DEBUG=0 /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ZEND_WIN32" /D "PHP_WIN32" /Fp"$(INTDIR)\ctsql.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ctsql.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=ws2_32.lib php$(PHPVER)ts.lib resolv.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ws2_32.lib libctesql.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\php_ctsql.pdb" /machine:I386 /nodefaultlib:"LIBCMT" /out:"Release_TS/php_ctsql.dll" /implib:"$(OUTDIR)\php_ctsql.lib" /libpath:"$(PHPBASE)\Release_TS" /libpath:"$(PHPBASE)\Release_TS_Inline" /libpath:"$(CTESQL)\ctreeESQL\lib" /libpath:"$(WIN32BUILD)\lib" 
LINK32_OBJS= \
	"$(INTDIR)\ctsql.obj"

".\Release_TS\php_ctsql.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 



!IF "$(CFG)" == "ctsql - Win32 Release_TS" || "$(CFG)" == "ctsql - Win32 Debug_TS" || "$(CFG)" == "ctsql - Win32 Release_DBG_TS"
SOURCE=.\ctsql.c

!IF  "$(CFG)" == "ctsql - Win32 Release_TS"


"$(INTDIR)\ctsql.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "ctsql - Win32 Debug_TS"


"$(INTDIR)\ctsql.obj"	"$(INTDIR)\ctsql.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "ctsql - Win32 Release_DBG_TS"


"$(INTDIR)\ctsql.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 


!ENDIF 

