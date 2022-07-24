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

    Shader *Shader::Create(const std::string &filepath) {
        //TODO: use smart pointers
        auto [vertexSrc, fragmentSrc] = ReadFile(filepath);
        switch (Renderer::getAPI()) {
            case RendererAPI::API::None:
                BF_ASSERT(false, "RendererAPI::API::None is currently not supported!")
            case RendererAPI::API::OpenGL:
                return new ShaderOpenGL(NameFromFile(filepath), vertexSrc, fragmentSrc);
        }
        BF_ASSERT(false, "Unknown RendererAPI!");
    }

    std::string Shader::NameFromFile(const std::string &filepath) {
        auto lastSlash = filepath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        auto lastDot = filepath.rfind('.');
        auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
        auto name = filepath.substr(lastSlash, count);
        return name;
    }

    void ShaderLibrary::Add(const std::string &name, Shader *shader) {
        BF_ASSERT(not Exists(name), "Shader '{0}' already exists", name);
        m_Shaders[name] = shader;
    }

    void ShaderLibrary::Add(Shader *shader) {
        Add(shader->GetName(), shader);
    }

    Shader *ShaderLibrary::Load(const std::string &filepath) {
        auto shader = Shader::Create(filepath);
        Add(shader);
        return shader;
    }

    Shader *ShaderLibrary::Load(const std::string &name, const std::string &filepath) {
        auto shader = Shader::Create(name, filepath);
        Add(shader);
        return shader;
    }

    Shader *ShaderLibrary::Get(const std::string &name) {
        BF_ASSERT(Exists(name), "Shader '{0}' does not exist", name);
        return m_Shaders[name];
    }

    bool ShaderLibrary::Exists(const std::string &name) const {
        return m_Shaders.find(name) != m_Shaders.end();
    }
} // bf