#ifndef COMPOUND_COMPONENTS_H
#define COMPOUND_COMPONENTS_H

#include <glm/glm.hpp>
#include <Renderer/Texture.h>
#include <Core/BlobPCH.h>
#include "Renderer/Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <Core/Timestep.h>

namespace bf {
    struct TagComponent {
        std::string Tag;

        TagComponent() = default;

        TagComponent(const TagComponent &) = default;

        TagComponent(const std::string &tag)
                : Tag(tag) {}
    };

    struct TransformComponent {
        glm::vec3 Position{0.0f, 0.0f, 0.0f};
        float Rotation{0.0f};
        glm::vec2 Scale{1.0f, 1.0f};

        TransformComponent() = default;

        TransformComponent(const TransformComponent &) = default;

        TransformComponent(const glm::vec3 &position)
                : Position(position) {}

        glm::mat4 GetTransform() const {
            auto t = glm::translate(glm::mat4(1.0f), Position) *
                     glm::rotate(glm::mat4(1.0f), Rotation, {0.0f, 0.0f, 1.0f})
                     * glm::scale(glm::mat4(1.0f), {Scale.x, Scale.y, 1.0f});
            return t;
        }
    };

    struct SpriteRendererComponent {
        glm::vec4 Color{1.0f, 1.0f, 1.0f, 1.0f};
        Texture2D *Texture; // TODO: smart pointers
        float TilingFactor = 1.0f;

        SpriteRendererComponent() = default;

        SpriteRendererComponent(const SpriteRendererComponent &) = default;

        SpriteRendererComponent(const glm::vec4 &color)
                : Color(color) {}
    };

    struct CameraComponent {
        Camera Camera;
        bool Primary = true;
        bool FixedAspectRatio = false;

        CameraComponent() = default;

        CameraComponent(const CameraComponent &) = default;

        CameraComponent(const glm::mat4 &projection)
                : Camera(projection) {}
    };

    // Forward declaration
    class NativeScript;


    struct NativeScriptComponent
    {
        NativeScript* Instance = nullptr;

        std::function<void()> InstantiateFunction;
        std::function<void()> DestroyInstanceFunction;

        template<typename T>
        void Bind()
        {
            InstantiateFunction = [&]() { Instance = new T(); };
            DestroyInstanceFunction = [&]() { delete (T*)Instance; Instance = nullptr; };
        }
    };
}

#endif //COMPOUND_COMPONENTS_H
