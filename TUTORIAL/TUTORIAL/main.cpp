#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

// VulkanCore
#include "VulkanCore.h"
#include "ULveWindow.h"

int main()
{
    lve::ULveWindow window(800, 600, "Vulkan Window");

    while (!window.shouldClose()) {
        glfwPollEvents();
    }

    return EXIT_SUCCESS;
}
