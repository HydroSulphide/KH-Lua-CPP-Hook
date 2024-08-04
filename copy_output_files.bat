@echo off
setlocal

:: Define the source and destination directories
set SOURCE_DIR_DBGHELP=out/build/x64-Debug
set SOURCE_DIR_MODS=out/mods

set KINGDOM_HEARTS_DIR=C:\Games\steamapps\common\KINGDOM HEARTS -HD 1.5+2.5 ReMIX-
set DEST_DIR_MODS=%KINGDOM_HEARTS_DIR%\mods
set DEST_DIR_SETUP_MOD=%KINGDOM_HEARTS_DIR%\KHMemoryHook

:: Create destination directories if they do not exist
if not exist "%DEST_DIR_MODS%" mkdir "%DEST_DIR_MODS%"
if not exist "%DEST_DIR_SETUP_MOD%" mkdir "%DEST_DIR_SETUP_MOD%"

:: Copy each DLL from source to destination
for %%f in ("%SOURCE_DIR_MODS%\*.dll") do (
    echo Processing file %%~nxf
    if /I "%%~nxf"=="kh_mod_setup.dll" (
        echo Copying %%~nxf to %DEST_DIR_SETUP_MOD%
        copy /Y "%%f" "%DEST_DIR_SETUP_MOD%"
    ) else (
        echo Copying %%~nxf to %DEST_DIR_MODS%
        copy /Y "%%f" "%DEST_DIR_MODS%"
    )
)

:: Additional copy of DBGHELP.dll
echo Copying DBGHELP.dll to %DEST_DIR_DBGHELP%
copy /Y "%SOURCE_DIR_DBGHELP%\DBGHELP.dll" "%KINGDOM_HEARTS_DIR%"

pause