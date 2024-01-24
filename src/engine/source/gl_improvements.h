#pragma once

#include "../../config.h"

void setColor(const math::color4& color) {
    glClearColor(color.r, color.g, color.b, color.a);
}

void setUpWindowHint(int v) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, v);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, v);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
}