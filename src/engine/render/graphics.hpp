#pragma once

#include <iostream>
#include <sstream>

// RGBA
class colour {
public:
    float r{};
    float g{};
    float b{};
    float a{};

    colour(float rValue, float gValue, float bValue, float aValue)
        : r(rValue), g(gValue), b(bValue), a(aValue) {}

    colour& operator=(const colour& other) = default;

    static colour BLACK() { return { 0.0f, 0.0f, 0.0f, 1.0f }; };

    static colour DARK_GRAY() { return { 0.2f, 0.2f, 0.2f, 1.0f }; };
    static colour LIGHT_GRAY() { return { 0.65f, 0.65f, 0.65f, 1.0f }; };

    static colour RED() { return { 1.0f, 0.0f, 0.0f, 1.0f }; };
    static colour GREEN() { return { 0.0f, 1.0f, 0.0f, 1.0f }; };
    static colour BLUE() { return { 0.0f, 0.0f, 1.0f, 1.0f }; };
    static colour YELLOW() { return { 1.0f, 1.0f, 0.0f, 1.0f }; };
    static colour PURPLE() { return { 0.5f, 0.3f, 0.8f, 1 }; }; //nice purple :)

    static colour WHITE() { return { 1.0f, 1.0f, 1.0f, 1.0f }; };
};
