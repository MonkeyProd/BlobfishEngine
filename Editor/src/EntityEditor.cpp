#include "EntityEditor.h"
#include <glm/gtc/type_ptr.hpp>
using namespace bf;

void EntityEditor::DisplayEntityEditorWindow(Scene *scene, glm::vec2 &viewportSize) {
    if (ImGui::Begin("Entities")) {
        // Deselect if clicked on empty space
        if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
            m_SelectedEntity = {};

        scene->GetRegistry().each([&](auto entityID) {
            Entity e(entityID, scene);
            auto tag = e.HasComponent<TagComponent>() ? e.GetComponent<TagComponent>().Tag.c_str() : std::to_string(
                    (uint32_t) entityID).c_str();
            ImGuiTreeNodeFlags flags =
                    ((m_SelectedEntity == e) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow |
                    ImGuiTreeNodeFlags_SpanAvailWidth;
            bool opened = ImGui::TreeNodeEx((void *) entityID, flags, "%s", tag);
            if (ImGui::IsItemClicked()) {
                m_SelectedEntity = e;
            }
            if (opened) {
                ImGui::Text("here can be a child of %s", tag);
                ImGui::TreePop();
            } else {
//                    ImGui::TreePop();
            }
        });

        // Show components of selected entity
        if (ImGui::Begin("Components")) {
            if (m_SelectedEntity) {
                // Add components popup menu button
                if (ImGui::Button("Add component")) {
                    ImGui::OpenPopup("components");
                }
                if (ImGui::BeginPopup("components")) {
                    bool has_anything_to_add = false;
                    if (not m_SelectedEntity.HasComponent<TransformComponent>()) {
                        if (ImGui::Selectable("TransformComponent")) {
                            m_SelectedEntity.AddComponent<TransformComponent>();
                        }
                        has_anything_to_add = true;
                    }
                    if (not m_SelectedEntity.HasComponent<SpriteRendererComponent>()) {
                        if (ImGui::Selectable("SpriteRendererComponent")) {
                            m_SelectedEntity.AddComponent<SpriteRendererComponent>();
                        }
                        has_anything_to_add = true;
                    }
                    if (not m_SelectedEntity.HasComponent<CameraComponent>()) {
                        if (ImGui::Selectable("CameraComponent")) {
                            m_SelectedEntity.AddComponent<CameraComponent>();
                            m_SelectedEntity.GetComponent<CameraComponent>().m_Camera.SetViewportSize(
                                    (uint32_t) viewportSize.x, (uint32_t) viewportSize.y);
                        }
                        has_anything_to_add = true;
                    }if (not m_SelectedEntity.HasComponent<NativeScriptComponent>()) {
                        if (ImGui::Selectable("NativeScriptComponent")) {
                            m_SelectedEntity.AddComponent<NativeScriptComponent>().Bind<NativeScript>();
                            // TODO think about initializing NativeScript
                            ImGui::EndPopup(); // 'Add component' popup
                            ImGui::End(); // 'Components' window
                            ImGui::End(); // 'Entities' window
                            return; // early exit to prevent access to uninitialized NativeScript->Instance
                        }
                        has_anything_to_add = true;
                    }
                    if (not has_anything_to_add) {
                        ImGui::Text("Nothing to add");
                    }
                    ImGui::EndPopup();
                }
                // Destroy entity button;
                ImGui::SameLine();
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(218 / 255.0f, 40 / 255.0f, 40 / 255.0f, 1.0f));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(239 / 255.0f, 103 / 255.0f, 103 / 255.0f, 1.0f));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(255 / 255.0f, 48 / 255.0f, 48 / 255.0f, 1.0f));
                if (ImGui::Button("Destroy entity")) {
                    scene->DestroyEntity(m_SelectedEntity);
                    m_SelectedEntity = {};
                    ImGui::PopStyleColor(3);
                } else {
                    ImGui::PopStyleColor(3);

                    // functions for displaying ui for all components
                    auto displayTagComponent = [&]() {
                        auto &tag = m_SelectedEntity.GetComponent<TagComponent>().Tag;
                        char buffer[256];
                        memset(buffer, 0, sizeof(buffer));
                        strncpy(buffer, tag.c_str(), sizeof(buffer));
                        if (ImGui::InputText("##Tag", buffer, sizeof(buffer))) {
                            tag = std::string(buffer);
                        }
                    };
                    auto displayTransformComponent = [&]() {
                        auto &transformComponent = m_SelectedEntity.GetComponent<TransformComponent>();
                        ImGui::DragFloat3("Position", glm::value_ptr(transformComponent.Position));
                        ImGui::SliderAngle("Rotation",
                                           &transformComponent.Rotation);
                        ImGui::DragFloat2("Scale", glm::value_ptr(transformComponent.Scale));
                    };
                    auto displaySpriteRendererComponent = [&]() {
                        auto &component = m_SelectedEntity.GetComponent<SpriteRendererComponent>();
                        ImGui::Text("Texture: ");
                        ImGui::SameLine();
                        if (component.Texture) {
                            ImGui::Image((ImTextureID) (intptr_t) component.Texture->GetRendererID(), ImVec2(64, 64),
                                         ImVec2(0, 1),
                                         ImVec2(1, 0));
                            ImGui::DragFloat("Tiling factor", &component.TilingFactor, 1.0f, 0.0f, 100.0f);
                            ImGui::ColorEdit4("Tint Color", glm::value_ptr(component.Color));
                        } else {
                            ImGui::Text("None");
                            ImGui::Text("Tiling factor: None");
                            ImGui::ColorEdit4("Color", glm::value_ptr(component.Color));
                        }
                    };
                    auto displayCameraComponent = [&]() {
                        auto &component = m_SelectedEntity.GetComponent<CameraComponent>();
                        auto& camera = component.m_Camera;

                        float orthoSize = camera.GetOrthographicSize();
                        if (ImGui::DragFloat("Orthographic Size", &orthoSize))
                            camera.SetOrthographicSize(orthoSize);

                        float orthoNear = camera.GetOrthographicNearClip();
                        if (ImGui::DragFloat("Near", &orthoNear))
                            camera.SetOrthographicNearClip(orthoNear);

                        float orthoFar = camera.GetOrthographicFarClip();
                        if (ImGui::DragFloat("Far", &orthoFar))
                            camera.SetOrthographicFarClip(orthoFar);

                        ImGui::Checkbox("Primary", &component.Primary);
                        ImGui::Checkbox("Fixed Aspect Ratio", &component.FixedAspectRatio);
                    };
                    auto displayNativeScriptComponent = [&]() {
                        auto &script = m_SelectedEntity.GetComponent<NativeScriptComponent>();
                        script.Instance->OnImGuiRender();
                    };
                    // Display components if they exist
                    ImGui::SameLine();
                    displayTagComponent(); // except for TagComponent which is always exist
                    DisplayComponent<TransformComponent>(displayTransformComponent, "TransformComponent");
                    DisplayComponent<SpriteRendererComponent>(displaySpriteRendererComponent,
                                                              "SpriteRendererComponent");
                    DisplayComponent<CameraComponent>(displayCameraComponent,
                                                      "CameraComponent");
                    DisplayComponent<NativeScriptComponent>(displayNativeScriptComponent, "NativeScriptComponent");
                }
            } else {
                // If no entity selected
                ImGui::Text("Click on entity in the 'Entities' menu to see/edit it's components");
                ImGui::Text("Or ");
                ImGui::SameLine();
                if (ImGui::Button("Create new entity")) {
                    scene->CreateEntity();
                }
            }
            ImGui::End();
        } else
            ImGui::End();

        // Right mouse button click response
        if (ImGui::BeginPopupContextWindow(nullptr, 1)) {
            if (ImGui::MenuItem("Add entity")) {
                scene->CreateEntity();
            }
            ImGui::EndPopup();
        }

    }
    ImGui::End();
}

template<class T, class F>
bool EntityEditor::DisplayComponent(F UIfunction, const char *title) {
    if (m_SelectedEntity.HasComponent<T>()) {
        ImGui::PushID(title);
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(218 / 255.0f, 40 / 255.0f, 40 / 255.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(239 / 255.0f, 103 / 255.0f, 103 / 255.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(255 / 255.0f, 48 / 255.0f, 48 / 255.0f, 1.0f));
        if (ImGui::Button("X")) {
            ImGui::PopStyleColor(3);
            m_SelectedEntity.RemoveComponent<T>();
            ImGui::PopID();
            return true;
        } else {
            ImGui::PopStyleColor(3);
            ImGui::SameLine();

            //TODO mb draw icon for component?

            if (ImGui::CollapsingHeader(title)) {
                ImGui::Indent(30.0f);
                UIfunction();
                ImGui::Unindent(30.0f);
            }
        }
        ImGui::PopID();
        return true;
    }
    return false;
}