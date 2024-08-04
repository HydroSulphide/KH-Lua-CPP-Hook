@echo off
setlocal enabledelayedexpansion

:: Directories
set LIB_DIR=out/build/x64-Debug
set INCLUDE_DIR=include/cpp/api
set SRC_DIR=src/cpp/mods
set OUTPUT_DIR=out/mods

:: Create output directory if it doesn't exist
if not exist "%OUTPUT_DIR%" mkdir "%OUTPUT_DIR%"

:: Compile each .cpp file in the src directory
for %%f in (%SRC_DIR%\*.cpp) do (
    :: Get the base name of the file (without path and extension)
    set base_name=%%~nf
    
    :: Set the output DLL name
    set dll_name=%OUTPUT_DIR%\!base_name!.dll
    
    :: Compile the .cpp file into a DLL
    g++ -shared -o "!dll_name!" "%%f" -I"%INCLUDE_DIR%" -L"%LIB_DIR%" -lDBGHELP -std=c++20 -Wl,--kill-at
    
    :: Check if compilation was successful
    if errorlevel 1 (
        echo Failed to compile %%f
    ) else (
        echo Successfully compiled %%f into !dll_name!
    )
)

pause
