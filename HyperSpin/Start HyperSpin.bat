TITLE Start HyperSpin
REM
REM Kill anything that we need to start.
REM
taskkill /T /F /FI "IMAGENAME eq HyperSpin*"
taskkill /T /F /FI "IMAGENAME eq wmplayer*"
taskkill /T /F /FI "IMAGENAME eq QBW.magic.led*"

REM Move to our Game Drive
E:

REM Play the old school sound
\GitHub\Arcade\Ambience\Arcade\arcade.mp3

REM Start HyperSpin
cd \HyperSpin\1.3.2.0\
HyperSpin.exe
