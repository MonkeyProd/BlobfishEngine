#include "Entity.h"

namespace bf {
    Entity::Entity(entt::entity handle, Scene *scene) : m_EntityHandle(handle), m_Scene(scene) {

    }
} // bf