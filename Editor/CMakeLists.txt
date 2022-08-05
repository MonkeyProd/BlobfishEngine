cmake_minimum_required(VERSION 3.13)
project(editor)
set(CMAKE_CXX_STANDARD 20)

set(GLAD_FILES ../Blobfish/extern/glad/src/glad.c src/EditorLayer.cpp src/EditorLayer.h)
add_compile_definitions(TRACY_ENABLE)

file(GLOB SOURCE_FILES src/*.cpp src/*.h)
file(GLOB TRACY_PROFILER_FILES extern/tracy/TracyClient.cpp)
add_executable(editor ${SOURCE_FILES} ${GLAD_FILES} ${TRACY_PROFILER_FILES})

#GameEngine
find_library(blobfish REQUIRE)

target_link_libraries(editor blobfish)
include_directories(../Blobfish/src/)

#externs
find_package(OpenGL REQUIRED)

include_directories(../Blobfish/extern/glad/include ../Blobfish/extern/tracy)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})

target_link_libraries(editor OpenGL::GL glfw )