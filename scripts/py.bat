@echo off
set "MPATH=%~dp0.."
xcopy "%MPATH%\launcher" "%MPATH%\bin\launcher\." /E /I /Y
