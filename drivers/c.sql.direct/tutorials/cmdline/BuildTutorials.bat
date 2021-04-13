setlocal
rem First we check your CMD Line Environment for Visual Studio
call CheckSetCompiler.bat
if errorlevel 1 (
   exit /B 1
)

if "%myBLD%" == "NO" goto done

cl -Zi -MD -I ..\..\..\ctree.drivers\include ..\DSQL_tutorial1.c @msvclibs /link /ignore:4099,4204 
cl -Zi -MD -I ..\..\..\ctree.drivers\include ..\DSQL_tutorial2.c @msvclibs /link /ignore:4099,4204 
cl -Zi -MD -I ..\..\..\ctree.drivers\include ..\DSQL_tutorial3.c @msvclibs /link /ignore:4099,4204 
cl -Zi -MD -I ..\..\..\ctree.drivers\include ..\DSQL_tutorial4.c @msvclibs /link /ignore:4099,4204 

echo Now we run the DSQL_Tutorials - Be sure your server is running
pause
if "%myRUN%" == "NO" goto done
DSQL_Tutorial1.exe
echo Now we will run Tutorial #2
pause
DSQL_Tutorial2.exe
echo Now we will run Tutorial #3
pause
DSQL_Tutorial3.exe
echo Now we will run Tutorial #4
pause
DSQL_Tutorial4.exe
pause

:done
endlocal 
