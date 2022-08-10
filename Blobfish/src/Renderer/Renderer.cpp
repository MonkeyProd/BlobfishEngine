#include "Renderer.h"

namespace bf {
    Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

    void Renderer::OnWindowResize(unsigned int width, unsigned int height) {
        RenderCommand::SetViewport(0, 0, width, height);
    }

    void Renderer::Init() {
        RenderCommand::Init();
    }
} // bf