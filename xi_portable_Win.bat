@echo off
break ON
rem fichiers BAT et fork cr��s par S�bastien CANET
cls
SET currentpath=%~dp1
cd %currentpath%
start .\nodejs\node.exe xiserver.js ard null 0 COM3 1234