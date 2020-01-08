@echo off

set DelDir=.\SavToXml\
rem for /f "delims=" %%i in (' dir /b /a-d %DelDir%*.xml 2^>NUL') do (
for /f "delims=" %%i in (' dir /b /a-d %DelDir%*.xml 2^>NUL') do (
  echo Removing %%i
  del %DelDir%%%i  
)

set DelDir=.\SavToXml\XmlToSav\
for /f "delims=" %%i in (' dir /b /a-d %DelDir%*.sav 2^>NUL') do (
  echo Removing %%i
  del %DelDir%%%i
)
