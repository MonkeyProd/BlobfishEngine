//
// Created by plasm on 21.07.2022.
//

#include "RenderCommand.h"

#include <Platform/OpenGL/RendererAPIOpenGL.h>

namespace bf {
    RendererAPI* RenderCommand::s_RendererAPI = new RendererAPIOpenGL;
} // bf