@echo off
setlocal
call CheckSetCompiler.bat
if errorlevel 1 (
   exit /B 1
)
if errorlevel 1 (
goto:EOF
)
@echo on
javac ..\JDBC_Tutorial1.java
javac ..\JDBC_Tutorial2.java
javac ..\JDBC_Tutorial3.java
javac ..\JDBC_Tutorial4.java

@echo off
echo Now we will run the Tutorial - be sure your Server is running.
pause
@echo on

java -cp ..;..\..\ctreeJDBC.jar JDBC_Tutorial1
echo Now we will run Tutorial #2
pause
java -cp ..;..\..\ctreeJDBC.jar JDBC_Tutorial2
echo Now we will run Tutorial #3
pause
java -cp ..;..\..\ctreeJDBC.jar JDBC_Tutorial3
echo Now we will run Tutorial #4
pause
java -cp ..;..\..\ctreeJDBC.jar JDBC_Tutorial4

