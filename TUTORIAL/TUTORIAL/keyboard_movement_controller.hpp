#pragma once

#include "ULve_gameobject.hpp"
#include "ULveWindow.h"

namespace lve {
    class KeyboardMovementController {
    public:
        struct KeyMappings {
            int moveLeft = GLFW_KEY_A;
            int moveRight = GLFW_KEY_D;
            int moveForward = GLFW_KEY_W;
            int moveBack = GLFW_KEY_S;
            int moveUp = GLFW_KEY_SPACE;
            int moveDown = GLFW_KEY_LEFT_CONTROL;
            int loopLeft = GLFW_KEY_LEFT;
            int loopRight = GLFW_KEY_RIGHT;
            int loopUp = GLFW_KEY_UP;
            int loopDown = GLFW_KEY_DOWN;
        };

        void moveInPlaneXZ(GLFWwindow* window, float dt, LveGameObject& obj);

        KeyMappings keys{};
        float moveSpeed{ 3.f };
        float lookSpeed{ 1.f };
    };
}