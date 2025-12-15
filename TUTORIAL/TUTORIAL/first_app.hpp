#include "ULveWindow.h"
#include "ULve_device.hpp"
#include "ULve_pipeline.hpp"
#include "ULve_swap_chain.hpp"
#include "ULve_model.hpp"

#include <memory>
#include <vector>

namespace lve{
    class FirstApp{
        public:
            static constexpr int WIDTH = 800;
            static constexpr int HEIGHT = 600;

            FirstApp();
            ~FirstApp();

            FirstApp(const FirstApp&) = delete;
            FirstApp& operator=(const FirstApp&) = delete;

            void run();

        private:
            void loadModel();
            void sierpinski(std::vector<LveModel::Vertex> &vertices, int depth, glm::vec2 left, glm::vec2 right, glm::vec2 top);
            void createPipelineLayout();
            void createPipeline();
            void createCommandBuffers();
            void drawFrame();

            ULveWindow lveWindow{ WIDTH, HEIGHT, "Hello Vulkan!" };
            ULveDevice lveDevice{ lveWindow };
            ULveSwapChain lveSwapChain{ lveDevice, lveWindow.getExtent() };
            std::unique_ptr<ULvePipeline> lvePipeline;
            VkPipelineLayout pipelineLayout;
            std::vector<VkCommandBuffer> commandBuffers;
            std::unique_ptr<LveModel> lveModel;
    };
}