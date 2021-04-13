setlocal
rem First we check your CMD Line Environment for Visual Studio
call CheckSetCompiler.bat
IF errorlevel 1 (
    exit /B 1
)

rem Now we build the Tutorials
if "%myBLD%" == "YES" msbuild ODBCTutorials.sln /t:rebuild /p:Configuration=debug /p:Platform=x64 /m 

if "%myRUN%" == "NO" goto done
echo Now we will run the Tutorial - be sure your Server is running.
pause

Debug\ODBCTutorial1.exe
echo Now we will run Tutorial #2
pause
Debug\ODBCTutorial2.exe
echo Now we will run Tutorial #3
pause
Debug\ODBCTutorial3.exe
echo Now we will run Tutorial #4
pause
Debug\ODBCTutorial4.exe
pause

:done
endlocal 
