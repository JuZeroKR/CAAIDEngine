#pragma once

#include "ULve_camera.hpp"
#include "ULve_device.hpp"
#include "ULve_pipeline.hpp"
#include "ULve_frame_info.hpp"
#include "ULve_gameobject.hpp"

#include <memory>
#include <vector>

namespace lve{
    class PointLightSystem{
        public:
            PointLightSystem(ULveDevice &device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout);
            ~PointLightSystem();

            PointLightSystem(const PointLightSystem&) = delete;
            PointLightSystem& operator=(const PointLightSystem&) = delete;

            void update(FrameInfo &frameInfo, GlobalUbo &ubo);
            void render(
                FrameInfo &frameInfo);

        private:
            void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);
            void createPipeline(VkRenderPass renderPass);

            ULveDevice &lveDevice;
            std::unique_ptr<ULvePipeline> lvePipeline;
            VkPipelineLayout pipelineLayout;
    };
}