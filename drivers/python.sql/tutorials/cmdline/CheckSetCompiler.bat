echo off
python.exe --version >NUL 2>&1
if errorlevel 1 (
	echo python.exe not found! Please set environment for Python.
	exit /b 1
)

exit /b 0

rem EOF
