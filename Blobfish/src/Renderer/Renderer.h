//
// Created by plasm on 21.07.2022.
//

#ifndef COMPOUND_RENDERER_H
#define COMPOUND_RENDERER_H

#include "RenderCommand.h"
#include "Shader.h"
#include "OrthographicCamera.h"
#include "Texture.h"

namespace bf {

    class Renderer {
    public:
        static void Init();

        static void BeginScene(OrthographicCamera &camera);

        static void EndScene();

        static void Submit(VertexArray *vertexArray, Shader *shader, glm::mat4 &Transform, Texture *texture);

        static void OnWindowResize(unsigned int width, unsigned int height);

        inline static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }

    private:
        struct SceneData {
            glm::mat4 ViewProjectionMatrix;
        };
        static SceneData *s_SceneData;
    };

} // bf

#endif //COMPOUND_RENDERER_H
