
#ifndef RENDERCOMMAND_H
#define RENDERCOMMAND_H

#include "RendererAPI.h"

namespace bf {

    class RenderCommand {
    public:
        static inline void Init(){
            s_RendererAPI->Init();
        }
        static inline void DrawIndexed(VertexArray *vertexArray){
            s_RendererAPI->DrawIndexed(vertexArray);
        }
        static inline void SetClearColor(const glm::vec4 &color){
            s_RendererAPI->SetClearColor(color);
        }
        static inline void Clear(){
            s_RendererAPI->Clear();
        }
        static inline void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
        {
            s_RendererAPI->SetViewport(x, y, width, height);
        }
    private:
        static RendererAPI* s_RendererAPI;
    };

} // bf

#endif //RENDERCOMMAND_H
