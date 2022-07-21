
//
// Created by plasm on 21.07.2022.
//

#ifndef COMPOUND_RENDERCOMMAND_H
#define COMPOUND_RENDERCOMMAND_H

#include "RendererAPI.h"

namespace bf {

    class RenderCommand {
    public:
        static inline void DrawIndexed(VertexArray *vertexArray){
            s_RendererAPI->DrawIndexed(vertexArray);
        }
        static inline void SetClearColor(const glm::vec4 &color){
            s_RendererAPI->SetClearColor(color);
        }
        static inline void Clear(){
            s_RendererAPI->Clear();
        }
    private:
        static RendererAPI* s_RendererAPI;
    };

} // bf

#endif //COMPOUND_RENDERCOMMAND_H
