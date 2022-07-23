//
// Created by plasm on 21.07.2022.
//

#ifndef COMPOUND_RENDERERAPIOPENGL_H
#define COMPOUND_RENDERERAPIOPENGL_H

#include <Renderer/RendererAPI.h>

namespace bf {

    class RendererAPIOpenGL: public RendererAPI{
    public:
        void Init() override;

        void Clear() override;

        void SetClearColor(const glm::vec4 &color) override;

        void DrawIndexed(VertexArray *vertexArray) override;

        void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) override;
    };

} // bf

#endif //COMPOUND_RENDERERAPIOPENGL_H
