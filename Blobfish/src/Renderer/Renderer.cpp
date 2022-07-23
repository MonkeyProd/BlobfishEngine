#include "Renderer.h"

namespace bf {
    Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

    void Renderer::BeginScene(OrthographicCamera &camera) {
        ZoneScoped;
        s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene() {
        ZoneScoped;
    }

    void Renderer::Submit(VertexArray *vertexArray, Shader *shader, glm::mat4& Transform, Texture *texture) {
        ZoneScoped;
        texture->Bind();
        shader->Bind();
        shader->setUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
        shader->setUniformMat4("u_Transform", Transform);
        shader->setUniformInt("u_Texture", 0);
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

    void Renderer::OnWindowResize(unsigned int width, unsigned int height) {
        RenderCommand::SetViewport(0, 0, width, height);
    }

    void Renderer::Init() {
        RenderCommand::Init();
    }
} // bf