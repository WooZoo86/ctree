setlocal enabledelayedexpansion
set ERROR=0
where /Q node.exe 
if %ERRORLEVEL% NEQ 0 set ERROR=1
where /Q npm.cmd
if %ERRORLEVEL% NEQ 0 set ERROR=1
if %ERROR% EQU 0 (
call npm.cmd init -y
call npm.cmd --prefix . install ..\..
copy /Y ..\createIndex.js
copy /Y ..\createRecord.js
copy /Y ..\createTable.js
copy /Y ..\deleteTable.js
copy /Y ..\query.js
node.exe createTable.js
node.exe createRecord.js
node.exe createIndex.js
node.exe query.js
node.exe deleteTable.js
exit /B 0
) else (
@echo "No nodejs found in path consider install nodejs"
exit /B 1
)
