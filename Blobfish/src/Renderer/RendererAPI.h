//
// Created by plasm on 21.07.2022.
//

#ifndef COMPOUND_RENDERERAPI_H
#define COMPOUND_RENDERERAPI_H

#include <glm/glm.hpp>
#include <Renderer/VertexArray.h>

namespace bf {
    class RendererAPI {
    public:
        enum class API {
            None = 0, OpenGL
        };
    public:
        virtual void Clear() = 0;

        virtual void SetClearColor(const glm::vec4 &color) = 0;

        virtual void DrawIndexed(VertexArray *vertexArray) = 0;

        inline static API getAPI() { return s_API; }

    private:
        static API s_API;
    };
}

#endif //COMPOUND_RENDERERAPI_H
