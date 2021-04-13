@echo off
setlocal
call CheckSetCompiler.bat
if errorlevel 1 (
goto:EOF
)
@echo on
pushd ..
set LIBDIR=..\..\ctree.drivers\lib
copy /Y %LIBDIR%\ctsqlapi.dll
popd
@echo off
echo If you seem to have trouble with this tutorial, the most likely cause is
echo that you do not have correctly installed SQLAlchemy in your python installation.
echo Make sure you follwed the readme for this API to know how to install SQLAlchemy.
pause
echo Now we will run the Tutorial - be sure your Server is running.
pause
@echo on
pushd ..
python.exe usage.py
popd
:EOF
endlocal