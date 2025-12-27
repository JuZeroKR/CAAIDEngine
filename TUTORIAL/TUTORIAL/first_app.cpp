#include "first_app.hpp"

#include "keyboard_movement_controller.hpp"
#include "ULve_camera.hpp"
#include "simple_render_system.hpp"

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <stdexcept>
#include <chrono>
#include <array>
#include <glm/gtc/constants.hpp>

#define MAX_FRAME_TIME 100.0f

namespace lve {
    FirstApp::FirstApp() {
        loadGameObjects();
    }

    FirstApp::~FirstApp() {
    }

    void FirstApp::run() {
        SimpleRenderSystem simpleRenderSystem(lveDevice, lveRenderer.getSwapChainRenderPass());
        ULveCamera camera;
        
        auto viewerObject = LveGameObject::createGameObject();
        KeyboardMovementController cameraController{};
        
        auto currentTime = std::chrono::high_resolution_clock::now();

        while (!lveWindow.shouldClose()) {
            glfwPollEvents();

            auto newTime = std::chrono::high_resolution_clock::now();
            float frameTime = 
                std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
            currentTime = newTime;

            frameTime = glm::min(frameTime, MAX_FRAME_TIME);

            cameraController.moveInPlaneXZ(lveWindow.getGLFWWindow(), frameTime, viewerObject);
            camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);

            float aspect = lveRenderer.getAspectRatio();
            camera.setPerspectiveProjection(glm::radians(50.f), aspect, 0.1f, 10.f);
            

            if(auto commandBuffer = lveRenderer.beginFrame()) {
                lveRenderer.beginSwapChainRenderPass(commandBuffer);
                simpleRenderSystem.renderGameObjects(commandBuffer, gameObjects, camera);
                lveRenderer.endSwapChainRenderPass(commandBuffer);
                lveRenderer.endFrame();
            }
        }

        vkDeviceWaitIdle(lveDevice.device());
    }

    void FirstApp::loadGameObjects() {
        std::shared_ptr<LveModel> model = LveModel::createModelFromFile(lveDevice, "../models/smooth_vase.obj");
        auto gameObj = LveGameObject::createGameObject();
        gameObj.model = model;
        gameObj.color = {.1f, .8f, .1f};
        gameObj.transform.translation = { 0.f, 0.f, 2.5f };
        gameObj.transform.scale = glm::vec3(3.f);
        gameObjects.push_back(std::move(gameObj));
    }

    void FirstApp::sierpinski(
        std::vector<LveModel::Vertex> &vertices,
        int depth,
        glm::vec2 left,
        glm::vec2 right,
        glm::vec2 top) {
        if (depth <= 0) {
            vertices.push_back({{top.x, top.y, 0.f}, {1.f, 0.f, 0.f}});
            vertices.push_back({{right.x, right.y, 0.f}, {1.f, 0.f, 0.f}});
            vertices.push_back({{left.x, left.y, 0.f}, {1.f, 0.f, 0.f}});
        } else {

            auto leftTop = 0.5f * (left + top);
            auto rightTop = 0.5f * (right + top);
            auto leftRight = 0.5f * (left + right);
            sierpinski(vertices, depth - 1, left, leftRight, leftTop);
            sierpinski(vertices, depth - 1, leftRight, right, rightTop);
            sierpinski(vertices, depth - 1, leftTop, rightTop, top);
        }
    }
}