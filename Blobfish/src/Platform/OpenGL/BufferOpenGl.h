#ifndef BUFFEROPENGL_H
#define BUFFEROPENGL_H

#include <Renderer/Buffer.h>

#include <glad/glad.h>

namespace bf {

    class VertexBufferOpenGL : public VertexBuffer {
    public:
        VertexBufferOpenGL(float *vertices, unsigned int size);
        ~VertexBufferOpenGL() override = default;

        void bind() const override;

        void unbind() const override;

        const BufferLayout &GetLayout() const override;

        void SetLayout(const BufferLayout &layout) override;

    private:
        unsigned int m_id;
        BufferLayout m_layout;
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

#endif //BUFFEROPENGL_H
