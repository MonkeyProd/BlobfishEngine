#include "RenderContext.h"
#include "Platform/OpenGL/RenderContextOpenGl.h"
#include <Core/BlobPCH.h>

bf::RenderContext *bf::RenderContext::Create(void *window) {
    ZoneScoped;
    return new RenderContextOpenGL(static_cast<GLFWwindow *>(window));
    //TODO: API CHOOSE
    /*
     *
    template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
     *
     *
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::None:    HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
    }

    BF_ASSERT(false, "Unknown RendererAPI!");
     */
}
