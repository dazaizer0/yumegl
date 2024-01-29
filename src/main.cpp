#include "config.h"

#include "engine/render/triangle.h"
#include "engine/render/square.h"
#include "engine/render/texture.h"

#include "engine/input/input.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

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

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "YumeGL!", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << ">> ERROR::OPENGL::COULDN'T LOAD >> " << std::endl;
        glfwTerminate();
        return -1;
    }
    else {
        std::cout << "- opengl loaded correctly.\n";
    }
#pragma endregion initialize
    setColor(mathy::colorRGBA::BLACK());

    // SHADERS
#pragma region shaders

    // VERTEX SHADER
    const char *vertexShaderSource =
#include "engine/shader/vertex.vs"
        ;

    unsigned int vertexShader;

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int  success;
    char infoLog[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << ">> ERROR::SHADER::VERTEX::COMPILATION_FAILED >> " << infoLog << std::endl;
    }
    else {
        std::cout << "- vertex shader loaded correctly.\n";
    }

    // FRAGMENT SHADER
    const char *fragmentShaderSource =
#include "engine/shader/fragment.vs"
    ;

    unsigned int fragmentShader;

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // COMPLETE SHADER
    unsigned int shader;

    shader = glCreateProgram();

    glAttachShader(shader, vertexShader);
    glAttachShader(shader, fragmentShader);
    glLinkProgram(shader);

    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shader, 512, NULL, infoLog);
        std::cerr << ">> ERROR::SHADER::FRAGMENT::COMPILATION_FAILED >> " << infoLog << std::endl;
    }
    else {
        std::cout << "- fragment shader loaded correctly.\n";
    }

#pragma endregion shaders
    // END SHADERS

    // TRIANGLE
    render::triangle triangle_object = render::triangle(
            mathy::vec3<float>::ZERO(),
            mathy::colorRGBA::WHITE(),
            0.4f
    );

    // MAIN LOOP
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        if (input::isKeyClicked('E')) {
            std::cerr << "- closing program..." << std::endl;
            break;
        }

        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader);

        // RENDER OBJECTS
        triangle_object.render_triangle();

        glfwSwapBuffers(window);
    }

    // DE-INITIALIZE
    std::cerr << "- program has been closed." << std::endl;

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    triangle_object.remove_data();

    glfwTerminate();
    return 0;
}