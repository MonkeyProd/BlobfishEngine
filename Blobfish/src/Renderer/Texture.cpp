#include "Texture.h"
#include <Platform/OpenGL/Texture2DOpenGL.h>
#include <Renderer/Renderer.h>

namespace bf{

    Texture2D *Texture2D::Create(unsigned int width, unsigned int height) {
        //TODO: use smart pointers
        switch (Renderer::getAPI()) {
            case RendererAPI::API::None:
                BF_ASSERT(false, "RendererAPI::API::None is currently not supported!")
            case RendererAPI::API::OpenGL:
                return new Texture2DOpenGL(width, height);
        }
        BF_ASSERT(false, "Unknown RendererAPI!");
    }

    Texture2D *Texture2D::Create(const std::string &path) {
        //TODO: use smart pointers
        switch (Renderer::getAPI()) {
            case RendererAPI::API::None:
                BF_ASSERT(false, "RendererAPI::API::None is currently not supported!")
            case RendererAPI::API::OpenGL:
                return new Texture2DOpenGL(path);
        }
        BF_ASSERT(false, "Unknown RendererAPI!");
    }
}