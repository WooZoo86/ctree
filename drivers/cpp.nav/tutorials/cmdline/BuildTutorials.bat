setlocal
call CheckSetCompiler.bat
if errorlevel 1 (
   exit /B 1
)
cl -Zi -EHsc -I ..\..\..\ctree.drivers\include ..\ctpp_tutorial1.cpp @msvclibs /link /ignore:4099,4204 
cl -Zi -EHsc -I ..\..\..\ctree.drivers\include ..\ctpp_tutorial2.cpp @msvclibs /link /ignore:4099,4204 
cl -Zi -EHsc -I ..\..\..\ctree.drivers\include ..\ctpp_tutorial3.cpp @msvclibs /link /ignore:4099,4204 
cl -Zi -EHsc -I ..\..\..\ctree.drivers\include ..\ctpp_tutorial4.cpp @msvclibs /link /ignore:4099,4204 
echo Now we will run the Tutorial - be sure your Server is running.
pause

ctpp_tutorial1.exe
echo Now we will run Tutorial #2
pause

ctpp_tutorial2.exe
echo Now we will run Tutorial #3
pause

ctpp_tutorial3.exe
echo Now we will run Tutorial #4
pause

ctpp_tutorial4.exe
pause

endlocal 
