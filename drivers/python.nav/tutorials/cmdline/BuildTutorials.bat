@echo off
setlocal
set LIBDIR=..\..\ctree.drivers\lib
call CheckSetCompiler.bat
if errorlevel 1 (
goto:EOF
)
@echo on
pushd ..
copy ..\*.py
copy %LIBDIR%\mtclient.dll
popd
@echo off
echo Now we will run the Tutorial - be sure your Server is running.
pause
@echo on
pushd ..
python.exe tutorial_1.py
popd
endlocal

