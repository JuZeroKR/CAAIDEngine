#pragma once

#include "ULve_device.hpp"

//lib
#include <vulkan/vulkan.hpp>

namespace lve {
    struct FrameInfo {
        int frameIndex;
        float frameTime;
        VkCommandBuffer commandBuffer;
        ULveCamera &camera;
        VkDescriptorSet globalDescriptorSet;
    };
}