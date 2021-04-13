echo off
set myBLD=YES
set myRUN=YES

rem Here we check the CMD Environment for Visual Studio
cl.exe >NUL 2>&1
if errorlevel 1 (
	echo cl.exe not found! Please set environment for Visual C/C++ compiler.
	exit /b 1
)
for /f "tokens=7" %%G IN ('cl.exe 2^>^&1 ^| find "Version"') DO set VERSION=%%G
::echo %VERSION%
for /f "tokens=1 delims=. " %%a in ("%VERSION%") do (
    set MAJ=%%a
)
for /f "tokens=2 delims=. " %%a in ("%VERSION%") do (
    set MIN=%%a
)
::echo %MAJ%
::echo %MIN%

rem Check for 64 Bit
	set 64BIT=0
	for /f "tokens=* delims=.- " %%a in ('cl.exe 2^>^&1 ^| %WINDIR%\system32\find.exe "x64"') do (
	set 64BIT=1
	)

rem  0. MSV19_24_X86 - Visual Studio 2019 (v16.x, v19.24)- 32bit 
rem  0: Microsoft (R) C/C++ Optimizing Compiler Version 19.24.28314 for x86

rem  0. MSV19_24_X64 - Visual Studio 2019 (v16.x, v19.24)- 64bit
rem  0: Microsoft (R) C/C++ Optimizing Compiler Version 19.24.28314 for x64

IF %MAJ% EQU 19 (
IF %MIN% GEQ 20 (
	set COMPILER=VC2019
	goto OK_OK
	)
	)

rem  1. MSV19_10_X86 - Visual Studio 2017 (v15.x, v19.10)- 32bit 
rem  1: Microsoft (R) C/C++ Optimizing Compiler Version 19.11.25508.2 for x86

rem  2. MSV19_10_X64 - Visual Studio 2017 (v15.x, v19.10)- 64bit
rem  2: Microsoft (R) C/C++ Optimizing Compiler Version 19.11.25508.2 for x64

IF %MAJ% EQU 19 (
IF %MIN% GEQ 10 (
	set COMPILER=VC2017
	goto OK_OK
	)
	)

rem  3. MSV19_00_X86 - Visual Studio 2015 (v14.x, v19.00)- 32bit
rem  3: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.23026 for x86

rem  4. MSV19_00_X64 - Visual Studio 2015 (v14.x, v19.00)- 64bit
rem  4: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.23026 for x64

IF %MAJ% EQU 19 (
IF %MIN% LSS 10 (
	set COMPILER=VC2015
	goto OK_OK
	)
	)

rem  5. MSV18_00_X86 - Visual Studio 2013 (v12.x, v18.x) - 32bit
rem  5: Microsoft (R) C/C++ Optimizing Compiler Version 18.00.40629 for x86

rem  6. MSV18_00_X64 - Visual Studio 2013 (v12.x, v18.x) - 64bit
rem  6: Microsoft (R) C/C++ Optimizing Compiler Version 18.00.40629 for x64

	for /f "tokens=* delims=.- " %%a in ('cl.exe 2^>^&1 ^| %WINDIR%\system32\find.exe "18.00"') do (
	set COMPILER=VC2013
	echo c-treeACE SDK 11.8 drops the support for Visual Studio 2013 and older
	echo Please contact FairCom if you need support for Visual Studio 2013 and older
	exit /B 1
	)


rem  7. MSV17_00_X86 - Visual Studio 2012 (v11.x, v17.x) - 32bit
rem  7: Microsoft (R) C/C++ Optimizing Compiler Version 17.00.61030 for x86

rem  8. MSV17_00_X64 - Visual Studio 2012 (v11.x, v17.x) - 64bit
rem  8: Microsoft (R) C/C++ Optimizing Compiler Version 17.00.61030 for x64

	for /f "tokens=* delims=.- " %%a in ('cl.exe 2^>^&1 ^| %WINDIR%\system32\find.exe "17.00"') do (
	set COMPILER=VC2012
	echo c-treeACE SDK 11.8 drops the support for Visual Studio 2013 and older
	echo Please contact FairCom if you need support for Visual Studio 2013 and older
	exit /B 1
	)

rem  9. MSV16_00_X86 - Visual Studio 2010 (v10.x, v16.x) - 32bit
rem  9: Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 16.00.40219.01 for 80x86

rem 10. MSV16_00_X64 - Visual Studio 2010 (v10.x, v16.x) - 64bit
rem 10: Microsoft (R) C/C++ Optimizing Compiler Version 16.00.40219.01 for x64

	for /f "tokens=* delims=.- " %%a in ('cl.exe 2^>^&1 ^| %WINDIR%\system32\find.exe "16.00"') do (
	set COMPILER=VC2010
	echo c-treeACE SDK 11.8 drops the support for Visual Studio 2013 and older
	echo Please contact FairCom if you need support for Visual Studio 2013 and older
	exit /B 1
	)

rem 11. MSV15_00_X86 - Visual Studio 2008 (v9.x,  v15.x) - 32bit
rem 11: Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 15.00.30729.01 for 80x86

rem 12. MSV15_00_X64 - Visual Studio 2008 (v9.x,  v15.x) - 64bit
rem 12: Microsoft (R) C/C++ Optimizing Compiler Version 15.00.30729.01 for x64

	for /f "tokens=* delims=.- " %%a in ('cl.exe 2^>^&1 ^| %WINDIR%\system32\find.exe "15.00"') do (
	set COMPILER=VC2008
	echo c-treeACE SDK 11.8 drops the support for Visual Studio 2013 and older
	echo Please contact FairCom if you need support for Visual Studio 2013 and older
	exit /B 1
	)

rem 13. MSV14_00_X86 - Visual Studio 2005 (v8.x,  v14.x) - 32bit
rem 13: Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 14.00.50727.762 for 80x86

rem 14. MSV14_00_X64 - Visual Studio 2005 (v8.x,  v14.x) - 64bit
rem 14: Microsoft (R) C/C++ Optimizing Compiler Version 14.00.50727.762 for x64

	for /f "tokens=* delims=.- " %%a in ('cl.exe 2^>^&1 ^| %WINDIR%\system32\find.exe "14.00"') do (
	set COMPILER=VC2005
	echo c-treeACE SDK 11.8 drops the support for Visual Studio 2013 and older
	echo Please contact FairCom if you need support for Visual Studio 2013 and older
	exit /B 1
	)

rem 15. MSV12_00_X86 - Visual Studio 6    (v6.x,  v12.x) - 32bit
rem 15: Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 12.00.8168 for 80x86

	for /f "tokens=* delims=.- " %%a in ('cl.exe 2^>^&1 ^| %WINDIR%\system32\find.exe "12.00"') do (
	set COMPILER=VC6
	echo c-treeACE SDK 11.8 drops the support for Visual Studio 2013 and older
	echo Please contact FairCom if you need support for Visual Studio 2013 and older
	exit /B 1
	)

exit /b 1

:OK_OK

exit /b 0

rem EOF



