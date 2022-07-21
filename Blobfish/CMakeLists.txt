cmake_minimum_required(VERSION 3.13)
project(blobfish)

add_definitions(-DDEBUG=1)
add_compile_definitions(TRACY_ENABLE)

set(CMAKE_CXX_STANDARD 20)

set(GLAD_FILES extern/glad/src/glad.c src/Renderer/RenderContext.h src/Platform/OpenGL/RenderContextOpenGl.cpp src/Platform/OpenGL/RenderContextOpenGl.h src/Renderer/RenderContext.cpp src/Renderer/Shader.cpp src/Renderer/Shader.h src/Platform/OpenGL/ShaderOpenGL.cpp src/Platform/OpenGL/ShaderOpenGL.h src/Renderer/Buffer.cpp src/Renderer/Buffer.h src/Platform/OpenGL/BufferOpenGl.cpp src/Platform/OpenGL/BufferOpenGl.h src/Renderer/VertexArray.cpp src/Renderer/VertexArray.h src/Platform/OpenGL/VertexArrayOpenGL.cpp src/Platform/OpenGL/VertexArrayOpenGL.h src/Renderer/RendererAPI.h src/Renderer/RendererAPI.cpp src/Renderer/Renderer.cpp src/Renderer/Renderer.h src/Renderer/RenderCommand.cpp src/Renderer/RenderCommand.h src/Platform/OpenGL/RendererAPIOpenGL.cpp src/Platform/OpenGL/RendererAPIOpenGL.h src/Renderer/OrthographicCamera.cpp src/Renderer/OrthographicCamera.h)

file(GLOB IMGUI_LIB_FILES extern/imgui/**.cpp)
file(GLOB CORE_FILES src/Core/**.cpp core/**.h)
file(GLOB EVENT_FILES src/Event/**.cpp src/Event/**.h)
file(GLOB IMGUI_FILES src/ImGui/**.cpp src/ImGui/**.h)
file(GLOB PLATFORM_FILES src/Platform/**/**.cpp src/Platform/**/**.h)
file(GLOB TRACY_PROFILER_FILES extern/tracy/TracyClient.cpp)

include_directories(extern/glad/include)
include_directories(extern/glfw/include)
include_directories(extern/spdlog/include)
include_directories(extern/imgui)
include_directories(src)

add_library(blobfish  ${GLAD_FILES} ${IMGUI_LIB_FILES} ${CORE_FILES} ${EVENT_FILES} ${IMGUI_FILES} ${PLATFORM_FILES} ${TRACY_PROFILER_FILES})
target_include_directories(blobfish PUBLIC extern/imgui extern/tracy)

add_subdirectory(extern/glfw)
add_subdirectory(extern/spdlog)
add_subdirectory(extern/glm)
add_subdirectory(extern/tracy)

link_directories(extern/glfw)

find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${TRACY_INCLUDE_DIRS})

target_link_libraries(blobfish OpenGL::GL glfw spdlog glm Tracy::TracyClient)