#include "Framebuffer.h"

#include <Renderer/Renderer.h>
#include <Platform/OpenGL/FramebufferOpenGL.h>

namespace bf {
    Framebuffer* Framebuffer::Create(const FramebufferSpecification& spec)
    {
        switch (Renderer::getAPI())
        {
            case RendererAPI::API::None:    BF_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return new FramebufferOpenGL(spec);
        }

        BF_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
} // bf