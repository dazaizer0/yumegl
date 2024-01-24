#include "config.h"
#include "stb/stb_image.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

int main() {
    // INITIALIZE
    GLFWwindow* window;

    if (!glfwInit()) {
        return -1;
    }
    else {
        std::cout << "glfw initialized correctly.\n";
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "YumeGL!", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Couldn't load opengl" << std::endl;
        glfwTerminate();
        return -1;
    }
    else {
        std::cout << "opengl loaded correctly.\n";
    }

    setColor(math::color4::BLACK()); // black

    // MAIN LOOP
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    // DE-INITIALIZE
    glfwTerminate();

    return 0;
}