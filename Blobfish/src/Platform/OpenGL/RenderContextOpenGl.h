//
// Created by plasm on 16.07.2022.
//

#ifndef COMPOUND_RENDERCONTEXTOPENGL_H
#define COMPOUND_RENDERCONTEXTOPENGL_H

#include <Renderer/RenderContext.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace bf {

    class RenderContextOpenGL : public RenderContext {
    public:
        RenderContextOpenGL(GLFWwindow *window);

        ~RenderContextOpenGL() override = default;

        void init() override;

        void swapBuffers() override;

    private:
        GLFWwindow *m_window;
    };

} // bf

#endif //COMPOUND_RENDERCONTEXTOPENGL_H
