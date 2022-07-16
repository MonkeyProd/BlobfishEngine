//
// Created by plasm on 15.07.2022.
//

#ifndef COMPOUND_IMGUILAYER_H
#define COMPOUND_IMGUILAYER_H

#include "../Core/Layer.h"
#include "../Platform/OpenGL/ImGuiOpenGL.h"
#include "../Platform/OpenGL/ImGuiGLFW.h"

namespace bf {

    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer();

        ~ImGuiLayer() override = default;

        void OnAttach() override;

        void OnDetach() override;

        void OnUpdate(Timestep ts) override;

        void OnImGuiRender() override;

        void OnEvent(Event &event) override;

        void Begin();

        void End();
    };

} // Blobfish

#endif //COMPOUND_IMGUILAYER_H
