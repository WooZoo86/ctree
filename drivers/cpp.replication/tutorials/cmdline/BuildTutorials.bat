setlocal
call CheckSetCompiler.bat
if errorlevel 1 (
   exit /B 1
)

cl -Zi -D_WINDOWS -I ..\..\..\ctree.drivers\include\repl -I ..\..\..\ctree.drivers\include ..\apiTestCPP.cpp @msvclibs /link /ignore:4099,4204 

echo Now we will run the Tutorial - be sure your Server is running.
pause

copy ..\..\..\ctree.drivers\bin\ctsqlapi.dll
copy ..\..\..\ctree.drivers\bin\fcRepl.dll
copy ..\..\..\ctree.drivers\bin\mtclient.dll
copy ..\..\..\ctree.drivers\bin\RCESBasic.dll
copy ..\..\..\ctree.drivers\bin\RCESDPCtree.dll
copy ..\..\..\ctree.drivers\bin\HazelcastClient3.12-SNAPSHOT_64.dll
apiTestCPP.exe
pause

endlocal 
