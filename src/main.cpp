#include "config.h"

#include "engine/render/triangle.h"
#include "engine/render/square.h"
#include "engine/render/texture.h"

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
    setColor(math::colorRGBA::BLACK());

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

    // TEXTURES
    rsq::square sq = rsq::square(
            math::vec3<float>::CUSTOM(0.4f, -0.2f, 0.0f),
            0.4f,
            math::colorRGBA::GREEN()
	);


    // MAIN LOOP
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        sq.draw();
        glfwSwapBuffers(window);
    }

    // DE-INITIALIZE
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    sq.del();

    glfwTerminate();
    return 0;
}