#ifndef IMGUILAYER_H
#define IMGUILAYER_H

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

        void Begin();

        void End();
    };

} // Blobfish

#endif //IMGUILAYER_H
