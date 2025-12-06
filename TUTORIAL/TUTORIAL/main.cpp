#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

// VulkanCore
#include "VulkanCore.h"

int main()
{
    std::cout << "Hello from CAAIDEngine!" << std::endl;

    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "GLFW initialized successfully!" << std::endl;

    // Check Vulkan support
    if (glfwVulkanSupported()) {
        std::cout << "Vulkan is supported!" << std::endl;
    } else {
        std::cerr << "Vulkan is NOT supported!" << std::endl;
        return EXIT_FAILURE;
    }

    

    glfwTerminate();
    return EXIT_SUCCESS;
}
