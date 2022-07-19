//
// Created by plasm on 19.07.2022.
//

#ifndef COMPOUND_BUFFER_H
#define COMPOUND_BUFFER_H

namespace bf {

    class VertexBuffer {
    public:
        virtual ~VertexBuffer() = default;
        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        static VertexBuffer* Create(float *vertices, unsigned int size);
    };

    class IndexBuffer {
    public:
        virtual ~IndexBuffer() = default;
        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        static IndexBuffer* Create(unsigned int *indices, unsigned int count);
    };

} // bf

#endif //COMPOUND_BUFFER_H
