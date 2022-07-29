#ifndef SHADER_H
#define SHADER_H

#include <Core/BlobPCH.h>
#include <glm/glm.hpp>

namespace bf {

    class Shader {
    public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;

        virtual void Unbind() const = 0;

        virtual void setUniform1f(std::string name, float uniform) = 0;

        virtual void setUniform3f(std::string name, float *uniform) = 0;

        virtual void setUniform4f(std::string name, float *uniform) = 0;

        virtual void setUniform3f(std::string name, const glm::vec3 &uniform) = 0;

        virtual void setUniform4f(std::string name, const glm::vec4 &uniform) = 0;

        virtual void setUniformMat4(const std::string &name, const glm::mat4 &matrix) = 0;

        virtual void setUniformInt(const std::string &name, const int &uniform) = 0;

        virtual void setUniformIntArray(const std::string &name, const int *arr, int count) = 0;

        virtual const std::string &GetName() const = 0;

        static Shader *Create(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc);

        static Shader *Create(const std::string &name, const std::string &filepath);

        static Shader *Create(const std::string &filepath);

    private:
        struct ShaderSource {
            std::string VertexSource;
            std::string FragmentSource;
        };

        static ShaderSource ReadFile(const std::string &filepath);

        static std::string NameFromFile(const std::string &filepath);
    };


    // TODO use smart pointers
    class ShaderLibrary {
    public:
        void Add(const std::string &name, Shader *shader);

        void Add(Shader *shader);

        Shader *Load(const std::string &filepath);

        Shader *Load(const std::string &name, const std::string &filepath);

        Shader *Get(const std::string &name);

        bool Exists(const std::string &name) const;

    private:
        std::unordered_map<std::string, Shader *> m_Shaders;
    };
} // bf

#endif //SHADER_H
