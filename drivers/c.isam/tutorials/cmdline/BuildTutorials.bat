setlocal
call CheckSetCompiler.bat
if errorlevel 1 (
   exit /B 1
)
cl -Zi -I ..\..\..\ctree.drivers\include ..\isam_tutorial1.c @msvclibs /link /ignore:4099,4204 

echo Now we will run the Tutorial - be sure your Server is running.
pause

isam_tutorial1.exe
pause


endlocal 
