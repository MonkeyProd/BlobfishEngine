#include "Shader.h"
#include <Platform/OpenGL/ShaderOpenGL.h>
#include <sstream>
#include <fstream>
#include <Renderer/Renderer.h>

namespace bf {
    Shader *Shader::Create(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc) {
        //TODO: use smart pointers
        ZoneScoped;
        switch (Renderer::getAPI()) {
            case RendererAPI::API::None:
                BF_ASSERT(false, "RendererAPI::API::None is currently not supported!")
            case RendererAPI::API::OpenGL:
                return new ShaderOpenGL(name, vertexSrc, fragmentSrc);
        }
        BF_ASSERT(false, "Unknown RendererAPI!");
    }

    Shader *Shader::Create(const std::string &name, const std::string &filepath) {
        //TODO: use smart pointers
        auto [vertexSrc, fragmentSrc] = ReadFile(filepath);
        switch (Renderer::getAPI()) {
            case RendererAPI::API::None:
                BF_ASSERT(false, "RendererAPI::API::None is currently not supported!")
            case RendererAPI::API::OpenGL:
                return new ShaderOpenGL(name, vertexSrc, fragmentSrc);
        }
        BF_ASSERT(false, "Unknown RendererAPI!");
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