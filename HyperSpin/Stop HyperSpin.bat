TITLE Stop HyperSpin

REM
REM Setup log file
REM
set log=E:\GitHub\Arcade\HyperSpin\HyperSpin.Stop.log
echo ----- %date% %time% ----- >>%log%

REM
REM Make sure we are on the game drive
REM 
E:
cd \GitHub\Arcade\QBW MAME Magic LED\C#\QBW_Magic_LED\bin\Release

REM
REM Kill everything we started
REM
taskkill /T /F /FI "IMAGENAME eq wmplayer*"
taskkill /T /F /FI "IMAGENAME eq QBW.magic.led*"

REM
REM Turn off all LEDs and exit QBW Magic LED
REM
START /wait QBW.magic.led.exe :led=systemExit.txt :system=HyperSpin
echo Error:%errorlevel% >>%log%

REM
REM Cleanup before we exit
REM
taskkill /T /F /FI "IMAGENAME eq wmplayer*"
taskkill /T /F /FI "IMAGENAME eq QBW.magic.led*"
rem taskkill /T /F /FI "IMAGENAME eq HyperSpin*"

echo Done: %date% %time% >>%log%