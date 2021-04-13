setlocal
echo off
rem First we check your CMD Line Environment for Visual Studio
call CheckSetCompiler.bat
if errorlevel 1 (
   exit /B 1
)

rem Now we build the Tutorials
if "%myBLD%" == "NO" goto done

rem Compile the Tutorial Applications
csc -platform:x64 -debug -reference:..\..\..\ctree.drivers\bin\FairCom.CtreeDb.dll -keyfile:.\faircom.snk ..\Tutorial1.cs
csc -platform:x64 -debug -reference:..\..\..\ctree.drivers\bin\FairCom.CtreeDb.dll -keyfile:.\faircom.snk ..\Tutorial2.cs
csc -platform:x64 -debug -reference:..\..\..\ctree.drivers\bin\FairCom.CtreeDb.dll -keyfile:.\faircom.snk ..\Tutorial3.cs
csc -platform:x64 -debug -reference:..\..\..\ctree.drivers\bin\FairCom.CtreeDb.dll -keyfile:.\faircom.snk ..\Tutorial4.cs

rem Copy in required DLLs
copy ..\..\..\ctree.drivers\bin\FairCom.CtreeDb.dll
copy ..\..\..\ctree.drivers\lib\mtclient.dll

echo off
if "%myRUN%" == "NO" goto done
echo Now we will run Tutorial #1 - Be sure your server is running
pause

rem Run the Tutorial Applications
Tutorial1.exe
echo Now we will run Tutorial #2 
pause
Tutorial2.exe
echo Now we will run Tutorial #3 
pause
Tutorial3.exe
echo Now we will run Tutorial #4 
pause
Tutorial4.exe 
pause

:done
endlocal 
