@echo off
echo The java.jpa.nav tutorials depend on Java SE Version 8 ONLY.
echo *
echo Refer to ReadMe.htm for more information
echo *
echo Make sure your Java is set to Java 8 specifically.
echo We will now try to execute 'java -version' to display your current java version
echo * 
java -version
echo * 
pause

set GRADLE=gradlew.bat
echo Now we will build java.jpa.nav tutorials.
pause
call %GRADLE% build
echo Now we run the java.jpa.nav Tutorials - Be sure your server is running
pause
call %GRADLE% -q --console plain run
