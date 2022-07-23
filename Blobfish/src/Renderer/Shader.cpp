#include "Shader.h"
#include <Platform/OpenGL/ShaderOpenGL.h>
#include <sstream>
#include <fstream>

namespace bf {
    Shader *Shader::Create(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc) {
        //TODO: API CHOOSE
        ZoneScoped;
        return new ShaderOpenGL(name, vertexSrc, fragmentSrc);
    }

    Shader *Shader::Create(const std::string &name, const std::string &filepath) {
        auto [vertexSrc, fragmentSrc] = ReadFile(filepath);
        return new ShaderOpenGL(name, vertexSrc, fragmentSrc);
    }

    Shader::ShaderSource Shader::ReadFile(const std::string &filepath) {
        std::stringstream src[2];
        int flag = -1;
        std::ifstream file(filepath);
        std::string line;
        while (std::getline(file, line)) {
            if (line.find("#type") != std::string::npos) {
                if (line.find("vertex") != std::string::npos) {
                    flag = 0;
                } else if (line.find("fragment") != std::string::npos) {
                    flag = 1;
                }
            } else {
                src[flag] << line + '\n';
            }
        }
        return {src[0].str(), src[1].str()};
    }
} // bf