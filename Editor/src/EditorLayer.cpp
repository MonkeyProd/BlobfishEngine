#include "EditorLayer.h"
#include <glm/gtc/type_ptr.hpp>
#include <Core/BlobPCH.h>

void EditorLayer::OnAttach() {
    m_apples = Texture2D::Create("../../Sandbox/assets/apples.png");
    m_Framebuffer = Framebuffer::Create({800, 600});

    ImGuiIO &io = ImGui::GetIO();
    float FontSize = 13;
    io.Fonts->AddFontFromFileTTF("../../Editor/Assets/Fonts/Ubuntu-Regular.ttf", FontSize);

    auto apples = m_scene.CreateEntity("apples");
    apples.AddComponent<SpriteRendererComponent>(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    apples.GetComponent<SpriteRendererComponent>().Texture = m_apples;

    ImVec4 *colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.44f, 0.44f, 0.44f, 0.60f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.57f, 0.57f, 0.57f, 0.70f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.76f, 0.76f, 0.76f, 0.80f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.60f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.13f, 0.75f, 0.55f, 0.80f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.13f, 0.75f, 0.75f, 0.80f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
    colors[ImGuiCol_Button] = ImVec4(0.13f, 0.75f, 0.55f, 0.40f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.13f, 0.75f, 0.75f, 0.60f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
    colors[ImGuiCol_Header] = ImVec4(0.13f, 0.75f, 0.55f, 0.40f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.13f, 0.75f, 0.75f, 0.60f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
    colors[ImGuiCol_Separator] = ImVec4(0.13f, 0.75f, 0.55f, 0.40f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.13f, 0.75f, 0.75f, 0.60f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.13f, 0.75f, 0.55f, 0.40f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.13f, 0.75f, 0.75f, 0.60f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
    colors[ImGuiCol_Tab] = ImVec4(0.13f, 0.75f, 0.55f, 0.80f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.13f, 0.75f, 0.75f, 0.80f);
    colors[ImGuiCol_TabActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.36f, 0.36f, 0.36f, 0.54f);
    colors[ImGuiCol_DockingPreview] = ImVec4(0.13f, 0.75f, 0.55f, 0.80f);
    colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.13f, 0.13f, 0.13f, 0.80f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
    colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
    colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
    colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.07f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}

void EditorLayer::OnDetach() {
}

void EditorLayer::OnUpdate(Timestep ts) {
    if (m_Framebuffer->GetSpecification().Height != m_ViewportSize.y and
        m_Framebuffer->GetSpecification().Width != m_ViewportSize.x) {
        m_Framebuffer->Resize(m_ViewportSize.x, m_ViewportSize.y);
//        m_cameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
        m_scene.OnViewportResize((uint32_t) m_ViewportSize.x, (uint32_t) m_ViewportSize.y);
    }

//    m_cameraController.OnUpdate(ts);
    m_Framebuffer->Bind();

    RenderCommand::SetClearColor({0.31, 0.34, 0.34, 1});
    RenderCommand::Clear();

    Renderer2D::ResetStats();
    m_scene.OnUpdate(ts);

    m_Framebuffer->Unbind();
}

void EditorLayer::OnImGuiRender() {

    static bool dockspaceOpen = true;
    static bool opt_fullscreen_persistant = true;
    bool opt_fullscreen = opt_fullscreen_persistant;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen) {
        ImGuiViewport *viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                        ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    if (ImGui::Begin("Blobfish Editor Dockspace", &dockspaceOpen, window_flags)) {
        ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // DockSpace
        ImGuiIO &io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
            ImGuiID dockspace_id = ImGui::GetID("Dockspace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                // Disabling fullscreen would allow the window to be moved to the front of other windows,
                // which we can't undo at the moment without finer window depth/z control.
                //ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);
                if (ImGui::MenuItem("Exit")) {
                    auto e = WindowCloseEvent();
                    Application::getInstance()->EmitEvent(e);
                }
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        DisplayDrawStatsWindow();

        DisplayEntityEditorWindow();

        DisplayViewport();
    }
}

void EditorLayer::DisplayViewport() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    if (ImGui::Begin("Viewport")) {

        ImVec2 size{ImGui::GetContentRegionAvail()};
        glm::vec2 size_ = {size.x, size.y};
        m_ViewportSize = size_;

        uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();

        ImGui::Image((ImTextureID) (intptr_t) textureID, ImVec2{m_ViewportSize.x, m_ViewportSize.y}, ImVec2(0, 1),
                     ImVec2(1, 0));
        ImGui::End();
        ImGui::PopStyleVar();
    }
    ImGui::End();
}

void EditorLayer::DisplayEntityEditorWindow() {
    if (ImGui::Begin("Entities")) {
        // Deselect if clicked on empty space
        if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
            m_SelectedEntity = {};

        m_scene.GetRegistry().each([&](auto entityID) {
            Entity e(entityID, &m_scene);
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
                            m_SelectedEntity.GetComponent<CameraComponent>().Camera.SetViewportSize(
                                    (uint32_t) m_ViewportSize.x, (uint32_t) m_ViewportSize.y);
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
                    m_scene.DestroyEntity(m_SelectedEntity);
                    m_SelectedEntity = {};
                    ImGui::PopStyleColor(3);
                } else {
                    ImGui::PopStyleColor(3);

                    // functions for displaying ui for all components
                    auto displayTagComponent = [&]() {
                        auto &tag = m_SelectedEntity.GetComponent<TagComponent>().Tag;
                        char buffer[256];
                        memset(buffer, 0, sizeof(buffer));
                        std::strncpy(buffer, tag.c_str(), sizeof(buffer));
                        if (ImGui::InputText("##Tag", buffer, sizeof(buffer))) {
                            tag = std::string(buffer);
                        }
                    };
                    auto displayTransformComponent = [&]() {
                        auto &transformComponent = m_SelectedEntity.GetComponent<TransformComponent>();
                        ImGui::SliderFloat3("Position", glm::value_ptr(transformComponent.Position), -1.0f,
                                            1.0f);
                        ImGui::SliderAngle("Rotation",
                                           &transformComponent.Rotation);
                        ImGui::SliderFloat2("Scale", glm::value_ptr(transformComponent.Scale), -2.0f, 2.0f);
                    };
                    auto displaySpriteRendererComponent = [&]() {
                        auto &component = m_SelectedEntity.GetComponent<SpriteRendererComponent>();
                        ImGui::Text("Texture: ");
                        ImGui::SameLine();
                        if (component.Texture) {
                            ImGui::Image((ImTextureID) (intptr_t) component.Texture->GetRendererID(), ImVec2(64, 64),
                                         ImVec2(0, 1),
                                         ImVec2(1, 0));
                            ImGui::SliderFloat("Tiling factor", &component.TilingFactor, 1.0f, 10.0f);
                            ImGui::ColorEdit4("Tint Color", glm::value_ptr(component.Color));
                        } else {
                            ImGui::Text("None");
                            ImGui::Text("Tiling factor: None");
                            ImGui::ColorEdit4("Color", glm::value_ptr(component.Color));
                        }
                    };
                    auto displayCameraComponent = [&]() {
                        auto &component = m_SelectedEntity.GetComponent<CameraComponent>();
                        ImGui::Checkbox("Primary", &component.Primary);
                        float orthoSize = component.Camera.GetOrthographicSize();
                        if (ImGui::DragFloat("Orthographic Size", &orthoSize))
                            component.Camera.SetOrthographicSize(orthoSize);
                    };
                    // Display components if they exist
                    ImGui::SameLine();
                    displayTagComponent(); // except for TagComponent which is always exist
                    DisplayComponent<TransformComponent>(displayTransformComponent, "TransformComponent");
                    DisplayComponent<SpriteRendererComponent>(displaySpriteRendererComponent,
                                                              "SpriteRendererComponent");
                    DisplayComponent<CameraComponent>(displayCameraComponent,
                                                      "CameraComponent");
                }
            } else {
                // If no entity selected
                ImGui::Text("Click on entity in the 'Entities' menu to see/edit it's components");
                ImGui::Text("Or ");
                ImGui::SameLine();
                if (ImGui::Button("Create new entity")) {
                    m_scene.CreateEntity();
                }
            }
            ImGui::End();
        } else
            ImGui::End();

        // Right mouse button click response
        if (ImGui::BeginPopupContextWindow(nullptr, 1, false)) {
            if (ImGui::MenuItem("Add entity")) {
                m_scene.CreateEntity();
            }
            ImGui::EndPopup();
        }

    }
    ImGui::End();
}

void EditorLayer::DisplayDrawStatsWindow() const {
    if (ImGui::Begin("Renderer2D Stats")) {
        ImGui::Text("FPS %.2f", ImGui::GetIO().Framerate);
        ImGui::NewLine();
        auto stats = Renderer2D::GetStats();
        ImGui::Text("Draw Calls: %d", stats.DrawCalls);
        ImGui::Text("Quads: %d", stats.QuadCount);
        ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
        ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
        ImGui::NewLine();

    }
    ImGui::End();
}

EditorLayer::EditorLayer() {

}

template<class T, class F>
bool EditorLayer::DisplayComponent(F UIfunction, const char *title) {
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

