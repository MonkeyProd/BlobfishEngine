//
// Created by plasm on 19.07.2022.
//

#ifndef COMPOUND_BUFFEROPENGL_H
#define COMPOUND_BUFFEROPENGL_H

#include <Renderer/Buffer.h>

#include <glad/glad.h>

namespace bf {

    class VertexBufferOpenGL : public VertexBuffer {
    public:
        VertexBufferOpenGL(float *vertices, unsigned int size);
        ~VertexBufferOpenGL() override = default;

        void bind() const override;

        void unbind() const override;
    private:
        unsigned int m_id;
    };

    class IndexBufferOpenGL : public IndexBuffer {
    public:
        IndexBufferOpenGL(unsigned int *indices, unsigned int count);
        ~IndexBufferOpenGL() override = default;

        void bind() const override;

        void unbind() const override;
    private:
        unsigned int m_id;
    };

} // bf

#endif //COMPOUND_BUFFEROPENGL_H
