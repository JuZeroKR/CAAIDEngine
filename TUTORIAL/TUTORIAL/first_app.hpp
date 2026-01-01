#include "ULveWindow.h"
#include "ULve_device.hpp"
#include "ULve_swap_chain.hpp"
#include "ULve_gameobject.hpp"
#include "ULve_renderer.hpp"
#include "ULve_descriptors.hpp"

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
            void loadGameObjects();
            void sierpinski(std::vector<LveModel::Vertex> &vertices, int depth, glm::vec2 left, glm::vec2 right, glm::vec2 top);

            ULveWindow lveWindow{ WIDTH, HEIGHT, "Hello Vulkan!" };
            ULveDevice lveDevice{ lveWindow };
            LveRenderer lveRenderer{ lveWindow, lveDevice };
            LveGameObject::Map gameObjects;
            std::unique_ptr<LveDescriptorPool> globalPool{};
    };
}