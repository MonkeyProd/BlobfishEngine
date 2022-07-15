//
// Created by plasm on 15.07.2022.
//

#ifndef COMPOUND_IMGUILAYER_H
#define COMPOUND_IMGUILAYER_H

#include "../Core/Layer.h"
#include "../Platform/OpenGL/ImGuiOpenGL.h"
#include <GLFW/glfw3.h>
#include "../Platform/OpenGL/ImGuiGLFW.h"

namespace Blobfish {

    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer();

        ~ImGuiLayer() override = default;

        void OnAttach() override;

        void OnDetach() override;

        void OnUpdate(Timestep ts) override;

        void OnImGuiRender() override;

        void OnEvent(Event &event) override;

        static ImGuiKey ImGui_ImplGlfw_KeyToImGuiKey(int key); //TODO: our own keymap
    };

} // Blobfish

#endif //COMPOUND_IMGUILAYER_H
