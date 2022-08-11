#include "EditorLayer.h"
#include "EntityEditor.h"
#include <glm/gtc/type_ptr.hpp>

// todo remove this
#include <glm/gtx/compatibility.hpp>

class Apples : public NativeScript {
    float speed = 1.0f;
public:
    void OnUpdate(Timestep ts) override {
        auto &transform = GetComponent<TransformComponent>();
        if (Input::IsKeyPressed(Key::W))
            transform.Position.y += ts * speed;
        if (Input::IsKeyPressed(Key::A))
            transform.Position.x -= ts * speed;
        if (Input::IsKeyPressed(Key::S))
            transform.Position.y -= ts * speed;
        if (Input::IsKeyPressed(Key::D))
            transform.Position.x += ts * speed;
    }

    void OnImGuiRender() override {
        ImGui::Text("hello im apple");
        ImGui::SliderFloat("speed", &speed, 0.0f, 10.0f);

    }
};


class CameraFollow : public NativeScript {
public:
    float smooth = 1.0f;

    void OnImGuiRender() override {
        ImGui::Text("hello from camera follow script");
        ImGui::SliderFloat("smooth", &smooth, 0.0f, 10.0f);
    }

    void OnUpdate(Timestep ts) override {
        auto apples = Find("apples");
        if (apples) {
            glm::vec3 &target = apples->GetComponent<TransformComponent>().Position;
            auto &pos = GetComponent<TransformComponent>().Position;
            pos = glm::lerp(pos, target, ts * smooth);
        }
    }
};

void EditorLayer::OnAttach() {
    m_apples = Texture2D::Create("../../Sandbox/assets/apples.png");
    m_Framebuffer = Framebuffer::Create({1280, 720});
    m_camera = new EditorCamera;

    ImGuiIO &io = ImGui::GetIO();
    float FontSize = 13;
    io.Fonts->AddFontFromFileTTF("../../Editor/Assets/Fonts/Ubuntu-Regular.ttf", FontSize);
    auto apples = m_scene.CreateEntity("apples");
    apples.AddComponent<SpriteRendererComponent>();
    apples.GetComponent<SpriteRendererComponent>().Texture = m_apples;
    apples.AddComponent<NativeScriptComponent>().Bind<Apples>();

    auto backgound = m_scene.CreateEntity("backgound");
    backgound.AddComponent<SpriteRendererComponent>();
    backgound.GetComponent<SpriteRendererComponent>().Texture = Texture2D::Create("../../Sandbox/assets/chessmate.jpg");
    backgound.GetComponent<TransformComponent>().Scale = glm::vec2{5.0f};

    auto camera = m_scene.CreateEntity("camera");
    camera.AddComponent<NativeScriptComponent>().Bind<CameraFollow>();

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
    BF_LOG_INFO("Detaching");
    delete m_camera;
}

void EditorLayer::OnUpdate(Timestep ts) {
    if (m_Framebuffer->GetSpecification().Height != m_ViewportSize.y or
        m_Framebuffer->GetSpecification().Width != m_ViewportSize.x) {
        m_Framebuffer->Resize(m_ViewportSize.x, m_ViewportSize.y);
//        m_cameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
        m_camera->SetViewportSize((uint32_t) m_ViewportSize.x, (uint32_t) m_ViewportSize.y);
        m_scene.OnViewportResize((uint32_t) m_ViewportSize.x, (uint32_t) m_ViewportSize.y);
    }

    m_camera->OnUpdate(ts, m_ViewportSize);
    m_Framebuffer->Bind();

    RenderCommand::SetClearColor({0.31, 0.34, 0.34, 1});
    RenderCommand::Clear();

    Renderer2D::ResetStats();
    if (running) {
        m_scene.OnUpdate(ts);
    } else {
        m_scene.OnUpdateEditor(ts, m_camera);
    }

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

        m_entityEditor.DisplayEntityEditorWindow(m_scene, m_ViewportSize);

        DisplayViewport();
    }
}

void EditorLayer::DisplayViewport() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    if (ImGui::Begin("Viewport")) {
        ImGui::SliderFloat("Font scale", &ImGui::GetIO().FontGlobalScale, 1.0f, 3.0f);
        ImGui::Checkbox("Running", &running);
        if (running) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(1.0f, 0.4f, 0.4f, 1.0f), "RUNNING");
        }
        ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "LeftAlt+RMB then drag mouse to move editor camera around");
        ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f),
                           "LeftAlt+LMB then drag mouse vertically to zoom editor camera");

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
//
//template<class T, class ReturnType, typename ...Args>
//static constexpr bool hasOnUpdate(T, ReturnType(Args...)) {
//    return std::is_same<decltype(std::declval<T>().OnUpdate(std::declval<Args>()...)), ReturnType>::value;
//}


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

