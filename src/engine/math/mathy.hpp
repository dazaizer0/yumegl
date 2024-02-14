#pragma once // IN DEVELOPMENT | SWITCHING TO GLM

#include <iostream>

namespace mathy {
    // VECTOR 2
    template <typename T>
    class vec2 {
    public:
        T x{};
        T y{};

        vec2(T xValue, T yValue)
                : x(xValue), y(yValue) {}

        void out() {
            std::cout << "x: " << x << ", y: " << y << "\n";
        }

        vec2<T>& operator=(const vec2<T>& other) {
            x = other.x;
            y = other.y;

            return *this;
        }

        vec2<T> operator+(const vec2<T>& other) const {
            return vec2<T>(x + other.x, y + other.y);
        }

        vec2<T> operator-(const vec2<T>& other) const {
            return vec2<T>(x - other.x, y - other.y);
        }

        vec2<T> operator*(const vec2<T>& other) const {
            return vec2<T>(x * other.x, y * other.y);
        }

        vec2<T> operator/(const vec2<T>& other) const {
            return vec2<T>(x / other.x, y / other.y);
        }

        glm::vec2 asGlm() {
            return {x, y};
        }

        static vec2<T> ZERO() { return {T(0), T(0)}; };
        static vec2<T> ONE() { return {T(1), T(1)}; };

        static vec2<T> UP() { return {T(0), T(-1)}; };
        static vec2<T> DOWN() { return {T(0), T(1)}; };
        static vec2<T> RIGHT() { return {T(1), T(0)}; };
        static vec2<T> LEFT() { return {T(-1), T(0)}; };
    };

    // VECTOR 3
    template <typename T>
    class vec3 {
    public:
        T x{};
        T y{};
        T z{};

        vec3(T xValue, T yValue, T zValue)
                : x(xValue), y(yValue), z(zValue) {}

        void out() {
            std::cout << "x: " << x << ", y: " << y << ", z: " << z << "\n";
        }

        vec3<T>& operator=(const vec3<T>& other) {
            x = other.x;
            y = other.y;
            z = other.z;

            return *this;
        }

        vec3<T> operator+(const vec3<T>& other) const {
            return vec3<T>(x + other.x, y + other.y, z + other.z);
        }

        vec3<T> operator-(const vec3<T>& other) const {
            return vec3<T>(x - other.x, y - other.y, z - other.z);
        }

        vec3<T> operator*(const vec3<T>& other) const {
            return vec3<T>(x * other.x, y * other.y, z * other.z);
        }

        vec3<T> operator/(const vec3<T>& other) const {
            return vec3<T>(x / other.x, y / other.y, z / other.z);
        }

        glm::vec3 asGlm() {
            return {x, y, z};
        }

        static vec3<T> ZERO() { return {T(0), T(0), T(0)}; };
        static vec3<T> ONE() { return {T(1), T(1), T(1)}; };

        static vec3<T> UP() { return {T(0), T(1), T(0)}; };
    };

    // RGBA
    class color {
    public:
        float r{};
        float g{};
        float b{};
        float a{};

        color(float rValue, float gValue, float bValue, float aValue)
                : r(rValue), g(gValue), b(bValue), a(aValue) {}

        color& operator=(const color& other) = default;

        static color BLACK() { return {0.0f, 0.0f, 0.0f, 1.0f}; };

        static color RED() { return {1.0f, 0.0f, 0.0f, 1.0f}; };
        static color GREEN() { return {0.0f, 1.0f, 0.0f, 1.0f}; };
        static color BLUE() { return {0.0f, 0.0f, 1.0f, 1.0f}; };

        static color WHITE() { return { 1.0f, 1.0f, 1.0f, 1.0f }; };
    };

    namespace convert {
        [[maybe_unused]] glm::vec2 mathyVec2_glmVec2(vec2<float> vec) {
            return glm::vec2 {vec.x, vec.y};
        }

        [[maybe_unused]] mathy::vec2<float> glmVec2_mathyVec2(glm::vec2 vec) {
            return mathy::vec2<float> {vec.x, vec.y};
        }

        [[maybe_unused]] glm::vec3 mathyVec3_glmVec3(vec3<float> vec) {
            return glm::vec3 {vec.x, vec.y, vec.z};
        }

        [[maybe_unused]] mathy::vec3<float> glmVec3_mathyVec3(glm::vec3 vec) {
            return mathy::vec3<float> {vec.x, vec.y, vec.z};
        }
    }
}
