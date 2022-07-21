//
// Created by user on 19.07.2022.
//

#include "VertexArrayOpenGL.h"

namespace bf {

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        ZoneScoped;
        switch (type)
        {
            case ShaderDataType::Float:    return GL_FLOAT;
            case ShaderDataType::Float2:   return GL_FLOAT;
            case ShaderDataType::Float3:   return GL_FLOAT;
            case ShaderDataType::Float4:   return GL_FLOAT;
            case ShaderDataType::Mat3:     return GL_FLOAT;
            case ShaderDataType::Mat4:     return GL_FLOAT;
            case ShaderDataType::Int:      return GL_INT;
            case ShaderDataType::Int2:     return GL_INT;
            case ShaderDataType::Int3:     return GL_INT;
            case ShaderDataType::Int4:     return GL_INT;
            case ShaderDataType::Bool:     return GL_BOOL;
        }

        BF_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    VertexArrayOpenGL::VertexArrayOpenGL() {
        ZoneScoped;
        glGenVertexArrays(1, &m_id);
    }

    void VertexArrayOpenGL::Bind() const {
        ZoneScoped;
        glBindVertexArray(m_id);
    }

    void VertexArrayOpenGL::Unbind() const {
        ZoneScoped;
        glBindVertexArray(0);
    }

    void VertexArrayOpenGL::AddVertexBuffer(VertexBuffer *vertexBuffer) {
        ZoneScoped;
        BF_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout");
        glBindVertexArray(m_id);
        vertexBuffer->bind();

        const auto &layout = vertexBuffer->GetLayout();
        const auto &layout_elements = vertexBuffer->GetLayout().GetElements();
        for (const auto &element: layout_elements) {
            switch (element.Type) {
                case ShaderDataType::Float:
                case ShaderDataType::Float2:
                case ShaderDataType::Float3:
                case ShaderDataType::Float4: {
                    glEnableVertexAttribArray(m_index);
                    glVertexAttribPointer(m_index,
                                          element.GetComponentCount(),
                                          ShaderDataTypeToOpenGLBaseType(element.Type),
                                          element.Normalized ? GL_TRUE : GL_FALSE,
                                          layout.GetStride(),
                                          (const void *) element.Offset);
                    m_index++;
                    break;
                }
                case ShaderDataType::Int:
                case ShaderDataType::Int2:
                case ShaderDataType::Int3:
                case ShaderDataType::Int4:
                case ShaderDataType::Bool: {
                    glEnableVertexAttribArray(m_index);
                    glVertexAttribIPointer(m_index,
                                           element.GetComponentCount(),
                                           ShaderDataTypeToOpenGLBaseType(element.Type),
                                           layout.GetStride(),
                                           (const void *) element.Offset);
                    m_index++;
                    break;
                }
                case ShaderDataType::Mat3:
                case ShaderDataType::Mat4: {
                    uint8_t count = element.GetComponentCount();
                    for (uint8_t i = 0; i < count; i++) {
                        glEnableVertexAttribArray(m_index);
                        glVertexAttribPointer(m_index,
                                              count,
                                              ShaderDataTypeToOpenGLBaseType(element.Type),
                                              element.Normalized ? GL_TRUE : GL_FALSE,
                                              layout.GetStride(),
                                              (const void *) (element.Offset + sizeof(float) * count * i));
                        glVertexAttribDivisor(m_index, 1);
                        m_index++;
                    }
                    break;
                }
                default:
                    BF_ASSERT(false, "Unknown ShaderDataType!");
            }
        }
        m_vertexBuffers.push_back(vertexBuffer);
    }

    void VertexArrayOpenGL::SetIndexBuffer(IndexBuffer *indexBuffer) {
        ZoneScoped;
        glBindVertexArray(m_id);
        indexBuffer->bind();
        m_indexBuffer = indexBuffer;
    }

    const std::vector<VertexBuffer*> &VertexArrayOpenGL::GetVertexBuffers() const {
        ZoneScoped;
        return m_vertexBuffers;
    }

    const IndexBuffer *VertexArrayOpenGL::GetIndexBuffer() const {
        ZoneScoped;
        return m_indexBuffer;
    }

} // bf