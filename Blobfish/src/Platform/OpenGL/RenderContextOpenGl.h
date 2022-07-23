#ifndef RENDERCONTEXTOPENGL_H
#define RENDERCONTEXTOPENGL_H

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

#endif //RENDERCONTEXTOPENGL_H
