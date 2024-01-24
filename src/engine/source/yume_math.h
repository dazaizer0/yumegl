#pragma once

namespace math {
    template <typename T>
    class vec2 {
    public:
        T a {};
        T b {};

        vec2(T aValue, T bValue)
        : a(aValue), b(bValue) {}

        void out() {
            std::cout << "a: " << a << "\n";
            std::cout << "b: " << b << "\n";
        }

        vec2 operator+(const vec2& other) const {
            return vec2(a + other.a, b + other.b);
        }

        vec2 operator-(const vec2& other) const {
            return vec2(a - other.a, b - other.b);
        }

        vec2 operator*(const vec2& other) const {
            return vec2(a * other.a, b * other.b);
        }

        vec2 operator/(const vec2& other) const {
            return vec2<float>(a / other.a, b / other.b);
        }

        static vec2 CUSTOM(T a, T b) { return {a, b}; };

        static vec2 ZERO() { return {0.0f, 0.0f}; };
        static vec2 ONE() { return {1.0f, 1.0f }; };

        static vec2 UP() { return {0.0f, 1.0f}; };
        static vec2 DOWN() { return {0.0f, -1.0f}; };
        static vec2 RIGHT() { return {1.0f, 0.0f}; };
        static vec2 LEFT() { return {-1.0f, 0.0f}; };
    };

    template <typename T>
    class vec3 {
    public:
        T a {};
        T b {};
        T c {};

        vec3(T aValue, T bValue, T cValue)
        : a(aValue), b(bValue), c(cValue) {}

        void out() {
            std::cout << "a: " << a << "\n";
            std::cout << "b: " << b << "\n";
            std::cout << "b: " << c << "\n";
        }

        static vec3 CUSTOM(T a, T b, T c) { return {a, b, c}; };

        static vec3 ZERO() { return {0.0f, 0.0f, 0.0f}; };
        static vec3 ONE() { return {1.0f, 1.0f, 1.0f}; };
    };

    template <typename T>
    class vec4 {
    public:
        T a {};
        T b {};
        T c {};
        T d {};

        vec4(T aValue, T bValue, T cValue, T dValue)
            : a(aValue), b(bValue), c(cValue), d(dValue) {}

        void out() {
            std::cout << "a: " << a << "\n";
            std::cout << "b: " << b << "\n";
            std::cout << "c: " << c << "\n";
            std::cout << "d: " << d << "\n";
        }

        static vec4 ZERO() { return {0.0f, 0.0f, 0.0f, 0.0f}; };
        static vec4 ONE() { return {1.0f, 1.0f, 1.0f, 1.0f}; };
    };

    class color4 {
    public:
        float r{};
        float g{};
        float b{};
        float a{};

        color4(float rValue, float gValue, float bValue, float aValue)
                : r(rValue), g(gValue), b(bValue), a(aValue) {}

        static color4 BLACK() { return {0.0f, 0.0f, 0.0f, 1.0f}; };
        static color4 WHITE() { return {1.0f, 1.0f, 1.0f, 1.0f}; };
        static color4 RED() { return {1.0f, 0.0f, 0.0f, 1.0f}; };
        static color4 GREEN() { return {0.0f, 1.0f, 0.0f, 1.0f}; };
        static color4 BLUE() { return {0.0f, 0.0f, 1.0f, 1.0f}; };
    };
}
