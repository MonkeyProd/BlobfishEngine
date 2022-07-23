#ifndef RENDERERAPI_H
#define RENDERERAPI_H

#include <glm/glm.hpp>
#include <Renderer/VertexArray.h>

namespace bf {
    class RendererAPI {
    public:
        enum class API {
            None = 0, OpenGL
        };
    public:
        virtual void Init() = 0;

        virtual void Clear() = 0;

        virtual void SetClearColor(const glm::vec4 &color) = 0;

        virtual void DrawIndexed(VertexArray *vertexArray) = 0;

        virtual void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) = 0;

        inline static API getAPI() { return s_API; }

    private:
        static API s_API;
    };
}

#endif //RENDERERAPI_H
