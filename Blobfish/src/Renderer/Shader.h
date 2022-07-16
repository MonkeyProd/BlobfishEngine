//
// Created by plasm on 16.07.2022.
//

#ifndef COMPOUND_SHADER_H
#define COMPOUND_SHADER_H

#include <Core/BlobPCH.h>

namespace bf {

    class Shader {
    public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void setUniform1f(std::string name, float uniform) = 0;
        virtual void setUniform3f(std::string name, float *uniform) = 0;


        static Shader* Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
    };

} // bf

#endif //COMPOUND_SHADER_H
