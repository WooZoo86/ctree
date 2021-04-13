set ISQL=..\..\..\ctree.drivers\bin\isql.exe
@echo off
echo Now we run the Interactive SQL Tutorials - Be sure your server is running
pause
@echo on
%ISQL% -s ..\isql_tutorial1.sql -u ADMIN -a ADMIN ctreeSQL
echo Now we will run Tutorial #2
@echo off
pause
@echo on
%ISQL% -s ..\isql_tutorial2.sql -u ADMIN -a ADMIN ctreeSQL
echo Now we will run Tutorial #3
@echo off
pause
@echo on
%ISQL% -s ..\isql_tutorial3.sql -u ADMIN -a ADMIN ctreeSQL
echo Now we will run Tutorial #4
@echo off
pause
@echo on
%ISQL% -s ..\isql_tutorial4.sql -u ADMIN -a ADMIN ctreeSQL
@echo off
pause
@echo on
