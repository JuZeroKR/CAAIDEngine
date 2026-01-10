#include "first_app.hpp"

#include "keyboard_movement_controller.hpp"
#include "ULve_camera.hpp"
#include "systems/simple_render_system.hpp"
#include "systems/point_light_system.hpp"
#include "systems/planet_render_system.hpp"

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <stdexcept>
#include <chrono>
#include <array>
#include <numeric>
#include <glm/gtc/constants.hpp>

#define MAX_FRAME_TIME 100.0f

namespace lve {

    

    FirstApp::FirstApp() {
        globalPool = LveDescriptorPool::Builder(lveDevice)
            .addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, ULveSwapChain::MAX_FRAMES_IN_FLIGHT)
            .addPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 10)
            .setMaxSets(ULveSwapChain::MAX_FRAMES_IN_FLIGHT + 10)
            .build();
        
        textureSetLayout = LveDescriptorSetLayout::Builder(lveDevice)
            .addBinding(0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT)
            .build();

        loadGameObjects();
    }

    FirstApp::~FirstApp() {
    }

    void FirstApp::run() {
        std::vector<std::unique_ptr<LveBuffer>> uboBuffers(ULveSwapChain::MAX_FRAMES_IN_FLIGHT);
        for (int i = 0; i < uboBuffers.size(); i++){
            uboBuffers[i] = std::make_unique<LveBuffer>(
                lveDevice,
                sizeof(GlobalUbo),
                1,
                VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
            uboBuffers[i]->map();
        }

        auto globalSetLayout = LveDescriptorSetLayout::Builder(lveDevice)
            .addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS)
            .build();


            
        std::vector<VkDescriptorSet> globalDescriptorSets(ULveSwapChain::MAX_FRAMES_IN_FLIGHT);
        for (int i = 0; i < globalDescriptorSets.size(); i++) {
            auto bufferInfo = uboBuffers[i]->descriptorInfo();
            LveDescriptorWriter(*globalSetLayout, *globalPool)
                .writeBuffer(0, &bufferInfo)
                .build(globalDescriptorSets[i]);
        }
        
        SimpleRenderSystem simpleRenderSystem(
            lveDevice, 
            lveRenderer.getSwapChainRenderPass(), 
            globalSetLayout->getDescriptorSetLayout());

        PointLightSystem pointLightSystem(
            lveDevice, 
            lveRenderer.getSwapChainRenderPass(), 
            globalSetLayout->getDescriptorSetLayout());

        PlanetRenderSystem planetRenderSystem(
            lveDevice,
            lveRenderer.getSwapChainRenderPass(), 
            globalSetLayout->getDescriptorSetLayout(),
            textureSetLayout->getDescriptorSetLayout());

        ULveCamera camera;
        
        auto viewerObject = LveGameObject::createGameObject();
        viewerObject.transform.translation.z = -2.5f;
        KeyboardMovementController cameraController{};
        
        auto currentTime = std::chrono::high_resolution_clock::now();
        float globalTime = 0.f;

        while (!lveWindow.shouldClose()) {
            glfwPollEvents();

            auto newTime = std::chrono::high_resolution_clock::now();
            float frameTime = 
                std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
            currentTime = newTime;
            globalTime += frameTime;

            frameTime = glm::min(frameTime, MAX_FRAME_TIME);

            cameraController.moveInPlaneXZ(lveWindow.getGLFWWindow(), frameTime, viewerObject);
            camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);

            float aspect = lveRenderer.getAspectRatio();
            camera.setPerspectiveProjection(glm::radians(50.f), aspect, 0.1f, 10.f);
            

            if(auto commandBuffer = lveRenderer.beginFrame()) {
                int frameIndex = lveRenderer.getFrameIndex();
                FrameInfo frameInfo{
                    frameIndex,
                    frameTime,
                    globalTime,
                    commandBuffer,
                    camera,
                    globalDescriptorSets[frameIndex],
                    gameObjects
                };

                // update
                GlobalUbo ubo{};
                ubo.projection = camera.getProjection();
                ubo.view = camera.getView();
                pointLightSystem.update(frameInfo, ubo);
                planetRenderSystem.update(frameInfo, ubo);
                uboBuffers[frameIndex]->writeToBuffer(&ubo);
                uboBuffers[frameIndex]->flush();


                // render
                lveRenderer.beginSwapChainRenderPass(commandBuffer);
                simpleRenderSystem.renderGameObjects(frameInfo);
                pointLightSystem.render(frameInfo);
                planetRenderSystem.render(frameInfo);
                lveRenderer.endSwapChainRenderPass(commandBuffer);
                lveRenderer.endFrame();
            }
        }

        vkDeviceWaitIdle(lveDevice.device());
    }

    void FirstApp::loadGameObjects() {
        std::shared_ptr<LveModel> model;

        model = LveModel::createModelFromFile(lveDevice, "../models/quad.obj");
        auto quad = LveGameObject::createGameObject();
        quad.model = model;
        quad.transform.translation = { 0.0f, .5f, 0.0f };
        quad.transform.scale = {3.f, 1.f, 3.f};
        gameObjects.emplace(quad.getId(), std::move(quad));

        // auto pointLight = LveGameObject::makePointLight(0.2f);
        // gameObjects.emplace(pointLight.getId(), std::move(pointLight));

        // std::vector<glm::vec3> lightColors{
        //     {1.f, .1f, .1f},
        //     {.1f, .1f, 1.f},
        //     {.1f, 1.f, .1f},
        //     {1.f, 1.f, .1f},
        //     {.1f, 1.f, 1.f},
        //     {1.f, 1.f, 1.f}
        // };

        // for(int i =0 ; i < lightColors.size(); i++)
        // {
        //     auto pointLight = LveGameObject::makePointLight(0.2f);
        //     pointLight.color = lightColors[i];
        //     auto rotateLight = glm::rotate(
        //         glm::mat4(1.f),
        //         (i * glm::two_pi<float>()) / lightColors.size(),
        //         {0.f, -1.f, 0.f}
        //     );
        //     pointLight.transform.translation = glm::vec3(rotateLight * glm::vec4(-1.f, -1.f, -1.f, 1.f));
        //     gameObjects.emplace(pointLight.getId(), std::move(pointLight));
        // }

        // 태양은 돌지 않는다.
        auto pointSun = LveGameObject::makePlanet(lveDevice, "Sun", 5.0f);
        pointSun.color = glm::vec3{1.f, 1.f, 0.0f};
        pointSun.transform.translation = glm::vec3{0.f, 0.f, 0.f};
        if (pointSun.texture) {
            auto imageInfo = pointSun.texture->getImageInfo();
            LveDescriptorWriter(*textureSetLayout, *globalPool)
                .writeImage(0, &imageInfo)
                .build(pointSun.textureDescriptor);
        }
        gameObjects.emplace(pointSun.getId(), std::move(pointSun));

        // 지구는 태양을 돈다.
        auto pointEarth = LveGameObject::makePlanet(lveDevice, "Earth", 1.0f);
        pointEarth.color = glm::vec3{0.f, 0.f, 1.f};
        // 지구는 태양으로부터 어느정도 떨어진 위치에 위치.
        pointEarth.transform.translation = glm::vec3(pointSun.transform.translation + glm::vec3(1.5f, 0.f, 0.f));
        if (pointEarth.texture) {
            auto imageInfo = pointEarth.texture->getImageInfo();
            LveDescriptorWriter(*textureSetLayout, *globalPool)
                .writeImage(0, &imageInfo)
                .build(pointEarth.textureDescriptor);
        }
        gameObjects.emplace(pointEarth.getId(), std::move(pointEarth));

        // 달은 지구를 돈다.
        auto pointMoon = LveGameObject::makePlanet(lveDevice, "Moon", 1.0f);
        pointMoon.color = glm::vec3{0.f, .5f, 0.f};
        // 달는 지구으로부터 어느정도 떨어진 위치에 위치.
        pointMoon.transform.translation = glm::vec3(pointEarth.transform.translation + glm::vec3(0.5f, 0.f, 0.f));
        if (pointMoon.texture) {
            auto imageInfo = pointMoon.texture->getImageInfo();
            LveDescriptorWriter(*textureSetLayout, *globalPool)
                .writeImage(0, &imageInfo)
                .build(pointMoon.textureDescriptor);
        }
        gameObjects.emplace(pointMoon.getId(), std::move(pointMoon));
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