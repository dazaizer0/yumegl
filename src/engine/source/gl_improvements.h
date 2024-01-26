#pragma once

#include "../../config.h"

void setColor(const math::colorRGBA& color) {
    glClearColor(color.r, color.g, color.b, color.a);
}