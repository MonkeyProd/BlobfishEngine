#include "VertexArray.h"
#include <Platform/OpenGL/VertexArrayOpenGL.h>

namespace bf {
    VertexArray *VertexArray::Create() {
        ZoneScoped;
        return new VertexArrayOpenGL;
    }
} // bf