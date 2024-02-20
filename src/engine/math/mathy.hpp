#pragma once // IN DEVELOPMENT | SWITCHING TO GLM

#include <iostream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace mathy {
    // VECTOR 2
    template <typename T = float>
    class vec2yu { // TODO: universal vectors (vec2)

    public:
        // FIELDS, PROPERTIES

        glm::vec<2, T, glm::defaultp> container;
        
        inline T x() { return container.x; }
        inline void x(T xIn) { container.x = xIn; }
        
        inline T y() { return container.y; }
        inline void y(T yIn) { container.y = yIn; }

        // CONSTRUCTORS

        vec2yu() {
            x(T(0));
            y(T(0));
        }
        vec2yu(T xIn, T yIn) {
            x(xIn);
            y(yIn);
        }
        explicit vec2yu(glm::vec<2, T, glm::defaultp> container) : container(container) { }

        // FUNCTIONS

        std::string toString() {
            std::stringstream ss;
            ss << "x: " << x() << ", y: " << y() << "\n";
            return ss.str();
        }

        void toStdout() {
            std::cout << toString(); // Uses toString() to make the code more clear. I know it's unoptimal to make an ss and then cout it, but this func.'s probably not gonna be used too much and if it's gonna be, then we'll think about it.
        }

        inline T length_2() {
            return x() * x() + y() * y();
        }

        inline T length() {
            if (typeid(T) == typeid(float))
                return sqrtf(length_2());
            else
                return sqrt(length_2());
        }

        inline T lengthInv() {
            return (T)1 / length();
        }

        inline vec2yu normalizE() {
            return *this *= lengthInv();
        }

        inline vec2yu normalizED() {
            return *this * lengthInv();
        }

        double distance(vec2yu<> other) {
            double dx = container.x - other.x();
            double dy = container.y - other.y();

            return std::sqrt(dx * dx + dy * dy);
        }

        static vec2yu<T> ZERO() { return { T(0), T(0) }; };
        static vec2yu<T> ONE() { return { T(1), T(1) }; };

        static vec2yu<T> UP() { return { T(0), T(-1) }; };
        static vec2yu<T> DOWN() { return { T(0), T(1) }; };
        static vec2yu<T> RIGHT() { return { T(1), T(0) }; };
        static vec2yu<T> LEFT() { return { T(-1), T(0) }; };

        // OPERATORS

        vec2yu<T>& operator=(const vec2yu<T>& other) {
            container = other.container;
            return *this;
        }

        vec2yu<T> operator+(const vec2yu<T>& other) const {
            return vec2yu<T>(container + other.container);
        }
        vec2yu<T>& operator+=(const vec2yu<T>& other) {
            container += other.container;
            return *this;
        }

        vec2yu<T> operator-(const vec2yu<T>& other) const {
            return vec2yu<T>(container - other.container);
        }
        vec2yu<T>& operator-=(const vec2yu<T>& other) {
            container -= other.container;
            return *this;
        }

        vec2yu<T> operator*(const vec2yu<T>& other) const {
            return vec2yu<T>(container * other.container);
        }
        vec2yu<T>& operator*=(const vec2yu<T>& other) {
            container *= other.container;
            return *this;
        }

        vec2yu<T> operator*(const T scale) const {
            return vec2yu<T>(container * scale);
        }
        vec2yu<T>& operator*=(const T scale) {
            container *= scale;
            return *this;
        }

        vec2yu<T> operator/(const vec2yu<T>& other) const {
            return vec2yu<T>(container / other.container);
        }
        vec2yu<T>& operator/=(const vec2yu<T>& other) {
            container /= other.container;
            return *this;
        }

        vec2yu<T> operator/(const T scale) const {
            return vec2yu<T>(container / scale);
        }
        vec2yu<T>& operator/=(const T scale) {
            container /= scale;
            return *this;
        }
    };

    
    // VECTOR 3
    template <typename T = float>
    class vec3yu { // TODO: universal vectors (vec2)

    public:
        // FIELDS, PROPERTIES

        glm::vec<3, T, glm::defaultp> container;

        inline T x() { return container.x; }
        inline void x(T xIn) { container.x = xIn; }

        inline T y() { return container.y; }
        inline void y(T yIn) { container.y = yIn; }

        inline T z() { return container.z; }
        inline void z(T zIn) { container.z = zIn; }

        // CONSTRUCTORS

        vec3yu() {
            x(T(0));
            y(T(0));
            z(T(0));
        }
        vec3yu(T xIn, T yIn, T zIn) {
            x(xIn);
            y(yIn);
            z(zIn);
        }
        explicit vec3yu(glm::vec<3, T, glm::defaultp> container) : container(container) { }

        // FUNCTIONS

        std::string toString() {
            std::stringstream ss;
            ss << "x: " << x() << ", y: " << y() << ", z: " << z() << "\n";
            return ss.str();
        }

        void toStdout() {
            std::cout << toString(); // Uses toString() to make the code more clear. I know it's unoptimal to make an ss and then cout it, but this func.'s probably not gonna be used too much and if it's gonna be, then we'll think about it.
        }

        inline T length_2() {
            return x() * x() + y() * y() + z() * z();
        }

        inline T length() {
            if (typeid(T) == typeid(float))
                return sqrtf(length_2());
            else
                return sqrt(length_2());
        }

        inline T lengthInv() {
            return (T)1 / length();
        }

        inline vec3yu normalizE() {
            return *this *= lengthInv();
        }

        inline vec3yu normalizED() {
            return *this * lengthInv();
        }

        double distance(vec3yu<> other) {
            double dx = container.x - other.x();
            double dy = container.y - other.y();
            double dz = container.z - other.z();

            return std::sqrt(dx * dx + dy * dy + dz * dz);
        }

        static vec3yu<T> ZERO() { return { T(0), T(0), T(0) }; }
        static vec3yu<T> ONE() { return { T(1), T(1), T(1) }; }

        static vec3yu<T> UP() { return { T(0), T(-1), T(0) }; }
        static vec3yu<T> DOWN() { return { T(0), T(1), T(0) }; }
        static vec3yu<T> RIGHT() { return { T(1), T(0), T(0) }; }
        static vec3yu<T> LEFT() { return { T(-1), T(0), T(0) }; }
        static vec3yu<T> FORWARD() { return { T(0), T(0), T(1) }; }
        static vec3yu<T> BACK() { return { T(0), T(0), T(-1) }; }

        // OPERATORS

        vec3yu<T>& operator=(const vec3yu<T>& other) {
            container = other.container;
            return *this;
        }

        vec3yu<T> operator+(const vec3yu<T>& other) const {
            return vec3yu<T>(container + other.container);
        }
        vec3yu<T>& operator+=(const vec3yu<T>& other) {
            container += other.container;
            return *this;
        }

        vec3yu<T> operator-(const vec3yu<T>& other) const {
            return vec3yu<T>(container - other.container);
        }
        vec3yu<T>& operator-=(const vec3yu<T>& other) {
            container -= other.container;
            return *this;
        }

        vec3yu<T> operator*(const vec3yu<T>& other) const {
            return vec3yu<T>(container * other.container);
        }
        vec3yu<T>& operator*=(const vec3yu<T>& other) {
            container *= other.container;
            return *this;
        }

        vec3yu<T> operator*(const T scale) const {
            return vec3yu<T>(container * scale);
        }
        vec3yu<T>& operator*=(const T scale) {
            container *= scale;
            return *this;
        }

        vec3yu<T> operator/(const vec3yu<T>& other) const {
            return vec3yu<T>(container / other.container);
        }
        vec3yu<T>& operator/=(const vec3yu<T>& other) {
            container /= other.container;
            return *this;
        }

        vec3yu<T> operator/(const T scale) const {
            return vec3yu<T>(container / scale);
        }
        vec3yu<T>& operator/=(const T scale) {
            container /= scale;
            return *this;
        }
    };

    vec2yu<> scaleToWindow(vec2yu<> vec, int window_x, int window_y) {
        return vec2yu<>{ 0.0f, 0.0f };

        // example:
        // vec.x = 1.0f, vec.y = 1.0f
        // window_x == 1280
        // window_y = 720
        // = 16 : 9
        // new vec = { 0.45f, 0.8f }
    }
}

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

    static colour BLACK() { return {0.0f, 0.0f, 0.0f, 1.0f}; };

    static colour RED() { return {1.0f, 0.0f, 0.0f, 1.0f}; };
    static colour GREEN() { return {0.0f, 1.0f, 0.0f, 1.0f}; };
    static colour BLUE() { return {0.0f, 0.0f, 1.0f, 1.0f}; };

    static colour WHITE() { return { 1.0f, 1.0f, 1.0f, 1.0f }; };
};
