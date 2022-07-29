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

    void RendererAPIOpenGL::DrawIndexed(VertexArray *vertexArray, uint32_t indexCount) {
        ZoneScoped;
        uint32_t count = indexCount ? vertexArray->GetIndexBuffer()->GetCount() : indexCount;
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void RendererAPIOpenGL::SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
        ZoneScoped;
        glViewport(x, y, width, height);
    }

    void RendererAPIOpenGL::Init() {
        ZoneScoped;
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
} // bf