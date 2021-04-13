setlocal
call CheckSetCompiler.bat
if errorlevel 1 (
   exit /B 1
)
cl -Zi -I ..\..\..\ctree.drivers\include ..\ctdb_tutorial1.c @msvclibs /link /ignore:4099,4204 
cl -Zi -I ..\..\..\ctree.drivers\include ..\ctdb_tutorial2.c @msvclibs /link /ignore:4099,4204 
cl -Zi -I ..\..\..\ctree.drivers\include ..\ctdb_tutorial3.c @msvclibs /link /ignore:4099,4204 
cl -Zi -I ..\..\..\ctree.drivers\include ..\ctdb_tutorial4.c @msvclibs /link /ignore:4099,4204 
echo Now we will run the Tutorial - be sure your Server is running.
pause

ctdb_tutorial1.exe
echo Now we will run Tutorial #2
pause

ctdb_tutorial2.exe
echo Now we will run Tutorial #3
pause

ctdb_tutorial3.exe
echo Now we will run Tutorial #4
pause

ctdb_tutorial4.exe
pause


endlocal 
