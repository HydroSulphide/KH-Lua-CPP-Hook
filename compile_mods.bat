@echo off
setlocal enabledelayedexpansion

:: Directories
set LIB_DIR=out/build/x64-Debug
set INCLUDE_DIR=include/cpp/api
set SRC_DIR=src/cpp/mods
set OUTPUT_DIR=out/mods

:: Create output directory if it doesn't exist
if not exist "%OUTPUT_DIR%" mkdir "%OUTPUT_DIR%"

:: Set up MSVC environment variables
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"

:: Compile each .cpp file in the src directory
for %%f in (%SRC_DIR%\*.cpp) do (
    :: Get the base name of the file (without path and extension)
    set base_name=%%~nf
    
    :: Set the output DLL name
    set dll_name=%OUTPUT_DIR%\!base_name!.dll
    
    cl /LD /I"%INCLUDE_DIR%" /D_CRT_SECURE_NO_WARNINGS /std:c++latest "%%f" /link /OUT:"!dll_name!" /LIBPATH:"%LIB_DIR%" DBGHELP.lib


    :: Check if compilation was successful
    if errorlevel 1 (
        echo Failed to compile %%f
    ) else (
        echo Successfully compiled %%f into !dll_name!
    )
)

pause
