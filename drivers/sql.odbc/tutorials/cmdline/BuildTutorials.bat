setlocal
rem First we check your CMD Line Environment for Visual Studio
call CheckSetCompiler.bat
if errorlevel 1 (
   exit /B 1
)

rem Now we build the Tutorials
if "%myBLD%" == "NO" goto done
del *.pdb
cl -Zi -Od   ..\ODBCTutorial1.c -link odbc32.lib wsock32.lib advapi32.lib gdi32.lib user32.lib crypt32.lib
cl -Zi -Od    ..\ODBCTutorial2.c -link odbc32.lib wsock32.lib advapi32.lib gdi32.lib user32.lib crypt32.lib
cl -Zi -Od    ..\ODBCTutorial3.c -link odbc32.lib wsock32.lib advapi32.lib gdi32.lib user32.lib crypt32.lib
cl -Zi -Od    ..\ODBCTutorial4.c -link odbc32.lib wsock32.lib advapi32.lib gdi32.lib user32.lib crypt32.lib

if "%myRUN%" == "NO" goto done
echo Now we will run the Tutorial - be sure your Server is running.
pause

ODBCTutorial1.exe
echo Now we will run Tutorial #2
pause
ODBCTutorial2.exe
echo Now we will run Tutorial #3
pause
ODBCTutorial3.exe
echo Now we will run Tutorial #4
pause
ODBCTutorial4.exe
pause

:done
endlocal 