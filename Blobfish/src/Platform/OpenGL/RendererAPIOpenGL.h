#ifndef RENDERERAPIOPENGL_H
#define RENDERERAPIOPENGL_H

#include <Renderer/RendererAPI.h>

namespace bf {

    class RendererAPIOpenGL: public RendererAPI{
    public:
        void Init() override;

        void Clear() override;

        void SetClearColor(const glm::vec4 &color) override;

        void DrawIndexed(VertexArray *vertexArray, uint32_t count = 0) override;

        void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) override;
    };

} // bf

#endif //RENDERERAPIOPENGL_H
