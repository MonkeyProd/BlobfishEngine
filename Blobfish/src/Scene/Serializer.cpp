#include "Serializer.h"
#include <pugixml.hpp>

namespace bf {
    static pugi::xml_document doc;

    Serializer::Serializer(Scene *scene) : m_scene(scene) {

    }

    void Serializer::Serialize(const std::string &name, const std::string &path) {
        doc.reset();
        auto scene_node = doc.append_child("scene");
        scene_node.append_attribute("name") = name.c_str();
        m_scene->m_Registry.each([&](auto entityID) {
            Entity e{entityID, m_scene};
            if (not e) return;
            SerializeEntity(e);
        });
        doc.save_file(path.c_str());
    }

    void Serializer::Deserialize(const std::string &filepath) {

        doc.reset();
        if (not doc.load_file(filepath.c_str())) {
            BF_LOG_WARN("Failed to load {0}", filepath);
            return;
        }
        auto scene = doc.child("scene");
        for (pugi::xml_node entity_node = scene.child("entity"); entity_node; entity_node = entity_node.next_sibling(
                "entity")) {
            auto entity = m_scene->CreateEntity(entity_node.attribute("Tag").as_string());
            if (entity_node.child("components").attribute("TransformComponent").as_bool()) {
                auto &transform = entity.GetComponent<TransformComponent>(); // TransformComponent exist by default. See Scene::CreateEntity.
                auto transform_node = entity_node.child("TransformComponent");

                auto position_node = transform_node.child("position");
                transform.Position.x = position_node.attribute("x").as_float();
                transform.Position.y = position_node.attribute("y").as_float();
                transform.Position.z = position_node.attribute("z").as_float();

                transform.Rotation = transform_node.child("rotation").attribute("degrees").as_float();

                auto scale_node = transform_node.child("scale");
                transform.Scale.x = scale_node.attribute("x").as_float();
                transform.Scale.y = scale_node.attribute("y").as_float();
            }
            if (entity_node.child("components").attribute("SpriteRendererComponent").as_bool()) {
                auto &sprite = entity.AddComponent<SpriteRendererComponent>();
                auto sprite_node = entity_node.child("SpriteRendererComponent");

                auto color_node = sprite_node.child("color");
                sprite.Color.r = color_node.attribute("r").as_float();
                sprite.Color.g = color_node.attribute("g").as_float();
                sprite.Color.b = color_node.attribute("b").as_float();
                sprite.Color.a = color_node.attribute("a").as_float();

                auto texture_node = sprite_node.child("texture");
                sprite.Texture = Texture2D::Create(texture_node.attribute("path").as_string());
                sprite.TilingFactor = texture_node.attribute("tiling-factor").as_float();
            }
            if (entity_node.child("components").attribute("CameraComponent").as_bool()) {
                auto &camera_component = entity.AddComponent<CameraComponent>();
                auto camera_component_node = entity_node.child("CameraComponent");

                auto flags = camera_component_node.child("flags");
                camera_component.Primary = flags.attribute("primary").as_bool();
                camera_component.FixedAspectRatio = flags.attribute("fixed-aspect-ratio").as_bool();

                auto camera_node = camera_component_node.child("camera");
                auto size = camera_node.attribute("orthographic-size").as_float();
                auto near = camera_node.attribute("orthographic-near-clip").as_float();
                auto far = camera_node.attribute("orthographic-far-clip").as_float();
                camera_component.Camera.SetOrthographic(size, near, far);
            }
            if (entity_node.child("components").attribute("NativeScriptComponent").as_bool()) {
                // todo implement this
                BF_LOG_WARN("NativeScriptComponent deserialization is not supported yet");
            }
        }
    }

    void Serializer::SerializeEntity(Entity &entity) {
        auto entity_node = doc.child("scene").append_child("entity");

        auto component_node = entity_node.append_child("components");
        component_node.append_attribute("TransformComponent") = false;
        component_node.append_attribute("SpriteRendererComponent") = false;
        component_node.append_attribute("CameraComponent") = false;
        component_node.append_attribute("NativeScriptComponent") = false;

        component_node.attribute("TagComponent") = true;
        entity_node.append_attribute("Tag") = entity.GetComponent<TagComponent>().Tag.c_str();

        if (entity.HasComponent<TransformComponent>()) {
            component_node.attribute("TransformComponent") = true;
            auto transform_node = entity_node.append_child("TransformComponent");
            auto transform = entity.GetComponent<TransformComponent>();

            auto position_node = transform_node.append_child("position");
            position_node.append_attribute("x") = transform.Position.x;
            position_node.append_attribute("y") = transform.Position.y;
            position_node.append_attribute("z") = transform.Position.z;

            transform_node.append_child("rotation").append_attribute("degrees") = transform.Rotation;

            auto scale_node = transform_node.append_child("scale");
            scale_node.append_attribute("x") = transform.Scale.x;
            scale_node.append_attribute("y") = transform.Scale.y;
        }
        if (entity.HasComponent<SpriteRendererComponent>()) {
            component_node.attribute("SpriteRendererComponent") = true;
            auto sprite_node = entity_node.append_child("SpriteRendererComponent");
            auto sprite = entity.GetComponent<SpriteRendererComponent>();

            auto color_node = sprite_node.append_child("color");
            color_node.append_attribute("r") = sprite.Color.r;
            color_node.append_attribute("g") = sprite.Color.g;
            color_node.append_attribute("b") = sprite.Color.b;
            color_node.append_attribute("a") = sprite.Color.a;

            auto texture_node = sprite_node.append_child("texture");
            texture_node.append_attribute("path") = sprite.Texture->GetPath().c_str();
            texture_node.append_attribute("tiling-factor") = sprite.TilingFactor;
        }
        if (entity.HasComponent<CameraComponent>()) {
            component_node.attribute("CameraComponent") = true;
            auto camera_component_node = entity_node.append_child("CameraComponent");
            auto camera = entity.GetComponent<CameraComponent>();

            auto flags_node = camera_component_node.append_child("flags");
            flags_node.append_attribute("primary") = camera.Primary;
            flags_node.append_attribute("fixed-aspect-ratio") = camera.FixedAspectRatio;

            auto camera_node = camera_component_node.append_child("camera");
            camera_node.append_attribute("orthographic-size") = camera.Camera.GetOrthographicSize();
            camera_node.append_attribute("orthographic-near-clip") = camera.Camera.GetOrthographicNearClip();
            camera_node.append_attribute("orthographic-far-clip") = camera.Camera.GetOrthographicFarClip();
        }
        if (entity.HasComponent<NativeScriptComponent>()) {
            component_node.attribute("NativeScriptComponent") = true;
            entity_node.append_child("NativeScriptComponent").append_child("data").append_attribute(
                    "info") = "nothing yet (not implemented)";
            // todo implement this
            BF_LOG_WARN("NativeScriptComponent serialization is not supported yet");
        }
    }
} // bf