#pragma once
#include <vector>
#include <string>
#include "ULve_device.hpp"

namespace lve {
    struct PipelineConfigInfo {
        PipelineConfigInfo() = default;
        PipelineConfigInfo(const PipelineConfigInfo&) = delete;
        PipelineConfigInfo& operator=(const PipelineConfigInfo&) = delete;

        std::vector<VkDynamicState> dynamicStateEnables;
        VkPipelineVertexInputStateCreateInfo vertexInputInfo;
        VkPipelineViewportStateCreateInfo viewportInfo;
        VkPipelineColorBlendAttachmentState colorBlendAttachment;  
        VkPipelineColorBlendStateCreateInfo colorBlending;
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
        VkPipelineRasterizationStateCreateInfo rasterizerInfo;
        VkPipelineMultisampleStateCreateInfo multisamplingInfo;
        VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
        VkPipelineDynamicStateCreateInfo dynamicStateInfo;
        VkPipelineLayout pipelineLayout = nullptr;
        VkRenderPass renderPass = nullptr;
        uint32_t subpass = 0;
    };

    class ULvePipeline {
        public:
            ULvePipeline(
                ULveDevice &device, 
                const std::string& vertFilepath, 
                const std::string& fragFilepath, 
                const PipelineConfigInfo &configInfo);
            ~ULvePipeline();
            ULvePipeline(const ULvePipeline &other) = delete;
            ULvePipeline &operator=(const ULvePipeline &other) = delete;
            
            void    bind(VkCommandBuffer commandBuffer);
            static void defaultPipelineConfigInfo(PipelineConfigInfo& configInfo);
        private:

            static std::vector<char> readFile(const std::string& filepath);

            void createGraphicsPipeline(const std::string& vertFilepath, 
                const std::string& fragFilepath,
                const PipelineConfigInfo &configInfo);

            void createShaderModule(const std::vector<char> &code, VkShaderModule *shaderModule);

            ULveDevice &device;
            VkPipeline graphicsPipeline;
            VkShaderModule vertShaderModule;
            VkShaderModule fragShaderModule;
    };  
}