#!/bin/bash

# Get the absolute path to the script directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Define the relative path to the local Vulkan SDK
# Note: Adjust the version number if it changes
LOCAL_VULKAN_PATH="TUTORIAL/TUTORIAL/VulkanSDK/1.4.309.0"
FULL_VULKAN_PATH="$SCRIPT_DIR/$LOCAL_VULKAN_PATH"

if [ -d "$FULL_VULKAN_PATH" ]; then
    echo "Found local Vulkan SDK at: $FULL_VULKAN_PATH"
    export VULKAN_SDK="$FULL_VULKAN_PATH"
    
    # Add Bin to PATH (if needed, though mainly for tools)
    export PATH="$FULL_VULKAN_PATH/Bin:$PATH"
    
    # For macOS, we might need DYLD_LIBRARY_PATH or VK_ICD_FILENAMES
    export DYLD_LIBRARY_PATH="$FULL_VULKAN_PATH/Lib:$DYLD_LIBRARY_PATH"
    export VK_LAYER_PATH="$FULL_VULKAN_PATH/Bin"
    
    echo ""
    echo "[SUCCESS] Environment variables configured."
    echo "VULKAN_SDK = $VULKAN_SDK"
    echo ""
    echo "NOTE: This script must be sourced to affect the current shell:"
    echo "      source ./setup.sh"
else
    echo "[ERROR] Local Vulkan SDK not found at: $FULL_VULKAN_PATH"
fi
