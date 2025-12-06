@echo off
echo Setting up Vulkan SDK environment...

:: Get the absolute path to the script directory
set "SCRIPT_DIR=%~dp0"

:: Define the relative path to the local Vulkan SDK
:: Note: Adjust the version number if it changes
set "LOCAL_VULKAN_PATH=TUTORIAL\TUTORIAL\VulkanSDK\1.4.309.0"
set "FULL_VULKAN_PATH=%SCRIPT_DIR%%LOCAL_VULKAN_PATH%"

if exist "%FULL_VULKAN_PATH%" (
    echo Found local Vulkan SDK at: %FULL_VULKAN_PATH%
    set "VULKAN_SDK=%FULL_VULKAN_PATH%"
    
    :: Add Bin to PATH
    set "PATH=%FULL_VULKAN_PATH%\Bin;%PATH%"
    
    echo.
    echo [SUCCESS] Environment variables configured.
    echo VULKAN_SDK = %VULKAN_SDK%
    echo.
    echo You can now run your build commands or executable from this terminal.
) else (
    echo [ERROR] Local Vulkan SDK not found at: %FULL_VULKAN_PATH%
    echo Please check if the folder exists.
)

cmd /k
