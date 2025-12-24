#include "ULveWindow.h"
#include "ULve_device.hpp"
#include "ULve_pipeline.hpp"
#include "ULve_swap_chain.hpp"
#include "ULve_gameobject.hpp"

#include <memory>
#include <vector>
#include <cassert>

namespace lve{
    class LveRenderer{
        public:

            LveRenderer(ULveWindow &window, ULveDevice &device);
            ~LveRenderer();

            LveRenderer(const LveRenderer&) = delete;
            LveRenderer& operator=(const LveRenderer&) = delete;

            bool isFrameInProgress() const { return isFrameStarted; }

            VkRenderPass getSwapChainRenderPass() const { return lveSwapChain->getRenderPass(); }
            float getAspectRatio() const { return lveSwapChain->extentAspectRatio(); }
            VkCommandBuffer getCurrentCommandBuffer() const { 
                assert(isFrameStarted && "Cannot get command buffer when frame is not in progress");
                return commandBuffers.at(currentFrameIndex); 
            }

            int getFrameIndex() const {
                assert(isFrameStarted && "Cannot get frame index when frame is not in progress");
                 return currentFrameIndex; 
            }

            VkCommandBuffer beginFrame();
            void endFrame();
            void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);
            void endSwapChainRenderPass(VkCommandBuffer commandBuffer);

        private:

            void createCommandBuffers();
            void freeCommandBuffers();
            void drawFrame();
            void recreateSwapChain();

            ULveWindow& lveWindow;
            ULveDevice& lveDevice;
            std::unique_ptr<ULveSwapChain> lveSwapChain;
            std::vector<VkCommandBuffer> commandBuffers;

            uint32_t currentImageIndex;
            int currentFrameIndex;
            bool isFrameStarted;
    };
}