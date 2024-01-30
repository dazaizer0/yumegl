#include "config.h"

#include "engine/render/triangle.h"
#include "engine/render/square.h"
#include "engine/input/input.h"

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
    setColor(mathy::colorRGBA::BLACK());

    // SHADERS
#pragma region shaders

    // VERTEX SHADER
    const char *vertexShaderSource =
#include "engine/shader/vertex.vs"
        ;

    unsigned int vertex_shader;

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertex_shader);

    int  success;
    char infoLog[512];

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertex_shader, 512, nullptr, infoLog);
        std::cerr << ">> ERROR::SHADER::VERTEX::COMPILATION_FAILED >> " << infoLog << std::endl;
    }
    else {
        std::cout << "- vertex shader loaded correctly.\n";
    }

    // FRAGMENT SHADER
    const char *fragment_shader_source =
#include "engine/shader/fragment.vs"
    ;

    unsigned int fragment_shader;

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr);
    glCompileShader(fragment_shader);

    // COMPLETE SHADER
    unsigned int shader;

    shader = glCreateProgram();

    glAttachShader(shader, vertex_shader);
    glAttachShader(shader, fragment_shader);
    glLinkProgram(shader);

    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << ">> ERROR::SHADER::FRAGMENT::COMPILATION_FAILED >> " << infoLog << std::endl;
    }
    else {
        std::cout << "- fragment shader loaded correctly.\n";
    }

#pragma endregion shaders
    // END SHADERS

    // TRIANGLE
    render::triangle triangle_obj = render::triangle(
            mathy::vec3 {0.5f, -0.2f, 0.0f},
            mathy::colorRGBA::GREEN(),
            0.4f
    );

    // SQUARE
    render::square square_obj = render::square(
        mathy::vec3 {-0.5f, 0.2f, 0.0f},
        mathy::colorRGBA::BLUE(),
        0.4f
    );

    // MAIN LOOP
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

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

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    triangle_obj.remove_data();
    square_obj.remove_data();

    glfwTerminate();
    return 0;
}