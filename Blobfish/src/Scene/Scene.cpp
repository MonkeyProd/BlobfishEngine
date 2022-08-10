#include "Scene.h"

#include "Entity.h"
#include "Components.h"
#include <Renderer/Renderer2D.h>

namespace bf {
    Scene::Scene() {
    }

    Scene::~Scene() {
    }

    Entity Scene::CreateEntity(const std::string &name) {
        Entity entity = {m_Registry.create(), this};
        entity.AddComponent<TransformComponent>();
        auto &tag = entity.AddComponent<TagComponent>();
        tag.Tag = name.empty() ? "Entity" : name;
        return entity;
    }

    void Scene::OnUpdate(Timestep ts) {
        Camera *mainCamera = nullptr;
        glm::mat4 cameraTransform{1.0f};
        {
            auto group = m_Registry.view<CameraComponent, TransformComponent>();
            for (auto entity: group) {
                auto [camera, transform] = group.get<CameraComponent, TransformComponent>(entity);
                if (camera.Primary) {
                    mainCamera = &camera.Camera;
                    cameraTransform = transform.GetTransform();
                    break;
                }
            }
        }

        if (mainCamera) {
            RenderScene(*mainCamera, cameraTransform);
        }
    }

    void Scene::RenderScene(const Camera &camera, const glm::mat4 &cameraTransform) {
        Renderer2D::BeginScene(camera.GetProjection(), cameraTransform);
        auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
        for (auto entity: group) {
            auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
            if (sprite.Texture)
                Renderer2D::DrawQuad(transform.GetTransform(), sprite.Texture, sprite.TilingFactor, sprite.Color);
            else
                Renderer2D::DrawQuad(transform.GetTransform(), sprite.Color);
        }
        Renderer2D::EndScene();
    }

    void Scene::OnViewportResize(uint32_t width, uint32_t height)
    {
        m_ViewportWidth = width;
        m_ViewportHeight = height;

        // Resize our non-FixedAspectRatio cameras
        auto view = m_Registry.view<CameraComponent>();
        for (auto entity : view)
        {
            auto& cameraComponent = view.get<CameraComponent>(entity);
            if (!cameraComponent.FixedAspectRatio)
                cameraComponent.Camera.SetViewportSize(width, height);
        }

    }

    void Scene::DestroyEntity(Entity e) {
        m_Registry.destroy(e);
    }
} // bf