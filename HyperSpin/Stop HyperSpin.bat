TITLE Stop HyperSpin
REM
REM Kill everything we started
REM

set log=E:\GitHub\Arcade\HyperSpin\HyperSpin.Stop.log

REM
REM Make sure we are on the game drive
REM 
E:
cd \GitHub\Arcade\QBW MAME Magic LED\C#\QBW_Magic_LED\bin\Release

echo ----- %date% %time% ----- >>%log%

taskkill /T /F /FI "IMAGENAME eq wmplayer*"
taskkill /T /F /FI "IMAGENAME eq QBW.magic.led*"

start QBW.magic.led.exe :led=clearall.txt :system=HyperSpin

REM Take a break for LED to clear (10 seconds)
REM START /wait /b ping -N 10 192.168.1.1
ping 127.0.0.1 -n 10 > nul

echo Error:%errorlevel% >>%log%

REM
REM Cleanup before we exit
REM
taskkill /T /F /FI "IMAGENAME eq wmplayer*"
taskkill /T /F /FI "IMAGENAME eq QBW.magic.led*"
rem taskkill /T /F /FI "IMAGENAME eq HyperSpin*"

echo Done: %date% %time% >>%log%
