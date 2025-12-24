    void FirstApp::renderGameObjects(VkCommandBuffer commandBuffer) {
        lvePipeline->bind(commandBuffer);

        for (auto& obj : gameObjects) {
            SimplePushConstantData push{};
            push.offset = obj.transform2d.translation;
            push.color = obj.color;
            push.transform = glm::mat4{obj.transform2d.mat2()};

            vkCmdPushConstants(
                commandBuffer,
                pipelineLayout,
                VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
                0,
                sizeof(SimplePushConstantData),
                &push);

            obj.model->bind(commandBuffer);
            obj.model->draw(commandBuffer); 
        }
    }
}
