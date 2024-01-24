#pragma once

#include "../../config.h"

void setColor(const math::color4& color) {
    glClearColor(color.r, color.g, color.b, color.a);
}