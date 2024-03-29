#ifndef COMPOUND_SCENE_H
#define COMPOUND_SCENE_H

#include <entt.hpp>
#include <Core/Timestep.h>
#include <Renderer/Camera.h>
#include "EditorCamera.h"

namespace bf {
    // forward declaration
    class Serializer;

    class Entity;

    class Scene {
    public:
        Scene();

        ~Scene();

        Entity CreateEntity(const std::string &name = std::string());

        void DestroyEntity(Entity e);

        void OnUpdate(Timestep ts);

        void OnUpdateEditor(Timestep ts, EditorCamera *camera);

        void OnViewportResize(uint32_t width, uint32_t height);

        const entt::registry &GetRegistry() const { return m_Registry; }

    private:
        void RenderScene(const Camera *camera, const glm::mat4 &cameraTransform);

    private:
        entt::registry m_Registry;
        uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

        friend class Entity;

        friend class Serializer;
    };

} // bf

#endif //COMPOUND_SCENE_H
