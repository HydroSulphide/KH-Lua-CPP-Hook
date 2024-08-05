@echo off
setlocal

:: Check if directory argument is provided
if "%~1"=="" (
    echo No directory specified.
    exit /b 1
)

set "target_dir=%~1"

:: Check if the directory exists
if not exist "%target_dir%" (
    echo Directory "%target_dir%" does not exist.
    exit /b 1
)

:: Change to the target directory
cd /d "%target_dir%"

:: Add a delay to allow the system to release file handles
timeout /t 1 /nobreak >nul

:: Remove read-only attribute and delete all .dll files
for %%F in (*.dll) do (
    attrib -r "%%F" 2>nul
    del /q /f "%%F"
)

:: Print a message indicating the completion
echo Deleted all .dll files in "%target_dir%".

:: Uncomment to keep the console window open
::echo Press any key to exit...
::pause >nul

endlocal
exit /b 0
