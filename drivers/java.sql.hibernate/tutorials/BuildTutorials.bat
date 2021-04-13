@echo off
setlocal enabledelayedexpansion
echo The java.sql.hibernate tutorial requires Java SE Version 8 or later to build and run properly:
echo * 
echo Refer to ReadMe.htm for more information
echo * 
echo We will now try to execute 'java -version' to display your current java version
echo * 
java -version
echo * 
pause

@echo off
set GRADLE=gradlew.bat
set ISQL=..\..\ctree.drivers\bin\isql.exe
set SCRIPT=tutorial.sql
set USR=ADMIN
set PWD=ADMIN
set DBS=6597@localhost:ctreeSQL
echo First we will create sample data using Interactive sql
pause
%ISQL% -s%SCRIPT% -u %USR% -a %PWD% %DBS%
echo Now we will build java.sql.hibernate tutorials.
pause
call %GRADLE% build
echo Now we run the java.sql.hibernate Tutorials - Be sure your server is running
pause
call %GRADLE% -q --console plain run
