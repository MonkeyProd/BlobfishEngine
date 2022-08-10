#ifndef RENDERER_H
#define RENDERER_H

#include "RenderCommand.h"
#include "Shader.h"
#include "Texture.h"

namespace bf {

    class Renderer {
    public:
        static void Init();

        static void OnWindowResize(unsigned int width, unsigned int height);

        inline static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }

    private:
        struct SceneData {
            glm::mat4 ViewProjectionMatrix;
        };
        static SceneData *s_SceneData;
    };

} // bf

#endif //RENDERER_H
