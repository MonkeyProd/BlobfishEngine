#ifndef COMPOUND_ENTITY_H
#define COMPOUND_ENTITY_H

#include "Scene.h"
#include <Core/BlobPCH.h>
#include <entt.hpp>
#include <optional>

namespace bf {

    class Entity {
    public:
        Entity() = default;

        Entity(entt::entity handle, Scene *scene);

        Entity(const Entity &other) = default;

        template<typename T, typename... Args>
        T &AddComponent(Args &&... args) {
            BF_ASSERT(!HasComponent<T>(), "Entity::AddComponent - Entity already has component!");
            return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
        }

        template<typename T, typename... Args>
        T& AddOrReplaceComponent(Args&&... args)
        {
            return m_Scene->m_Registry.emplace_or_replace<T>(m_EntityHandle, std::forward<Args>(args)...);
        }

        template<typename T>
        T &GetComponent() {
            BF_ASSERT(HasComponent<T>(), "Entity::GetComponent - Entity does not have component!");
            return m_Scene->m_Registry.get<T>(m_EntityHandle);
        }

        template<typename T>
        bool HasComponent() {
            return m_Scene->m_Registry.all_of<T>(m_EntityHandle);
        }

        template<typename T>
        void RemoveComponent() {
            BF_ASSERT(HasComponent<T>(), "Entity::RemoveComponent - Entity does not have component!");
            m_Scene->m_Registry.remove<T>(m_EntityHandle);
        }

        operator bool() const { return m_EntityHandle != entt::null; }

        operator entt::entity() const { return m_EntityHandle; }

        operator uint32_t() const { return (uint32_t) m_EntityHandle; }

        bool operator==(const Entity &other) const {
            return m_EntityHandle == other.m_EntityHandle && m_Scene == other.m_Scene;
        }

        bool operator!=(const Entity &other) const {
            return !(*this == other);
        }

        std::optional<Entity> Find(const std::string &Tag){
            auto view = m_Scene->m_Registry.view<TagComponent>();
            for(auto entity: view){
                if(m_Scene->m_Registry.get<TagComponent>(entity).Tag==Tag){
                    return Entity{entity, m_Scene};
                }
            }
            return {};
        }

    private:
        entt::entity m_EntityHandle{entt::null};
        Scene *m_Scene = nullptr;

        friend class Scene;
    };


} // bf

#endif //COMPOUND_ENTITY_H
