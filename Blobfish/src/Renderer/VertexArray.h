//
// Created by user on 19.07.2022.
//

#ifndef COMPOUND_VERTEXARRAY_H
#define COMPOUND_VERTEXARRAY_H

#include "Buffer.h"
#include <Core/BlobPCH.h>

namespace bf {

    class VertexArray {
    public:
        virtual ~VertexArray() = default;

        virtual void Bind() const = 0;

        virtual void Unbind() const = 0;

        virtual void AddVertexBuffer(VertexBuffer *vertexBuffer) = 0;

        virtual void SetIndexBuffer(IndexBuffer *indexBuffer) = 0;

        virtual const std::vector<VertexBuffer*> &GetVertexBuffers() const = 0;

        virtual const IndexBuffer *GetIndexBuffer() const = 0;

        static VertexArray *Create();
    };

} // bf

#endif //COMPOUND_VERTEXARRAY_H
