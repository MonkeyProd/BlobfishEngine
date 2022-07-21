//
// Created by user on 19.07.2022.
//

#ifndef COMPOUND_VERTEXARRAYOPENGL_H
#define COMPOUND_VERTEXARRAYOPENGL_H

#include <Renderer/VertexArray.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace bf {

    class VertexArrayOpenGL : public VertexArray {
    public:
        VertexArrayOpenGL();

        ~VertexArrayOpenGL() override = default;

        void Bind() const override;

        void Unbind() const override;

        void AddVertexBuffer(VertexBuffer *vertexBuffer) override;

        void SetIndexBuffer(IndexBuffer *indexBuffer) override;

        const std::vector<VertexBuffer *> &GetVertexBuffers() const override;

        const IndexBuffer *GetIndexBuffer() const override;

    private:
        unsigned int m_id=0;
        unsigned int m_index = 0;
        std::vector<VertexBuffer *> m_vertexBuffers;
        IndexBuffer *m_indexBuffer;
    };

} // bf

#endif //COMPOUND_VERTEXARRAYOPENGL_H
