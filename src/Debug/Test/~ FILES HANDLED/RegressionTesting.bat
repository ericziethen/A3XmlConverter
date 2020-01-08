set BinDir=..\..\
set DiffBinDir=..\

set startTime=%time%

rem Clear the Files
call %DiffBinDir%"ClearTestFiles.bat"

rem Import All Files
set importStartTime=%time%
%BinDir%"A3XmlConverter.exe" import
set importEndTime=%time%

rem Export Files
set exportStartTime=%time%
%BinDir%"A3XmlConverter.exe" export
set exportEndTime=%time%

rem Do Diff Comparison
call %DiffBinDir%"DiffSavFiles"

set endTime=%time%

echo ===============================
echo Start  Time:        %startTime%
echo Import Start  Time:     %importStartTime%
echo Import Finish Time:     %importEndTime%
echo Export Start  Time:     %exportStartTime%
echo Export Finish Time:     %exportEndTime%
echo Finish Time:        %endTime%
