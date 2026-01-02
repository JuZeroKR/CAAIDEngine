#pragma once

#include "ULve_model.hpp"

//libs
#include <glm/gtc/matrix_transform.hpp>


#include <memory>
#include <unordered_map>

namespace lve {
    struct TransformComponent {
        glm::vec3 translation{};  // (position offset)
        glm::vec3 scale{1.f, 1.f, 1.f};
        glm::vec3 rotation;

        // Matrix corresponds to translate * Rz * Rx * Ry * scale transformation
        // Matrix corrsponds to Translate * Ry * Rx * Rz * Scale
        // Rotations correspond to Tait-bryan angles of Y(1), X(2), Z(3)
        // https://en.wikipedia.org/wiki/Euler_angles#Rotation_matrix
        glm::mat4 mat4();
        glm::mat3 normalMatrix();
    };

    struct PointLightComponent {
        float lightIntensity = 1.0f;
    };

    class LveGameObject {
        public:
            using id_t = unsigned int;
            using Map = std::unordered_map<id_t, LveGameObject>;

            static LveGameObject createGameObject() {
                static id_t id = 0;
                return LveGameObject(id++);
            }

            id_t getId() const { return id; }

            static LveGameObject makePointLight(
                float intensity = 10.f, float radius = 0.1f, glm::vec3 color = glm::vec3{1.f});

            LveGameObject(const LveGameObject&) = delete;
            LveGameObject& operator=(const LveGameObject&) = delete;
            LveGameObject(LveGameObject&&) = default;
            LveGameObject& operator=(LveGameObject&&) = default;
            
            glm::vec3 color{};
            TransformComponent transform{};

            // Optional Pointer components
            std::shared_ptr<LveModel> model{};
            std::unique_ptr<PointLightComponent> pointLight = nullptr;

        private:
        LveGameObject(id_t objId) : id(objId) {}

        id_t id;

    };
}