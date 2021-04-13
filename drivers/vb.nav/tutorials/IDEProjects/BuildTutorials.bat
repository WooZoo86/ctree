setlocal
rem First we check your CMD Line Environment for Visual Studio
call CheckSetCompiler.bat
IF errorlevel 1 (
    exit /B 1
)

rem Now we build the Tutorials
if "%myBLD%" == "YES" msbuild Tutorials.sln /t:rebuild /p:Configuration=debug /p:Platform=x64 /m 

if "%myRUN%" == "NO" goto done
echo Now we will run the Tutorial - be sure your Server is running.
pause

rem Copy in required DLLs
copy ..\..\..\..\ctree.drivers\bin\FairCom.CtreeDb.dll
copy ..\..\..\..\ctree.drivers\lib\mtclient.dll


.\Tutorial1\bin\Debug\Tutorial1.exe
echo Now we will run Tutorial #2
pause
.\Tutorial2\bin\Debug\Tutorial2.exe
echo Now we will run Tutorial #3
pause
.\Tutorial3\bin\Debug\Tutorial3.exe
echo Now we will run Tutorial #4
pause
.\Tutorial4\bin\Debug\Tutorial4.exe
pause

:done
endlocal 
