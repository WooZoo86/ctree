setlocal
rem First we check your CMD Line Environment for Visual Studio
call CheckSetCompiler.bat
if errorlevel 1 (
   exit /B 1
)
if "%myBLD%" == "NO" goto done

csc -reference:..\..\Ctree.Data.SqlClient.dll -debug ..\CSharpTutorial1.cs
csc -reference:..\..\Ctree.Data.SqlClient.dll -debug ..\CSharpTutorial2.cs
csc -reference:..\..\Ctree.Data.SqlClient.dll -debug ..\CSharpTutorial3.cs
csc -reference:..\..\Ctree.Data.SqlClient.dll -debug ..\CSharpTutorial4.cs

if "%myRUN%" == "NO" goto done
echo Now we will run Tutorial #1 - Be sure your server is running
pause

copy ..\..\Ctree.Data.SqlClient.dll

CSharpTutorial1.exe
echo Now we will run Tutorial #2
pause
CSharpTutorial2.exe
echo Now we will run Tutorial #3
pause
CSharpTutorial3.exe
echo Now we will run Tutorial #4
pause
CSharpTutorial4.exe
pause

:done
endlocal 
