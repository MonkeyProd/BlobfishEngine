//
// Created by plasm on 19.07.2022.
//

#include "Buffer.h"
#include <Platform/OpenGL/BufferOpenGl.h>

namespace bf {
    VertexBuffer *VertexBuffer::Create(float *vertices, unsigned int size) {
        return new VertexBufferOpenGL(vertices, size);
    }

    IndexBuffer *IndexBuffer::Create(unsigned int *indices, unsigned int count) {
        return new IndexBufferOpenGL(indices, count);
    }
} // bf