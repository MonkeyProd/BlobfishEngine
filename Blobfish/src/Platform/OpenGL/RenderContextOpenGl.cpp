#include "RenderContextOpenGl.h"
#include <Core/BlobPCH.h>

namespace bf {
    void RenderContextOpenGL::init() {
        ZoneScoped;
        glfwMakeContextCurrent(m_window);
        BF_ASSERT((m_window != nullptr), "GLFW WINDOW INIT FAILED");
        int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        BF_ASSERT(status, "GLAD INIT FAILED");
    }

    void RenderContextOpenGL::swapBuffers() {
        ZoneScoped;
        glfwSwapBuffers(m_window);
    }

    RenderContextOpenGL::RenderContextOpenGL(GLFWwindow *window) : m_window(window) {
        ZoneScoped;
        BF_ASSERT((window != nullptr), "WINDOW IS NULL DURING CREATE OF RenderContextOpenGL");
    }
} // bf