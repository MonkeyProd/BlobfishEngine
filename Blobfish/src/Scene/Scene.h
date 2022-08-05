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

        void OnUpdate(Timestep ts);

    private:
        entt::registry m_Registry;

        friend class Entity;
    };

} // bf

#endif //COMPOUND_SCENE_H
