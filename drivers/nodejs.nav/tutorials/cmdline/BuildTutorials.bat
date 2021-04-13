@echo off
setlocal enabledelayedexpansion
echo The nodejs.nav tutorial requires NodeJS Version 10 or newer build and run properly:
echo * 
echo Refer to ReadMe.htm for more information
echo * 
echo We will now try to execute 'node -v' to display your current nodejs version
echo * 

node -v
echo * 
pause

set ERROR=0
where /Q node.exe 
if %ERRORLEVEL% NEQ 0 set ERROR=1
where /Q npm.cmd
if %ERRORLEVEL% NEQ 0 set ERROR=1
if %ERROR% EQU 0 (
call npm.cmd init -y
call npm.cmd --prefix . install ..\..
copy /Y ..\*.js
copy /Y ..\..\..\ctree.drivers\lib\mtclient.dll

node.exe ctdb_tutorial1.js
exit /B 0
) else (
@echo No nodejs found in path consider install nodejs
exit /B 1
)