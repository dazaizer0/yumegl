#pragma once

#include "../../config.h"

namespace yumegl {
    // WINDOW
    GLFWwindow* _window;

    void init(int width, int height, const std::string& title) {
        // GAME WINDOW INITIALIZATION
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

        _window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

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
            std::cout << "Failed to initialize GLAD\n";
            return;
        }
        else {
            std::cout << "GLAD initialized correctly\n";
        }
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

    void close() {
        std::cerr << "Opengl has been successfully closed" << std::endl;
        glfwTerminate();
    }

    // OTHER
    void setColor(const mathy::colorRGBA& color) {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    std::string yumePath() {
        std::filesystem::path executablePath = std::filesystem::absolute(std::filesystem::path(__FILE__));
        std::filesystem::path folderPath = executablePath.parent_path().parent_path().parent_path().parent_path();

        std::string result = folderPath.string();

        for (char & i : result) {
            if (i == '\\') {
                i = '/';
            }
        }

        return result;
    }
}