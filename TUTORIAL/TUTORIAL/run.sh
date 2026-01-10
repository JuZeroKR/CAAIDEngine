#!/bin/bash
# Set the path to Vulkan Validation Layers (installed via Homebrew)
export VK_LAYER_PATH=/opt/homebrew/opt/vulkan-validationlayers/share/vulkan/explicit_layer.d

# Ensure the dynamic linker can find libvulkan.dylib and validation layers
export DYLD_LIBRARY_PATH=/opt/homebrew/lib:/opt/homebrew/opt/vulkan-loader/lib:/opt/homebrew/opt/vulkan-validationlayers/lib:$DYLD_LIBRARY_PATH

# Set path to MoltenVK ICD (Driver)
export VK_ICD_FILENAMES=/opt/homebrew/etc/vulkan/icd.d/MoltenVK_icd.json

# Run the application
./TutorialApp
