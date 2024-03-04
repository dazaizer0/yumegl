#pragma once // IN DEVELOPMENT | SWITCHING TO GLM

#define _USE_MATH_DEFINES

#include <iostream>
#include <sstream>
#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace mathy {

    /// <summary>
/// Does what the name says.
/// Designed to be invoked every frame.
/// </summary>
/// <param name="timer">: Usually a timer(a variable changing at a constant speed[at least here])</param>
/// <param name="period">Period of the sine wave.</param>
/// <returns></returns>
    double sine_0_1_smooth_period_change(double timer, double period) {
        static double last_period = 1, slide;

        if (period != last_period) {
            slide = timer - ((timer - slide) * period / last_period);
            last_period = period;
            //slide -= (period * floor(slide / period));
        }
        return sin((((timer - slide) / period) - 0.25) * 2 * M_PI) * 0.5 + 0.5;
    }



    // VECTOR 2
    template <typename T = float>
    class vec2yu {

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
            std::cout << toString(); // Uses toString() to make the code more clear. I know it's suboptimal to make an ss and then cout it, but this func.'s probably not going to be used too much and if it's going to be, then we'll think about it.
        }

        inline T length_2() {
            return x() * x() + y() * y();
        }

        inline T length();

        inline T lengthInv();

        [[maybe_unused]] inline vec2yu normalizE() {
            return *this *= lengthInv();
        }

        [[maybe_unused]] inline vec2yu normalizED() {
            return *this * lengthInv();
        }

        T distance(vec2yu<T> other);

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
        vec2yu<T> operator+(const T scale) const {
            return vec2yu<T>(container + scale);
        }
        vec2yu<T>& operator+=(const T scale) {
            container += scale;
            return *this;
        }

        vec2yu<T> operator-(const vec2yu<T>& other) const {
            return vec2yu<T>(container - other.container);
        }
        vec2yu<T>& operator-=(const vec2yu<T>& other) {
            container -= other.container;
            return *this;
        }
        vec2yu<T> operator-(const T scale) const {
            return vec2yu<T>(container - scale);
        }
        vec2yu<T>& operator-=(const T scale) {
            container -= scale;
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

        template<typename A>
        operator vec2yu<A>() {
            return vec2yu<A>((A)(this->container.x), (A)(this->container.y));
        }
    };

    template<typename T>
    T vec2yu<T>::length() {
        return sqrt(length_2());
    }
    template<>
    float vec2yu<>::length() {
        return sqrtf(length_2());
    }

    template<typename T>
    T vec2yu<T>::lengthInv() {
        return (T)1 / length();
    }

    template<typename T>
    T distance(vec2yu<T> other) {
        return (*this - other).length();
    }

    vec2yu<> scaleToWindow(int window_x, int window_y) {
        return vec2yu<>{ 0.0f, 0.0f };

        // example:
        // vec.x = 1.0f, vec.y = 1.0f
        // window_x == 1280
        // window_y = 720
        // = 16 : 9
        // new vec = { 0.45f, 0.8f }
    }



    // VECTOR 3
    template <typename T = float>
    class vec3yu {

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
            std::cout << toString(); // Uses toString() to make the code more clear. I know it's suboptimal to make an ss and then cout it, but this func.'s probably not going to be used too much and if it's going to be, then we'll think about it.
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

        [[maybe_unused]] inline vec3yu normalizE() {
            return *this *= lengthInv();
        }

        [[maybe_unused]] inline vec3yu normalizED() {
            return *this * lengthInv();
        }

        T distance(vec3yu other) {
            return (*this - other).length();
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
        vec3yu<T> operator+(const T scale) const {
            return vec3yu<T>(container + scale);
        }
        vec3yu<T>& operator+=(const T scale) {
            container += scale;
            return *this;
        }

        vec3yu<T> operator-(const vec3yu<T>& other) const {
            return vec3yu<T>(container - other.container);
        }
        vec3yu<T>& operator-=(const vec3yu<T>& other) {
            container -= other.container;
            return *this;
        }
        vec3yu<T> operator-(const T scale) const {
            return vec3yu<T>(container - scale);
        }
        vec3yu<T>& operator-=(const T scale) {
            container -= scale;
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

        template<typename A>
        operator vec3yu<A>() {
            return vec3yu<A>((A)this->container.x, (A)this->container.y, (A)this->container.z);
        }
    };

    // VECTOR 4
    template <typename T = float>
    class vec4yu {

    public:
        // FIELDS, PROPERTIES

        glm::vec<4, T, glm::defaultp> container;

        inline T x() { return container.x; }
        inline void x(T xIn) { container.x = xIn; }

        inline T y() { return container.y; }
        inline void y(T yIn) { container.y = yIn; }

        inline T z() { return container.z; }
        inline void z(T zIn) { container.z = zIn; }

        inline T w() { return container.w; }
        inline void w(T wIn) { container.w = wIn; }

        // CONSTRUCTORS

        vec4yu() {
            x(T(0));
            y(T(0));
            z(T(0));
            w(T(0));
        }
        vec4yu(T xIn, T yIn, T zIn, T wIn) {
            x(xIn);
            y(yIn);
            z(zIn);
            w(zIn);
        }
        explicit vec4yu(glm::vec<4, T, glm::defaultp> container) : container(container) { }

        // FUNCTIONS

        std::string toString() {
            std::stringstream ss;
            ss << "x: " << x() << ", y: " << y() << ", z: " << z() << ", w: " << w() << std::endl;
            return ss.str();
        }

        void toStdout() {
            std::cout << toString(); // Uses toString() to make the code more clear. I know it's suboptimal to make an ss and then cout it, but this func.'s probably not going to be used too much and if it's going to be, then we'll think about it.
        }

        inline T length_2() {
            return x() * x() + y() * y() + z() * z() + w() * w();
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

        [[maybe_unused]] inline vec4yu normalizE() {
            return *this *= lengthInv();
        }

        [[maybe_unused]] inline vec4yu normalizED() {
            return *this * lengthInv();
        }

        T distance(vec4yu other) {
            return (*this - other).length();
        }

        static vec4yu<T> ZERO() { return { T(0), T(0), T(0), T(0) }; }
        static vec4yu<T> ONE() { return { T(1), T(1), T(1), T(1) }; }

        static vec4yu<T> UP() { return { T(0), T(-1), T(0), T(1) }; }
        static vec4yu<T> DOWN() { return { T(0), T(1), T(0), T(1) }; }
        static vec4yu<T> RIGHT() { return { T(1), T(0), T(0), T(1) }; }
        static vec4yu<T> LEFT() { return { T(-1), T(0), T(0), T(1) }; }
        static vec4yu<T> FORWARD() { return { T(0), T(0), T(1), T(1) }; }
        static vec4yu<T> BACK() { return { T(0), T(0), T(-1), T(1) }; }

        vec3yu<T> fromHomoToVec3yu() {
            return vec3yu<T>(x(), y(), z()) / w();
        }

        // OPERATORS

        vec4yu<T>& operator=(const vec4yu<T>& other) {
            container = other.container;
            return *this;
        }

        vec4yu<T> operator+(const vec4yu<T>& other) const {
            return vec4yu<T>(container + other);
        }
        vec4yu<T>& operator+=(const vec4yu<T>& other) {
            container += other;
            return *this;
        }
        vec4yu<T> operator+(const T other) const {
            return vec4yu<T>(container + other);
        }
        vec4yu<T>& operator+=(const T other) {
            container += other;
            return *this;
        }

        vec4yu<T> operator-(const vec4yu<T>& other) const {
            return vec4yu<T>(container - other.container);
        }
        vec4yu<T>& operator-=(const vec4yu<T>& other) {
            container -= other.container;
            return *this;
        }
        vec4yu<T> operator-(const T other) const {
            return vec4yu<T>(container - other);
        }
        vec4yu<T>& operator-=(const T other) {
            container -= other;
            return *this;
        }

        vec4yu<T> operator*(const vec4yu<T>& other) const {
            return vec4yu<T>(container * other.container);
        }
        vec4yu<T>& operator*=(const vec4yu<T>& other) {
            container *= other.container;
            return *this;
        }

        vec4yu<T> operator*(const T scale) const {
            return vec4yu<T>(container * scale);
        }
        vec4yu<T>& operator*=(const T scale) {
            container *= scale;
            return *this;
        }

        vec4yu<T> operator/(const vec4yu<T>& other) const {
            return vec4yu<T>(container / other.container);
        }
        vec4yu<T>& operator/=(const vec4yu<T>& other) {
            container /= other.container;
            return *this;
        }

        vec4yu<T> operator/(const T scale) const {
            return vec4yu<T>(container / scale);
        }
        vec4yu<T>& operator/=(const T scale) {
            container /= scale;
            return *this;
        }

        template<typename A>
        operator vec4yu<A>() {
            return vec4yu<A>((A)this->container.x, (A)this->container.y, (A)this->container.z, (A)this->container.w);
        }
    };

    template <typename T = float>
    class yuMatrix2x2 {
    public:

        glm::mat<2, 2, T, glm::defaultp> container;

        inline T value(GLubyte column, GLubyte row) {
            if (column > 1 || row > 1) {
                std::cerr << "ERROR: MATRIX: ARGUMENT(s) OUT OF BOUNDS " << std::endl;
                return 0;
            }
            return container[column][row];
        }
        inline void value(GLubyte column, GLubyte row, T in) { 
            if (column > 1 || row > 1) {
                std::cerr << "ERROR: MATRIX: ARGUMENT(s) OUT OF BOUNDS " << std::endl;
                return;
            }
            container[column][row] = in;
        }

        inline vec2yu<T> value(GLubyte column) {
            if (column > 1 ) {
                std::cerr << "ERROR: MATRIX: ARGUMENT OUT OF BOUNDS " << std::endl;
                return vec2yu<T>::ZERO();
            }
            return vec2yu<T>(container[column]);
        }
        inline void value(GLubyte column, vec2yu<T> in) {
            if (column > 1 ) {
                std::cerr << "ERROR: MATRIX: ARGUMENT OUT OF BOUNDS " << std::endl;
                return;
            }
            container[column] = in.container;
        }

        yuMatrix2x2() : container({ {0, 0},{0, 0} }) {}
        
        yuMatrix2x2(const glm::mat<2, 2, T, glm::defaultp>& yeet) : container(yeet) {}
        
        yuMatrix2x2(const T arrayIn[2][2]) : container({ {arrayIn[0][0], arrayIn[0][1]}, {arrayIn[1][0], arrayIn[1][1]} }) {}

        yuMatrix2x2(const yuMatrix2x2<T>& obj) : container(obj.container) { }

        static yuMatrix2x2<T> unit() {
            const T numbers[2][2] = { {(T)1, (T)0}, {(T)0, (T)1} };
            return yuMatrix2x2<T>(numbers);
        }

        yuMatrix2x2<T> operator +(const yuMatrix2x2<T>& b) {
            return yuMatrix2x2(this->container + b.container);
        }
        yuMatrix2x2<T> operator +=(const yuMatrix2x2<T>& b) {
            this->container += b.container;
            return *this;
        }

        yuMatrix2x2<T> operator -(const yuMatrix2x2<T>& b) {
            return yuMatrix2x2(this->container - b.container);
        }
        yuMatrix2x2<T> operator -=(const yuMatrix2x2<T>& b) {
            this->container -= b.container;
            return *this;
        }


        yuMatrix2x2<T> operator *(const yuMatrix2x2<T>& b) {
            return yuMatrix2x2(this->container * b.container);
        }
        yuMatrix2x2<T> operator *=(const yuMatrix2x2<T>& b) {
            this->container *= b.container;
            return *this;
        }

        /// <summary>
        /// Returns a new vector. It is b transformed by the matrix on the left.
        /// </summary>
        /// <param name="b">Vector with the data to transform</param>
        /// <returns>A new vector that = matrix * b.</returns>
        vec2yu<T> operator *(const vec2yu<T> b) {
            return vec2yu<T>(this->container * b.container);
        }

        /// <summary>
        /// Transforms vector b by the matrix on the left.
        /// Saves the changes to vector b.
        /// </summary>
        /// <param name="b">Vector to be transformed.</param>
        /// <returns>Reference to the transformed vector.</returns>
        vec2yu<T>& operator *=(vec2yu<T>& b) {
            b = *this * b;
            return b;
        }
    };

    template <typename T = float>
    class yuMatrix3x3 {
    public:

        glm::mat<3, 3, T, glm::defaultp> container;

        inline T value(GLubyte column, GLubyte row) {
            if (column > 2 || row > 2) {
                std::cerr << "ERROR: MATRIX: ARGUMENT(s) OUT OF BOUNDS " << std::endl;
                return 0;
            }
            return container[column][row];
        }
        inline void value(GLubyte column, GLubyte row, T in) {
            if (column > 2 || row > 2) {
                std::cerr << "ERROR: MATRIX: ARGUMENT(s) OUT OF BOUNDS " << std::endl;
                return;
            }
            container[column][row] = in;
        }

        inline vec3yu<T> value(GLubyte column) {
            if (column > 2) {
                std::cerr << "ERROR: MATRIX: ARGUMENT OUT OF BOUNDS " << std::endl;
                return vec3yu<T>::ZERO();
            }
            return vec3yu<T>(container[column]);
        }
        inline void value(GLubyte column, vec3yu<T> in) {
            if (column > 2) {
                std::cerr << "ERROR: MATRIX: ARGUMENT OUT OF BOUNDS " << std::endl;
                return;
            }
            container[column] = in.container;
        }

        yuMatrix3x3() : container({ {0, 0, 0}, {0, 0, 0}, {0, 0, 0} }) {}

        yuMatrix3x3(const glm::mat<3, 3, T, glm::defaultp>& yeet) : container(yeet) {}

        yuMatrix3x3(const T arrayIn[3][3]) : container({ {arrayIn[0][0], arrayIn[0][1], arrayIn[0][2]},
            {arrayIn[1][0], arrayIn[1][1], arrayIn[1][2]}, {arrayIn[2][0], arrayIn[2][1], arrayIn[2][2]} }) {}

        yuMatrix3x3(const yuMatrix3x3<T>& obj) : container(obj.container) { }

        static yuMatrix3x3<T> unit() {
            const T numbers[3][3] = { {(T)1, (T)0, (T)0}, {(T)0, (T)1, (T)0}, {(T)0, (T)0, (T)1} };
            return yuMatrix3x3<T>(numbers);
        }

        yuMatrix3x3<T> operator +(const yuMatrix3x3<T>& b) {
            return yuMatrix3x3(this->container + b.container);
        }
        yuMatrix3x3<T> operator +=(const yuMatrix3x3<T>& b) {
            this->container += b.container;
            return *this;
        }

        yuMatrix3x3<T> operator -(const yuMatrix3x3<T>& b) {
            return yuMatrix3x3(this->container - b.container);
        }
        yuMatrix3x3<T> operator -=(const yuMatrix3x3<T>& b) {
            this->container -= b.container;
            return *this;
        }


        yuMatrix3x3<T> operator *(const yuMatrix3x3<T>& b) {
            return yuMatrix3x3(this->container * b.container);
        }
        yuMatrix3x3<T> operator *=(const yuMatrix3x3<T>& b) {
            this->container *= b.container;
            return *this;
        }

        /// <summary>
        /// Returns a new vector. It is b transformed by the matrix on the left.
        /// </summary>
        /// <param name="b">Vector with the data to transform</param>
        /// <returns>A new vector that = matrix * b.</returns>
        vec3yu<T> operator *(const vec3yu<T> b) {
            return vec3yu<T>(this->container * b.container);
        }

        /// <summary>
        /// Transforms vector b by the matrix on the left.
        /// Saves the changes to vector b.
        /// </summary>
        /// <param name="b">Vector to be transformed.</param>
        /// <returns>Reference to the transformed vector.</returns>
        vec3yu<T>& operator *=(vec3yu<T>& b) {
            b = *this * b;
            return b;
        }
    };

    template <typename T = float>
    class yuMatrix4x4 {
    public:

        glm::mat<4, 4, T, glm::defaultp> container;

        inline T value(GLubyte column, GLubyte row) {
            if (column > 3 || row > 3) {
                std::cerr << "ERROR: MATRIX: ARGUMENT(s) OUT OF BOUNDS " << std::endl;
                return 0;
            }
            return container[column][row];
        }
        inline void value(GLubyte column, GLubyte row, T in) {
            if (column > 3 || row > 3) {
                std::cerr << "ERROR: MATRIX: ARGUMENT(s) OUT OF BOUNDS " << std::endl;
                return;
            }
            container[column][row] = in;
        }

        inline vec4yu<T> value(GLubyte column) {
            if (column > 3) {
                std::cerr << "ERROR: MATRIX: ARGUMENT OUT OF BOUNDS " << std::endl;
                return vec4yu<T>::ZERO();
            }
            return vec4yu<T>(container[column]);
        }
        inline void value(GLubyte column, vec4yu<T> in) {
            if (column > 3) {
                std::cerr << "ERROR: MATRIX: ARGUMENT OUT OF BOUNDS " << std::endl;
                return;
            }
            container[column] = in.container;
        }

        yuMatrix4x4() : container({ {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} }) {}

        yuMatrix4x4(const glm::mat<4, 4, T, glm::defaultp>& yeet) : container(yeet) {}

        yuMatrix4x4(const T arrayIn[4][4]) : container({ arrayIn[0], arrayIn[1], arrayIn[2], arrayIn[3] }) {}

        yuMatrix4x4(const yuMatrix4x4<T>& obj) : container(obj.container) { }

        static yuMatrix4x4<T> unit() {
            return yuMatrix4x4<T>({ {(T)1, (T)0, (T)0, (T)0}, {(T)0, (T)1, (T)0, (T)0}, {(T)0, (T)0, (T)1, (T)0}, {(T)0, (T)0, (T)0, (T)1} });
        }

        yuMatrix4x4<T> operator +(const yuMatrix4x4<T>& b) {
            return yuMatrix4x4(this->container + b.container);
        }
        yuMatrix4x4<T> operator +=(const yuMatrix4x4<T>& b) {
            this->container += b.container;
            return *this;
        }

        yuMatrix4x4<T> operator -(const yuMatrix4x4<T>& b) {
            return yuMatrix4x4(this->container - b.container);
        }
        yuMatrix4x4<T> operator -=(const yuMatrix4x4<T>& b) {
            this->container -= b.container;
            return *this;
        }


        yuMatrix4x4<T> operator *(const yuMatrix4x4<T>& b) {
            return yuMatrix4x4(this->container * b.container);
        }
        yuMatrix4x4<T> operator *=(const yuMatrix4x4<T>& b) {
            this->container *= b.container;
            return *this;
        }

        /// <summary>
        /// Returns a new vector. It is b transformed by the matrix on the left.
        /// </summary>
        /// <param name="b">Vector with the data to transform</param>
        /// <returns>A new vector that = matrix * b.</returns>
        vec4yu<T> operator *(const vec4yu<T> b) {
            return vec4yu<T>(this->container * b.container);
        }

        /// <summary>
        /// Transforms vector b by the matrix on the left.
        /// Saves the changes to vector b.
        /// </summary>
        /// <param name="b">Vector to be transformed.</param>
        /// <returns>Reference to the transformed vector.</returns>
        vec4yu<T>& operator *=(vec4yu<T>& b) {
            b = *this * b;
            return b;
        }
    };
}