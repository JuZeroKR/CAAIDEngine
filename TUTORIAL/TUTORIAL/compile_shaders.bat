@echo off
setlocal

:: Path to glslc.exe (relative to this script)
set BASE_DIR=%~dp0
set GLSLC="%BASE_DIR%VulkanSDK\1.4.309.0\Bin\glslc.exe"
set SHADER_DIR="%BASE_DIR%..\shaders"

if not exist %GLSLC% (
    echo Error: glslc.exe not found at %GLSLC%
    exit /b 1
)

echo Compiling shaders...

for %%f in (%SHADER_DIR%\*.vert) do (
    echo Compiling %%~nxf...
    %GLSLC% "%%f" -o "%%f.spv"
    if errorlevel 1 (
        echo Failed to compile %%~nxf
        exit /b 1
    )
)

for %%f in (%SHADER_DIR%\*.frag) do (
    echo Compiling %%~nxf...
    %GLSLC% "%%f" -o "%%f.spv"
    if errorlevel 1 (
        echo Failed to compile %%~nxf
        exit /b 1
    )
)

echo Shaders compiled successfully.
endlocal
