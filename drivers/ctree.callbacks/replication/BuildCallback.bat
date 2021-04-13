setlocal
pushd bin
call ..\CheckSetCompiler.bat

set MY_INCLUDES=-I ..\..\..\ctree.drivers\include
cl  %FJ_CFLAGS%  %MY_INCLUDES% ..\src\ctrepluser.c 
rc -r -i ..\..\..\ctree.drivers\include -fo ctrepluser.res ..\src\ctrepluser.rc
link  ctrepluser.obj ctrepluser.res -subsystem:console @msvclibs 
pause

dir 
popd

endlocal 

