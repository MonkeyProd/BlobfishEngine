#include "Sandbox2D_test.h"

using namespace bf;

void Sandbox2D::OnAttach() {
    m_apples = Texture2D::Create("../../Sandbox/assets/apples.png");
    m_apple_pos = {0.0f, 0.3f, 0.0f};

    m_RPGTileset = Texture2D::Create("../../Sandbox/assets/RPG_Urban_Pack.png");
    for (int i = 0; i < 6; ++i) {
        m_LightSprites[i] = SubTexture2D::CreateFromCoordinates(m_RPGTileset, {2 + i, 10}, {16, 16}, {1, 2});
    }
}

void Sandbox2D::OnDetach() {

}

void Sandbox2D::OnUpdate(Timestep ts) {
    m_cameraController.OnUpdate(ts);

    RenderCommand::SetClearColor({0.31, 0.34, 0.34, 1});
    RenderCommand::Clear();

    Renderer2D::ResetStats();
    Renderer2D::BeginScene(m_cameraController.GetCamera());

    Renderer2D::DrawQuad({0.5f, 0.0f}, {3.0f, 0.5f}, {0.5f, 0.5f, 1.0f, 1.0f});

    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            glm::vec2 p = {i * 0.05f, j * 0.05f};
            glm::vec2 s = {0.025f, 0.025f};
            glm::vec4 c = {i * sin(Time::GetTime()) / 100.0f, j * cos(Time::GetTime()) / 100.0f, 1.0f, 1.0f};
            Renderer2D::DrawQuad(p, s, c);
        }
    }
    Renderer2D::DrawQuad(m_apple_pos, {1.0f, 0.5f}, m_apples);
    for (int i = 0; i < 6; ++i) {
        Renderer2D::DrawQuad({-1.0f + i, -1.0f}, {0.5f, 1.0f}, m_LightSprites[i]);
    }

    Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender() {
    ImGui::SliderFloat3("apple pos", glm::value_ptr(m_apple_pos), -5.0f, 5.0f);
    ImGui::NewLine();
    auto stats = Renderer2D::GetStats();
    ImGui::Text("Renderer2D Stats:");
    ImGui::Text("Draw Calls: %d", stats.DrawCalls);
    ImGui::Text("Quads: %d", stats.QuadCount);
    ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
    ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
    ImGui::NewLine();
//    ImGui::ShowMetricsWindow();
}

void Sandbox2D::OnEvent(Event &event) {
    m_cameraController.OnEvent(event);
}

Sandbox2D::Sandbox2D() : m_cameraController(1.0f, true) {

}