#include "config.h"

#include "engine/render/triangle.h"
#include "engine/render/square.h"
#include "engine/input/input.h"
#include "engine/shader/shader.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

namespace yumeEngine {
    void gameInit() {

    }

    void gameUpdate() {

    }

    void gameDeInit() {

    }
}

int main() {
    // INITIALIZATION
    GL::init(WINDOW_WIDTH, WINDOW_HEIGHT, "Yume");
    setColor(mathy::colorRGBA::BLACK());

    // SHADERS
    shader::Shader shader = shader::Shader(
            "C:/Users/mydat/Documents/_active_c/_cpp/YumeGl/yumegl/src/engine/shader/shader_scripts/vertex.glsl",
            "C:/Users/mydat/Documents/_active_c/_cpp/YumeGl/yumegl/src/engine/shader/shader_scripts/fragment.glsl"
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
    while (GL::windowIsOpen()) {
        // UPDATE
        // TODO: SOME COOL STUFF

        // INPUT
        input::updateInput();

        if (input::keyPressed(GLFW_KEY_ESCAPE)) {
            GL::setWindowShouldClose(true);
        }

        if (input::keyPressed(GLFW_KEY_1)) {
            std::cerr << "Key pressed: 1\n";
        }
        else if (input::keyDown(GLFW_KEY_2)) {
            std::cerr << "Key down: 2\n";
        }

        // RENDER
        glClear(GL_COLOR_BUFFER_BIT);
        shader.useShader();

        // RENDER OBJECTS
        triangle_obj.renderTriangle();
        square_obj.renderSquare();

        GL::swapBuffersPollEvents();
    }

    // DE-INITIALIZATION
    shader.deleteShader();

    triangle_obj.deleteData();
    square_obj.deleteData();

    GL::cleanup();

    return 0;
}