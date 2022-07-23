#include "Window.h"
#include "../Platform/GLFW/WindowGLFW.h"

namespace bf {
    Window *bf::Window::Create(const bf::WindowProps &props) {
        return new WindowGLFW(props); //TODO: make unique
    }
}