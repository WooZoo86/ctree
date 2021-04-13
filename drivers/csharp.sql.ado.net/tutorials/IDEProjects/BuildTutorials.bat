setlocal
rem First we check your CMD Line Environment for Visual Studio
call CheckSetCompiler.bat
IF errorlevel 1 (
    exit /B 1
)

rem Now we build the Tutorials
if "%myBLD%" == "YES" msbuild CSharpTutorials.sln /t:rebuild /p:Configuration=debug /p:Platform=x64 /m 

if "%myRUN%" == "NO" goto done

copy ..\..\..\Ctree.Data.SqlClient.dll .\Tutorial1\bin\Debug
copy ..\..\..\Ctree.Data.SqlClient.dll .\Tutorial2\bin\Debug
copy ..\..\..\Ctree.Data.SqlClient.dll .\Tutorial3\bin\Debug
copy ..\..\..\Ctree.Data.SqlClient.dll .\Tutorial4\bin\Debug
echo Now we will run Tutorial #1 - Be sure your server is running

echo If you experience any errors when running these Tutorials you might want to
echo check your 'Global Assembly Cache' (GAC) to ensure it has the correct version
echo of the Ctree.Data.SqlClient.dll is being used.
echo .
echo List the GAC:   gacutil /l Ctree.Data.SqlClient
echo Unload the GAC: gacutil /u Ctree.Data.SqlClient
pause
.\Tutorial1\bin\Debug\CSharpTutorials1.exe
echo Now we will run Tutorial #2
pause
.\Tutorial2\bin\Debug\CSharpTutorials2.exe
echo Now we will run Tutorial #3
pause
.\Tutorial3\bin\Debug\CSharpTutorials3.exe
echo Now we will run Tutorial #4
pause
.\Tutorial4\bin\Debug\CSharpTutorials4.exe
pause

:done
endlocal 
