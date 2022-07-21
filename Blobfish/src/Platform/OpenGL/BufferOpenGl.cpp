//
// Created by plasm on 19.07.2022.
//

#include "BufferOpenGl.h"

namespace bf {
    VertexBufferOpenGL::VertexBufferOpenGL(float *vertices, unsigned int size) {
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    void VertexBufferOpenGL::bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
    }

    void VertexBufferOpenGL::unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    const BufferLayout &VertexBufferOpenGL::GetLayout() const {
        return m_layout;
    }

    void VertexBufferOpenGL::SetLayout(const BufferLayout &layout) {
        m_layout = layout;
    }

    IndexBufferOpenGL::IndexBufferOpenGL(unsigned int *indices, unsigned int count) {
        m_count = count;
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    }

    void IndexBufferOpenGL::bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    }

    void IndexBufferOpenGL::unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
} // bf