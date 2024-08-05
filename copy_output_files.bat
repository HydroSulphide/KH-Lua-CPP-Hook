@echo off
setlocal

:: Define the source and destination directories
set SOURCE_DIR_DBGHELP=out/build/x64-Debug
set SOURCE_DIR_MODS=out/mods

set KINGDOM_HEARTS_DIR=C:\Games\steamapps\common\KINGDOM HEARTS -HD 1.5+2.5 ReMIX-
set DEST_DIR_MODS=%KINGDOM_HEARTS_DIR%\mods
set DEST_DIR_SETUP=%KINGDOM_HEARTS_DIR%\KHMemoryHook
set DEST_DIR_DBGHELP=%KINGDOM_HEARTS_DIR%

:: Create destination directories if they do not exist
if not exist "%DEST_DIR_MODS%" mkdir "%DEST_DIR_MODS%"
if not exist "%DEST_DIR_SETUP%" mkdir "%DEST_DIR_SETUP%"

:: Copy each DLL from source to destination
for %%f in ("%SOURCE_DIR_MODS%\*.dll") do (
    echo Processing file %%~nxf
    if /I "%%~nxf"=="kh_mod_setup.dll" (
        echo Copying %%~nxf to %DEST_DIR_SETUP%
        copy /Y "%%f" "%DEST_DIR_SETUP%"
    ) else (
        echo Copying %%~nxf to %DEST_DIR_MODS%
        copy /Y "%%f" "%DEST_DIR_MODS%"
    )
)

:: Additional copy of remove_loaded_mods.bat
echo Copying remove_loaded_mods.bat to %DEST_DIR_SETUP%
copy /Y "remove_loaded_mods.bat" "%DEST_DIR_SETUP%"

:: Additional copy of DBGHELP.dll
echo Copying DBGHELP.dll to %DEST_DIR_DBGHELP%
copy /Y "%SOURCE_DIR_DBGHELP%\DBGHELP.dll" "%DEST_DIR_DBGHELP%"

pause
