#pragma once

#include "ULve_camera.hpp"
#include "ULve_device.hpp"
#include "ULve_pipeline.hpp"
#include "ULve_frame_info.hpp"
#include "ULve_gameobject.hpp"

#include <memory>
#include <vector>

namespace lve{
    class SimpleRenderSystem{
        public:
            SimpleRenderSystem(ULveDevice &device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout);
            ~SimpleRenderSystem();

            SimpleRenderSystem(const SimpleRenderSystem&) = delete;
            SimpleRenderSystem& operator=(const SimpleRenderSystem&) = delete;

            void renderGameObjects(
                FrameInfo &frameInfo);

        private:
            void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);
            void createPipeline(VkRenderPass renderPass);

            ULveDevice &lveDevice;
            std::unique_ptr<ULvePipeline> lvePipeline;
            VkPipelineLayout pipelineLayout;
    };
}