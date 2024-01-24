#include "config.h"

#include "engine/render/triangle.h"
#include "engine/render/square.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

int main() {
    // INITIALIZE
#pragma region initialize
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
#pragma endregion initialize
    setColor(math::color4::BLACK()); // black

    //SHADERS
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
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    else {
        std::cout << "VERTEX SHADER LOADED CORRECTLY\n";
    }

    // FRAGMENT SHADER
    const char *fragmentShaderSource =
#include "engine/shader/fragment.vs"
    ;

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    else {
        std::cout << "FRAGMENT SHADER LOADED CORRECTLY\n";
    }

#pragma endregion shaders

    // TRIANGLE
    rt::triangle tr = rt::triangle(
            math::vec3<float>::CUSTOM(0.2f, 0.3f, 0.0f),
            0.1f,
            math::color4::RED()
    );

    rs::square sq = rs::square(
            math::vec3<float>::CUSTOM(-0.2f, -0.3f, 0.0f),
            0.2f,
            math::color4::GREEN()
    );

    // MAIN LOOP
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        glUseProgram(shaderProgram);

        tr.draw();
        sq.draw();

        glfwSwapBuffers(window);
    }

    // DE-INITIALIZE
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    tr.del();
    sq.del();

    glfwTerminate();
    return 0;
}