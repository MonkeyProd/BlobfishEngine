#ifndef COMPOUND_RENDERER2D_H
#define COMPOUND_RENDERER2D_H

#include "OrthographicCamera.h"
#include "Texture.h"
#include "SubTexture2D.h"
#include "Shader.h"
#include "VertexArray.h"
#include "RenderCommand.h"
#include "Camera.h"
#include <glm/glm.hpp>

namespace bf {

    class Renderer2D {
    public:
        static void Init();
        static void Shutdown();

        static void BeginScene(const Camera& camera, const glm::mat4& transform);
        static void EndScene();
        static void Flush();

        // Primitives
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, Texture2D *texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, Texture2D *texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, SubTexture2D *texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, SubTexture2D *texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

        static void DrawQuad(const glm::mat4 &transform, const glm::vec4 &color);
        static void DrawQuad(const glm::mat4 &transform, Texture2D *texture, float tilingFactor = 1.0f,
                             const glm::vec4 &tintColor = glm::vec4(1.0f));
        static void DrawQuad(const glm::mat4 &transform, SubTexture2D *texture, float tilingFactor = 1.0f,
                             const glm::vec4 &tintColor = glm::vec4(1.0f));

        static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
        static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
        static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, Texture2D *texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
        static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, Texture2D *texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
        static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, SubTexture2D *texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
        static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, SubTexture2D *texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));


        struct Statistics
        {
            uint32_t DrawCalls = 0;
            uint32_t QuadCount = 0;

            uint32_t GetTotalVertexCount() const { return QuadCount * 4; }
            uint32_t GetTotalIndexCount() const { return QuadCount * 6; }
        };
        static void ResetStats();
        static Statistics GetStats();
    private:
        static void FlushAndReset();
    };

} // bf

#endif //COMPOUND_RENDERER2D_H
