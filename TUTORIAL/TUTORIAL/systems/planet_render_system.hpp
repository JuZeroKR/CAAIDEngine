#pragma once

#include "ULve_camera.hpp"
#include "ULve_device.hpp"
#include "ULve_pipeline.hpp"
#include "ULve_frame_info.hpp"
#include "ULve_gameobject.hpp"

#include <memory>
#include <vector>

namespace lve{
    class PlanetRenderSystem{
        public:
            PlanetRenderSystem(ULveDevice &device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout, VkDescriptorSetLayout textureSetLayout);
            ~PlanetRenderSystem();

            PlanetRenderSystem(const PlanetRenderSystem&) = delete;
            PlanetRenderSystem& operator=(const PlanetRenderSystem&) = delete;

            void update(FrameInfo &frameInfo, GlobalUbo &ubo);
            void render(
                FrameInfo &frameInfo);

        private:
            void createPipelineLayout(VkDescriptorSetLayout globalSetLayout, VkDescriptorSetLayout textureSetLayout);
            void createPipeline(VkRenderPass renderPass);

            ULveDevice &lveDevice;
            std::unique_ptr<ULvePipeline> lvePipeline;
            VkPipelineLayout pipelineLayout;
    };
}