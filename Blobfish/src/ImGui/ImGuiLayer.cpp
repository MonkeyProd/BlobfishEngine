#include "ImGuiLayer.h"
#include <GLFW/glfw3.h>
#include <imgui.h>

#include "../Core/Application.h"
#include <Tracy.hpp>

namespace bf {
    void ImGuiLayer::OnAttach() {
        ZoneScoped;
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL((GLFWwindow *) Application::getInstance()->getWindow().GetNativeWindow(), true);
        ImGui_ImplOpenGL3_Init("#version 330");
        BF_LOG_DEBUG("LAYER '{0}' ATTACHED SUCCESSFULLY", GetName());
    }

    void ImGuiLayer::OnDetach() {
        ZoneScoped;
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::OnUpdate(Timestep ts) {
        ZoneScoped;

    }

    void ImGuiLayer::OnImGuiRender() {
        ZoneScoped;
        static bool show = true;
        ImGui::ShowDemoWindow(&show);
    }

    ImGuiLayer::ImGuiLayer() : Layer("ImGui Layer") {
    }

    void ImGuiLayer::Begin() {
        ZoneScoped;
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::End() {
        ZoneScoped;
        ImGuiIO &io = ImGui::GetIO();
        Application &app = *Application::getInstance();
        io.DisplaySize = ImVec2(app.getWindow().GetWidth(), app.getWindow().GetHeight());

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
} // Blobfish