@echo off
set GRADLE=gradlew.bat
set GRADLEQ=%GRADLE%% -q --console plain
echo This demo is intended to show how is it possible to interact with c-treeACE Replication Manager 
echo by sending simple HTTP calls through a Java program.
echo In order to make sure that this sample will work properly please prepare the environment as described
echo in this API read me file.
echo.
echo We will now build the java program...
pause
call %GRADLE% build
if %ERRORLEVEL% NEQ 0 (
goto EOF
)
echo In order to see how this program interacts we suggest you to open your browser and visit:
echo http://localhost:8080/ReplicationManager
pause
echo We will now setup a replication plan between the two servers
pause
call %GRADLE% run --args=setup
call %GRADLEQ% run --args=status
echo We will now stop the replication plan
pause
call %GRADLE% run --args=stop
call %GRADLEQ% run --args=status
echo We will now restart the replication plan
pause
call %GRADLE% run --args=start
call %GRADLEQ% run --args=status
:EOF