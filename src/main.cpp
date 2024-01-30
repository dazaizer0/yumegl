#include "config.h"

#include "engine/render/triangle.h"
#include "engine/render/square.h"
#include "engine/input/input.h"
#include "engine/shader/shader.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

int main() {
    // INITIALIZE
#pragma region initialize
    GLFWwindow* window;

    if (!glfwInit()) {
        std::cerr << ">> ERROR::GLFW::INITIALIZATION >> " << std::endl;
        return -1;
    }
    else {
        std::cout << "- glfw initialized correctly.\n";
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "YumeGL!", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << ">> ERROR::OPENGL::COULDN'T_LOAD >> " << std::endl;
        glfwTerminate();
        return -1;
    }
    else {
        std::cout << "- opengl loaded correctly.\n";
    }
#pragma endregion initialize

    // SCREEN COLOR
    setColor(mathy::colorRGBA::BLACK());

    // SHADERS
    unsigned int shader = shader::make_shader(
            "C:/Users/mydat/Documents/_active_c/_cpp/YumeGl/yumegl/src/engine/shader/shader_scripts/vertex.txt",
            "C:/Users/mydat/Documents/_active_c/_cpp/YumeGl/yumegl/src/engine/shader/shader_scripts/fragment.txt"
    );

    // TRIANGLE
    render::Triangle triangle_obj = render::Triangle(
            mathy::vec3 {0.5f, -0.2f, 0.0f},
            mathy::colorRGBA::GREEN(),
            0.4f
    );

    // SQUARE
    render::Square square_obj = render::Square(
        mathy::vec3 {-0.5f, 0.2f, 0.0f},
        mathy::colorRGBA::BLUE(),
        0.4f
    );

    // MAIN LOOP
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // INPUT
        if (input::isKeyClicked('P')) { break; }

        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader);

        // RENDER OBJECTS
        triangle_obj.render_triangle();
        square_obj.render_square();

        glfwSwapBuffers(window);
    }

    // DE-INITIALIZE
    std::cout << std::endl;
    std::cerr << "- program has been closed.\n";

    glDeleteShader(shader);

    triangle_obj.remove_data();
    square_obj.remove_data();

    glfwTerminate();
    return 0;
}