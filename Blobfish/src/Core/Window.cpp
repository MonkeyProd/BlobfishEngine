//
// Created by plasm on 14.07.2022.
//

#include "Window.h"
#include "../Platform/WindowGLFW.h"

namespace Blobfish {
    Window *Blobfish::Window::Create(const Blobfish::WindowProps &props) {
        return new WindowGLFW(props); //TODO: make unique
    }
}