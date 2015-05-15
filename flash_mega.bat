@echo off
break ON
rem fichiers BAT et fork créés par Sébastien CANET
SET currentpath=%~dp1
cd %currentpath%tools
cls
.\avrdude -Cavrdude.conf -v -patmega2560 -cwiring -P\\.\COM4 -b115200 -D -V -Uflash:w:johnny-five_firmata_mega.hex:i
pause