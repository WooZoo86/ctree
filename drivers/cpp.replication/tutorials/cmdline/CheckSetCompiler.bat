echo off
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

	echo "..\..\..\ctree.drivers\lib\fcRepl.lib" > msvclibs
	echo "..\..\..\ctree.drivers\lib\Microsoft Visual Studio 2015\mtclient.lib" >> msvclibs
	echo user32.lib   >> msvclibs
	echo gdi32.lib    >> msvclibs
	echo winspool.lib >> msvclibs
	echo comdlg32.lib >> msvclibs
	echo advapi32.lib >> msvclibs
	echo shell32.lib  >> msvclibs
	echo kernel32.lib >> msvclibs
	echo oldnames.lib >> msvclibs
	echo ws2_32.lib  >> msvclibs
	echo rpcrt4.lib   >> msvclibs
	echo crypt32.lib  >> msvclibs

exit /b 0

rem EOF
