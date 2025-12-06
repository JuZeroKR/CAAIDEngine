#include "VulkanCore.h"

#include <iostream>
using namespace std;

VulkanCore::VulkanCore()
{
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::cout << extensionCount << " extensions supported" << std::endl;
}

VulkanCore::~VulkanCore()
{
}

void VulkanCore::initVulkan()
{
}
