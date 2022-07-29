cmake_minimum_required(VERSION 3.13)
project(sandbox)
set(CMAKE_CXX_STANDARD 20)

set(GLAD_FILES ../Blobfish/extern/glad/src/glad.c)
add_compile_definitions(TRACY_ENABLE)

set(SOURCE_FILES src/main_test.cpp src/Sandbox2D_test.cpp src/Sandbox2D_test.h)
file(GLOB TRACY_PROFILER_FILES extern/tracy/TracyClient.cpp)
add_executable(sandbox ${SOURCE_FILES} ${GLAD_FILES} ${TRACY_PROFILER_FILES})

#GameEngine
find_library(blobfish REQUIRE)

target_link_libraries(sandbox blobfish)
include_directories(../Blobfish/src/)

#externs
find_package(OpenGL REQUIRED)

include_directories(../Blobfish/extern/glad/include ../Blobfish/extern/tracy)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})

target_link_libraries(sandbox OpenGL::GL glfw )