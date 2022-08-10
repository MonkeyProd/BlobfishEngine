#ifndef COMPOUND_SCENE_H
#define COMPOUND_SCENE_H

#include <entt.hpp>
#include <Core/Timestep.h>

namespace bf {

    class Entity;

    class Scene {
    public:
        Scene();

        ~Scene();

        Entity CreateEntity(const std::string &name = std::string());

        void DestroyEntity(Entity e);

        void OnUpdate(Timestep ts);

        void OnViewportResize(uint32_t width, uint32_t height);

        const entt::registry &GetRegistry() const { return m_Registry; }

    private:
        entt::registry m_Registry;
        uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

        friend class Entity;
    };

} // bf

#endif //COMPOUND_SCENE_H
