#pragma once

#include "../../config.h"
#include <cstdlib>

namespace yumegl {
    // WINDOW
    unsigned int WINDOW_WIDTH{ 1280 };
    unsigned int WINDOW_HEIGHT{ 720 };

    GLFWwindow* _window;

    float deltaTime{};
    float lastFrame{};

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

        _window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, title.c_str(), nullptr, nullptr);

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
            std::cout << "GLAD initialized correctly\n";
        }

        glfwSwapInterval(1);
    }

    void update() {
        auto currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
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

    namespace eFunc {
        void setColor(const mathy::color& color) {
            glClearColor(color.r, color.g, color.b, color.a);
        }

        std::string yumePath() {
            std::filesystem::path executablePath = std::filesystem::absolute(std::filesystem::path(__FILE__));
            std::filesystem::path folderPath = executablePath.parent_path().parent_path().parent_path().parent_path();

            std::string result = folderPath.string();

            for (char& i : result) {
                if (i == '\\') {
                    i = '/';
                }
            }

            return result;
        }

        [[maybe_unused]] const char* convertToAsssetsPath(const std::string& path) {
            std::string path2 = yumegl::eFunc::yumePath() + "/assets/" + path;
            const char* result = path2.c_str();

            if (result == nullptr) {
                std::cerr << "ERROR:CONVERTING:PATH" << std::endl;
            }
            else {
                std::cout << "path converted correctly\n";
            }

            return result;
        }
    }

    namespace eExit {
        void close() {
            std::cerr << "Opengl has been successfully closed" << std::endl;
            glfwTerminate();
        }

        // void delete...(...) { ... }
    }
}