@echo off
setlocal
set LIBDIR=..\..\ctree.drivers\lib
call CheckSetCompiler.bat
if errorlevel 1 (
goto:EOF
)
@echo on
pushd ..
copy /Y ..\pyctree.py
copy /Y ..\pyctsqlapi.py
copy /Y %LIBDIR%\ctsqlapi.dll
popd
@echo off
echo Now we will run the Tutorial - be sure your Server is running.
pause
@echo on
pushd ..
python.exe PY_Tutorial2.py
python.exe PY_Tutorial4.py
popd
endlocal

