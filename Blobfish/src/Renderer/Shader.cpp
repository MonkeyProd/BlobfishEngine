//
// Created by plasm on 16.07.2022.
//

#include "Shader.h"
#include <Platform/OpenGL/ShaderOpenGL.h>

namespace bf {
    Shader* Shader::Create(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc) {
        //TODO: API CHOOSE
        ZoneScoped;
        return new ShaderOpenGL(name, vertexSrc, fragmentSrc);
    }
} // bf