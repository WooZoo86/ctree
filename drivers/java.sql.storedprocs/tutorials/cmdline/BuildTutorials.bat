echo off
 
echo If you seem to have trouble with this tutorial, the most likely cause is
echo that you do not have your JVM set up properly in your server's config file (ctsrvr.cfg)
echo Check the start-up banner for your server. 
echo If you see the message "JVM Init Error: JVM_LIB environment variable not set."
echo you will need to modify your ctsrvr.cfg with the proper PATHS for your machine's JVM.
pause


set ISQL=..\..\..\ctree.drivers\bin\isql.exe
%ISQL% -s ..\SPTTutorial1.sql -u ADMIN -a ADMIN ctreeSQL
echo Now we will run Tutorial #2
@echo off
pause
@echo on
%ISQL% -s ..\SPTTutorial2.sql -u ADMIN -a ADMIN ctreeSQL
echo Now we will run Tutorial #3
@echo off
pause
@echo on
%ISQL% -s ..\SPTTutorial3.sql -u ADMIN -a ADMIN ctreeSQL
echo Now we will run Tutorial #4
@echo off
pause
@echo on
%ISQL% -s ..\SPTTutorial4.sql -u ADMIN -a ADMIN ctreeSQL
@echo off
pause
@echo on