//
// Created by plasm on 14.07.2022.
//

#include "../../Core/TimeUtils.h"
#include "GLFW/glfw3.h"
#include <Tracy.hpp>


float bf::Time::GetTime() {
    ZoneScoped;
    return glfwGetTime();
}