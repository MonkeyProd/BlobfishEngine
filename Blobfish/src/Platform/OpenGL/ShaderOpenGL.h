//
// Created by plasm on 16.07.2022.
//

#ifndef COMPOUND_SHADEROPENGL_H
#define COMPOUND_SHADEROPENGL_H

#include <Renderer/Shader.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Core/BlobPCH.h>

namespace bf {

    class ShaderOpenGL : public Shader {
    public:
        ShaderOpenGL(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc);

        void Bind() const override;

        void setUniform1f(std::string name, float uniform) override;

        void setUniform3f(std::string name, float *uniform) override;

        void setUniformMat4(const std::string& name, const glm::mat4 &matrix) override;

        void setUniformInt(const std::string &name, const int &uniform) override;

        void Unbind() const override;
    private:
        GLuint m_RendererID;
        std::string m_name;
    };

} // bf

#endif //COMPOUND_SHADEROPENGL_H
