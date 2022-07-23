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

        virtual void setUniformMat4(const std::string& name, const glm::mat4 &matrix) = 0;
        virtual void setUniformInt(const std::string& name, const int &uniform) = 0;


        static Shader *Create(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc);
        static Shader *Create(const std::string &name, const std::string &filepath);
    private:
        struct ShaderSource{
            std::string VertexSource;
            std::string FragmentSource;
        };
        static ShaderSource ReadFile(const std::string &filepath);
    };

} // bf

#endif //SHADER_H
