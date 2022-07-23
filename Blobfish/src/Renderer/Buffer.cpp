#include "Buffer.h"
#include <Platform/OpenGL/BufferOpenGl.h>

namespace bf {
    VertexBuffer *VertexBuffer::Create(float *vertices, unsigned int size) {
        ZoneScoped;
        return new VertexBufferOpenGL(vertices, size);
    }

    IndexBuffer *IndexBuffer::Create(unsigned int *indices, unsigned int count) {
        ZoneScoped;
        return new IndexBufferOpenGL(indices, count);
    }
} // bf