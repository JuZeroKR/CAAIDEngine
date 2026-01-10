#pragma once

#include "ULve_device.hpp"

#include <string>

namespace lve {
    class ULveTexture {
    public:
        ULveTexture(ULveDevice& device, const std::string& imageFilepath);
        ~ULveTexture();
        
        ULveTexture(const ULveTexture &other) = delete;
        ULveTexture &operator=(const ULveTexture &other) = delete;

        VkDescriptorImageInfo getImageInfo() const;

    private:
        ULveDevice& lveDevice;
        VkImage image;
        VkDeviceMemory imageMemory;
        VkImageView imageView;
        VkSampler sampler;

        void transitionImageLayout(VkImageLayout oldLayout, VkImageLayout newLayout);
    };
}