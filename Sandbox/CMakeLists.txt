cmake_minimum_required(VERSION 3.13)
project(sandbox)
set(CMAKE_CXX_STANDARD 20)

set(GLAD_FILES ../Blobfish/extern/glad/src/glad.c)

set(SOURCE_FILES src/main_test.cpp)

add_executable(sandbox ${SOURCE_FILES} ${GLAD_FILES})

#GameEngine
find_library(blobfish REQUIRE)

target_link_libraries(sandbox blobfish)
include_directories(../Blobfish/src/)

#externs
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

include_directories(../Blobfish/extern/glad/include)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})

target_link_libraries(sandbox OpenGL::GL glfw )