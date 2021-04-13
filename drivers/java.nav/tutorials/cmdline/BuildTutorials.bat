setlocal
call CheckSetCompiler.bat
if errorlevel 1 (
   exit /B 1
)
echo on
javac -d . -cp ..\..\ctreeJTDB.jar ..\JTDB_Tutorial1.java
javac -d . -cp ..\..\ctreeJTDB.jar ..\JTDB_Tutorial2.java
javac -d . -cp ..\..\ctreeJTDB.jar ..\JTDB_Tutorial3.java
javac -d . -cp ..\..\ctreeJTDB.jar ..\JTDB_Tutorial4.java


java -cp .;..\..\ctreeJTDB.jar -Djava.library.path=..\..\ JTDB_Tutorial1
java -cp .;..\..\ctreeJTDB.jar -Djava.library.path=..\..\ JTDB_Tutorial2
java -cp .;..\..\ctreeJTDB.jar -Djava.library.path=..\..\ JTDB_Tutorial3
java -cp .;..\..\ctreeJTDB.jar -Djava.library.path=..\..\ JTDB_Tutorial4

endlocal 
