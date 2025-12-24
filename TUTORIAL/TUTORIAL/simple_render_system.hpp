#pragma once

#include "Ulve_camera.hpp"
#include "ULve_device.hpp"
#include "ULve_pipeline.hpp"
#include "ULve_gameobject.hpp"

#include <memory>
#include <vector>

namespace lve{
    class SimpleRenderSystem{
        public:
            SimpleRenderSystem(ULveDevice &device, VkRenderPass renderPass);
            ~SimpleRenderSystem();

            SimpleRenderSystem(const SimpleRenderSystem&) = delete;
            SimpleRenderSystem& operator=(const SimpleRenderSystem&) = delete;

            void renderGameObjects(
                VkCommandBuffer commandBuffer,
                std::vector<LveGameObject> &gameObjects,
                const ULveCamera&camera);

        private:
            void createPipelineLayout();
            void createPipeline(VkRenderPass renderPass);

            ULveDevice &lveDevice;
            std::unique_ptr<ULvePipeline> lvePipeline;
            VkPipelineLayout pipelineLayout;
    };
}