setlocal
rem First we check your CMD Line Environment for Visual Studio
call CheckSetCompiler.bat
IF errorlevel 1 (
    exit /B 1
)

rem Now we build the Tutorials
if "%myBLD%" == "YES" msbuild Tutorials.sln /t:rebuild /p:Configuration=debug /p:Platform=x64 /m 

echo Now we will run the Tutorial - be sure your Server is running.
pause

Debug\Tutorial1.exe
echo Now we will run Tutorial #2
pause
Debug\Tutorial2.exe
echo Now we will run Tutorial #3
pause
Debug\Tutorial3.exe
echo Now we will run Tutorial #4
pause
Debug\Tutorial4.exe
pause

endlocal 
