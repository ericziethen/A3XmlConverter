@echo off

set BaseDir=.
set CompaeDir=.\SavToXml\XmlToSav

for /f "delims=" %%i in (' dir /b /a-d *.sav') do (
  FC %BaseDir%\%%i %CompaeDir%\%%i

)
