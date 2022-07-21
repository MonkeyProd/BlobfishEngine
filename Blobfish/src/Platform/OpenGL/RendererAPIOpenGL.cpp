//
// Created by plasm on 21.07.2022.
//

#include "RendererAPIOpenGL.h"

#include <glad/glad.h>

namespace bf {
    void RendererAPIOpenGL::Clear() {
        ZoneScoped;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RendererAPIOpenGL::SetClearColor(const glm::vec4 &color) {
        ZoneScoped;
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void RendererAPIOpenGL::DrawIndexed(VertexArray *vertexArray) {
        ZoneScoped;
        glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }
} // bf