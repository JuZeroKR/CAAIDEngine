@echo off
set "MAKE_PATH=C:\Program Files (x86)\GnuWin32\bin"
set "MINGW_PATH=C:\Users\tjwnd\AppData\Local\Microsoft\WinGet\Packages\BrechtSanders.WinLibs.MCF.UCRT_Microsoft.Winget.Source_8wekyb3d8bbwe\mingw64\bin"

set "PATH=%MAKE_PATH%;%MINGW_PATH%;%PATH%"

echo Environment updated.
echo Checking for g++...
g++ --version
echo Checking for make...
make --version

echo.
echo Running make...
make
if %errorlevel% neq 0 (
    echo Build failed.
    pause
    exit /b 1
)

echo Build successful!
pause
