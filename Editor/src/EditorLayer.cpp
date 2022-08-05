#include "EditorLayer.h"
#include <glm/gtc/type_ptr.hpp>

void EditorLayer::OnAttach() {
    m_apples = Texture2D::Create("../../Sandbox/assets/apples.png");
    m_apple_pos = {0.0f, 0.3f, 0.0f};
    m_Framebuffer = Framebuffer::Create({800, 600});

    ImGuiIO &io = ImGui::GetIO();
    float FontSize = 20;
    io.Fonts->AddFontFromFileTTF("../../Editor/Assets/Fonts/Ubuntu-Regular.ttf", FontSize);

    m_test_entity = m_scene.CreateEntity("test");
    m_test_entity.AddComponent<SpriteRendererComponent>(glm::vec4(1.0f, 0.3f, 0.7f, 1.0f));

    m_apples_entity = m_scene.CreateEntity("apples");
    m_apples_entity.AddComponent<SpriteRendererComponent>(glm::vec4(0.0f, 0.3f, 0.7f, 1.0f));
    m_apples_entity.GetComponent<SpriteRendererComponent>().Texture = m_apples;
    m_apples_entity.GetComponent<SpriteRendererComponent>().TilingFactor = 3;
    m_apples_entity.GetComponent<TransformComponent>().Position = m_apple_pos;
}

void EditorLayer::OnDetach() {

}

void EditorLayer::OnUpdate(Timestep ts) {
    if (m_Framebuffer->GetSpecification().Height != m_ViewportSize.y and
        m_Framebuffer->GetSpecification().Width != m_ViewportSize.x) {
        m_Framebuffer->Resize(m_ViewportSize.x, m_ViewportSize.y);
        m_cameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
    }

    m_cameraController.OnUpdate(ts);
    m_Framebuffer->Bind();

    RenderCommand::SetClearColor({0.31, 0.34, 0.34, 1});
    RenderCommand::Clear();

    Renderer2D::ResetStats();
    Renderer2D::BeginScene(m_cameraController.GetCamera());
    m_scene.OnUpdate(ts);
//    Renderer2D::DrawQuad({0.5f, 0.0f}, {3.0f, 0.5f}, {0.5f, 0.5f, 1.0f, 1.0f});
//    Renderer2D::DrawQuad(m_apple_pos, {1.0f, 0.5f}, m_apples);

    Renderer2D::EndScene();
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
    if (ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags)) {
        ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // DockSpace
        ImGuiIO &io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
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

        if (ImGui::Begin("Renderer2D Stats")) {
            ImGui::Text("FPS %.2f", ImGui::GetIO().Framerate);
            ImGui::SliderFloat3("apple pos", glm::value_ptr(m_apple_pos), -5.0f, 5.0f);
            m_apples_entity.GetComponent<TransformComponent>().Position = m_apple_pos;
            ImGui::NewLine();
            auto stats = Renderer2D::GetStats();
            ImGui::Text("Draw Calls: %d", stats.DrawCalls);
            ImGui::Text("Quads: %d", stats.QuadCount);
            ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
            ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
            ImGui::NewLine();
            ImGui::End();
        }

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        if (ImGui::Begin("Viewport")) {

            ImVec2 size{ImGui::GetContentRegionAvail()};
            glm::vec2 size_ = {size.x, size.y};
            m_ViewportSize = size_;

            uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();

            //FIXME cast: (ImTextureID) textureID throws warning 'cast to pointer from integer of different size [-Wint-to-pointer-cast]'
            ImGui::Image((ImTextureID) textureID, ImVec2{m_ViewportSize.x, m_ViewportSize.y}, ImVec2(0, 1),
                         ImVec2(1, 0));
            ImGui::End();
            ImGui::PopStyleVar();
        }
        ImGui::End();
    }
}

EditorLayer::EditorLayer() : m_cameraController(1.0f, true) {

}
