//
// Created by user on 19.07.2022.
//

#include "VertexArray.h"
#include <Platform/OpenGL/VertexArrayOpenGL.h>

namespace bf {
    VertexArray *VertexArray::Create() {
        ZoneScoped;
        return new VertexArrayOpenGL;
    }
} // bf