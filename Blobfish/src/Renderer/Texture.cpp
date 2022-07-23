#include "Texture.h"
#include <Platform/OpenGL/Texture2DOpenGL.h>

namespace bf{

    Texture2D *Texture2D::Create(unsigned int width, unsigned int height) {
        return new Texture2DOpenGL(width, height);
    }

    Texture2D *Texture2D::Create(const std::string &path) {
        return new Texture2DOpenGL(path);
    }
}