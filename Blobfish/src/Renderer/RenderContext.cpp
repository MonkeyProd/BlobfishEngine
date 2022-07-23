#include "RenderContext.h"
#include "Platform/OpenGL/RenderContextOpenGl.h"
#include <Core/BlobPCH.h>
#include "Renderer.h"

bf::RenderContext *bf::RenderContext::Create(void *window) {
    ZoneScoped;
    switch (Renderer::getAPI()) {
        case RendererAPI::API::None:
            BF_ASSERT(false, "RendererAPI::API::None is currently not supported!")
        case RendererAPI::API::OpenGL:
            return new RenderContextOpenGL(static_cast<GLFWwindow *>(window));
    }
    BF_ASSERT(false, "Unknown RendererAPI!");
    //TODO: use smart pointers
}
