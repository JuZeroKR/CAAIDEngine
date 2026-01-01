#pragma once

#include "ULve_camera.hpp"
#include "ULve_gameobject.hpp"

//lib
#include <vulkan/vulkan.hpp>

namespace lve {
    struct FrameInfo {
        int frameIndex;
        float frameTime;
        VkCommandBuffer commandBuffer;
        ULveCamera &camera;
        VkDescriptorSet globalDescriptorSet;
        LveGameObject::Map &gameObjects;
    };
}