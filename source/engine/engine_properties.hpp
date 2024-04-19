#ifndef YUMEGL_MP_ENGINE_PROPERTIES_HPP
#define YUMEGL_MP_ENGINE_PROPERTIES_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb/stb_image.h>

#include "../config.h"
#include "../yume_elementary.h"

namespace yumegl {
    // WINDOW
    unsigned int WINDOW_WIDTH{ 1280 };
    unsigned int WINDOW_HEIGHT{ 720 };

    unsigned int GRID{ 1 };

    GLFWwindow* _window;

    float dupaTime{};
    float lastFrame{};

    void setWindowSize(unsigned int width, unsigned int height) {
        WINDOW_WIDTH = width;
        WINDOW_HEIGHT = height;
    }

    void init(const std::string& title) {
        // GAME WINDOW INITIALIZATION
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

        _window = glfwCreateWindow((int)WINDOW_WIDTH, (int)WINDOW_HEIGHT, title.c_str(), nullptr, nullptr);

        if (_window == nullptr) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }
        else {
            std::cout << "GLFW window created correctly" << std::endl;
        }

        glfwMakeContextCurrent(_window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD\n";
            return;
        }
        else {
            std::cout << "GLAD initialized correctly\n> yumegl2 0.0.1 <\n";
        }

        glfwSwapInterval(1);
        std::cout << std::flush;
    }

    void update() {
        auto currentFrame = static_cast<float>(glfwGetTime());
        dupaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    }

    GLFWwindow* getWindowPointer() {
        return _window;
    }

    bool isWindowOpen() {
        return !glfwWindowShouldClose(_window);
    }

    void setWindowStatus(bool value) {
        glfwSetWindowShouldClose(_window, !value);
    }

    void swapBuffersPollEvents() {
        glfwSwapBuffers(_window);
        glfwPollEvents();
    }

    namespace eExit { // ENGINE'S PROCESS TERMINATION FUNCTIONS
        void close() {
            std::cout << "Opengl has been successfully closed" << std::endl;

            glfwTerminate();
        }

        // void delete...(...) { ... }
    }
}

#endif
