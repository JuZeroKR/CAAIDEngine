#include "planet_render_system.hpp"

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <stdexcept>
#include <array>
#include <glm/gtc/constants.hpp>



namespace lve {

    struct PointLightPushConstants {
        glm::vec4 position{};
        glm::vec4 color{};
        float radius;
    };

    PlanetRenderSystem::PlanetRenderSystem(ULveDevice &device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout, VkDescriptorSetLayout textureSetLayout) : lveDevice(device) {
        createPipelineLayout(globalSetLayout, textureSetLayout);
        createPipeline(renderPass);
    }

    PlanetRenderSystem::~PlanetRenderSystem() {
        vkDestroyPipelineLayout(lveDevice.device(), pipelineLayout, nullptr);
    }

    void PlanetRenderSystem::createPipelineLayout(VkDescriptorSetLayout globalSetLayout, VkDescriptorSetLayout textureSetLayout) {

        VkPushConstantRange pushConstantRange{};
        pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
        pushConstantRange.offset = 0;
        pushConstantRange.size = sizeof(PointLightPushConstants);

        std::vector<VkDescriptorSetLayout> descriptorSetLayouts{globalSetLayout, textureSetLayout};
        
        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = descriptorSetLayouts.size();
        pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();
        pipelineLayoutInfo.pushConstantRangeCount = 1;
        pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;

        if (vkCreatePipelineLayout(lveDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
            throw std::runtime_error("failed to create pipeline layout!");
        }
    }

    void PlanetRenderSystem::createPipeline(VkRenderPass renderPass) {
        PipelineConfigInfo pipelineConfig{};
        ULvePipeline::defaultPipelineConfigInfo(pipelineConfig);
        pipelineConfig.renderPass = renderPass;
        pipelineConfig.pipelineLayout = pipelineLayout;
        lvePipeline = std::make_unique<ULvePipeline>(lveDevice, 
            "../shaders/point_light.vert.spv",
            "../shaders/point_light.frag.spv", 
            pipelineConfig
        );
    }
    
    void PlanetRenderSystem::update(FrameInfo &frameInfo, GlobalUbo &ubo) {
        // 1. Find planet objects
        LveGameObject* sun = nullptr;
        LveGameObject* earth = nullptr;
        LveGameObject* moon = nullptr;

        for(auto &kv : frameInfo.gameObjects) {
            auto& obj = kv.second;
            if(obj.planetInfo == nullptr) continue;

            if(obj.objectName == "Sun") sun = &obj;
            else if(obj.objectName == "Earth") earth = &obj;
            else if(obj.objectName == "Moon") moon = &obj;
        }

        // 2. Update positions (Hierarchical)
        if (sun) {
            // Sun stays at center (or rotates around itself, but here fixed)
            sun->transform.translation = glm::vec3(0.f); 
        }

        if (earth && sun) {
            auto rotateEarth = glm::rotate(
                glm::mat4(1.f),
                frameInfo.globalTime * 0.5f, // Earth speed
                {0.f, 1.f, 0.f}
            );
            // Earth orbits Sun at distance 1.5
            earth->transform.translation = sun->transform.translation + glm::vec3(rotateEarth * glm::vec4(1.5f, 0.f, 0.f, 1.f));
        }

        if (moon && earth) {
            auto rotateMoon = glm::rotate(
                glm::mat4(1.f),
                frameInfo.globalTime * 2.0f, // Moon orbits faster
                {0.f, 1.f, 0.f}
            );
            // Moon orbits Earth at distance 0.5
            moon->transform.translation = earth->transform.translation + glm::vec3(rotateMoon * glm::vec4(0.5f, 0.f, 0.f, 1.f));
        }

        // 3. Update UBO for lighting
        int planetIndex = 0;
        for(auto &kv : frameInfo.gameObjects) {
            auto& obj = kv.second;
            if(obj.planetInfo == nullptr) continue;

            assert(planetIndex < MAX_LIGHTS && "Point lights exceed maximum specified");

            // copy light to ubo
            ubo.pointLights[planetIndex].position = glm::vec4(obj.transform.translation, 1.f);
            ubo.pointLights[planetIndex].color = glm::vec4(obj.color, obj.planetInfo->lightIntensity);
            planetIndex++;
        }
        ubo.numLights = planetIndex;
    }

    void PlanetRenderSystem::render(
        FrameInfo &frameInfo) {
        lvePipeline->bind(frameInfo.commandBuffer);

        vkCmdBindDescriptorSets(
            frameInfo.commandBuffer,
            VK_PIPELINE_BIND_POINT_GRAPHICS,
            pipelineLayout,
            0,
            1,
            &frameInfo.globalDescriptorSet,
            0,
            nullptr
        );

        for(auto &kv : frameInfo.gameObjects) {
            auto& obj = kv.second;
            if(obj.planetInfo == nullptr) continue;

            PointLightPushConstants pushConstants{};
            pushConstants.position = glm::vec4(obj.transform.translation, 1.f);
            pushConstants.color = glm::vec4(obj.color, obj.planetInfo->lightIntensity);
            pushConstants.radius = obj.transform.scale.x;

            if (obj.textureDescriptor != VK_NULL_HANDLE) {
                vkCmdBindDescriptorSets(
                    frameInfo.commandBuffer,
                    VK_PIPELINE_BIND_POINT_GRAPHICS,
                    pipelineLayout,
                    1,  // firstSet (Set 1)
                    1,  // descriptorSetCount
                    &obj.textureDescriptor,
                    0,
                    nullptr
                );
            }

            vkCmdPushConstants(
                frameInfo.commandBuffer,
                pipelineLayout,
                VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
                0,
                sizeof(PointLightPushConstants),
                &pushConstants
            );
            vkCmdDraw(frameInfo.commandBuffer, 6, 1, 0, 0);
        }

    }
}