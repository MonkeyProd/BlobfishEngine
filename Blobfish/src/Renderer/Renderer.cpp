//
// Created by plasm on 21.07.2022.
//

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

    void Renderer::Submit(VertexArray *vertexArray, Shader *shader) {
        ZoneScoped;
        shader->Bind();
        shader->setUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
} // bf