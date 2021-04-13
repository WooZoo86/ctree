setlocal
rem First we check your CMD Line Environment for Visual Studio
call CheckSetCompiler.bat
IF errorlevel 1 (
    exit /B 1
)

rem Now we build the Tutorials
if "%myBLD%" == "YES" msbuild DSQL_Tutorials.sln /t:rebuild /p:Configuration=debug /p:Platform=x64 /m 

echo Now we run the DSQL_Tutorials - Be sure your server is running
pause
if "%myRUN%" == "NO" goto done
Debug\DSQL_Tutorial1.exe
echo Now we will run Tutorial #2
pause
Debug\DSQL_Tutorial2.exe
echo Now we will run Tutorial #3
pause
Debug\DSQL_Tutorial3.exe
echo Now we will run Tutorial #4
pause
Debug\DSQL_Tutorial4.exe
pause

:done
endlocal 
