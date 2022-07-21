//
// Created by plasm on 19.07.2022.
//

#ifndef COMPOUND_BUFFER_H
#define COMPOUND_BUFFER_H

#include <Core/BlobPCH.h>

namespace bf {
    enum class ShaderDataType {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    static unsigned int ShaderDataTypeSize(ShaderDataType type) {
        ZoneScoped;
        switch (type) {
            case ShaderDataType::Float:
                return 4;
            case ShaderDataType::Float2:
                return 4 * 2;
            case ShaderDataType::Float3:
                return 4 * 3;
            case ShaderDataType::Float4:
                return 4 * 4;
            case ShaderDataType::Mat3:
                return 4 * 3 * 3;
            case ShaderDataType::Mat4:
                return 4 * 4 * 4;
            case ShaderDataType::Int:
                return 4;
            case ShaderDataType::Int2:
                return 4 * 2;
            case ShaderDataType::Int3:
                return 4 * 3;
            case ShaderDataType::Int4:
                return 4 * 4;
            case ShaderDataType::Bool:
                return 1;
        }

        BF_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    struct BufferElement {
        std::string Name;
        ShaderDataType Type;
        uint32_t Size;
        size_t Offset;
        bool Normalized;

        BufferElement() = default;

        BufferElement(ShaderDataType type, const std::string &name, bool normalized = false)
                : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized) {
        }

        uint32_t GetComponentCount() const {
            ZoneScoped;
            switch (Type) {
                case ShaderDataType::Float:
                    return 1;
                case ShaderDataType::Float2:
                    return 2;
                case ShaderDataType::Float3:
                    return 3;
                case ShaderDataType::Float4:
                    return 4;
                case ShaderDataType::Mat3:
                    return 3; // 3* float3
                case ShaderDataType::Mat4:
                    return 4; // 4* float4
                case ShaderDataType::Int:
                    return 1;
                case ShaderDataType::Int2:
                    return 2;
                case ShaderDataType::Int3:
                    return 3;
                case ShaderDataType::Int4:
                    return 4;
                case ShaderDataType::Bool:
                    return 1;
            }

            BF_ASSERT(false, "Unknown ShaderDataType!");
            return 0;
        }
    };

    class BufferLayout {
    public:
        BufferLayout() {}

        BufferLayout(std::initializer_list<BufferElement> elements)
                : m_Elements(elements) {
            CalculateOffsetsAndStride();
        }

        unsigned int GetStride() const { return m_Stride; }

        const std::vector<BufferElement> &GetElements() const { return m_Elements; }

        std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }

        std::vector<BufferElement>::iterator end() { return m_Elements.end(); }

        std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }

        std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

    private:
        void CalculateOffsetsAndStride() {
            ZoneScoped;
            size_t offset = 0;
            m_Stride = 0;
            for (auto &element: m_Elements) {
                element.Offset = offset;
                offset += element.Size;
                m_Stride += element.Size;
            }
        }

    private:
        std::vector<BufferElement> m_Elements;
        unsigned int m_Stride = 0;
    };


    class VertexBuffer {
    public:
        virtual ~VertexBuffer() = default;

        virtual void bind() const = 0;

        virtual void unbind() const = 0;

        static VertexBuffer *Create(float *vertices, unsigned int size);

        virtual const BufferLayout &GetLayout() const = 0;

        virtual void SetLayout(const BufferLayout &layout) = 0;
    };

    class IndexBuffer {
    protected:
        unsigned int m_count;
    public:
        virtual ~IndexBuffer() = default;

        virtual void bind() const = 0;

        virtual void unbind() const = 0;

        static IndexBuffer *Create(unsigned int *indices, unsigned int count);

        unsigned int GetCount() const { return m_count; }
    };

} // bf

#endif //COMPOUND_BUFFER_H
