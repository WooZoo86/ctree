echo off
javac.exe -version >NUL 2>&1
if errorlevel 1 (
	echo JDK not found! Please set environment for the Java JDK.
	exit /b 1
)

javac.exe -version >NUL 2>&1
if errorlevel 1 (
	echo javac.exe not found! Please set environment for the Java JDK.
	exit /b 1
)

rem Check for 64 Bit
	set _64BIT=0
	for /f "tokens=* delims=.- " %%a in ('java.exe -version 2^>^&1 ^| %WINDIR%\system32\find.exe "64-Bit"') do (
	set _64BIT=1
	echo 64bit Java 
	)
	if "%_64BIT%" == "0" echo 32bit Java  

exit /b 0

rem EOF
