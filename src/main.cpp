#include "config.h"

#include "engine/render/triangle.h"
#include "engine/render/square.h"
#include "engine/input/input.h"
#include "engine/shader/shader.h"

#include "engine/render/texture.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

int main() {
    // INITIALIZATION
    GL::init(WINDOW_WIDTH, WINDOW_HEIGHT, "Yume");
    setColor(mathy::colorRGBA::BLACK());

    // SHADERS
    shader::Shader shader = shader::Shader(
            "C:/Users/mydat/Documents/_active_c/_cpp/YumeGl/yumegl/src/engine/shader/shader_scripts/vertex.glsl",
            "C:/Users/mydat/Documents/_active_c/_cpp/YumeGl/yumegl/src/engine/shader/shader_scripts/fragment.glsl"
    );

    shader::Shader texturesShader = shader::Shader(
        "C:/Users/mydat/Documents/_active_c/_cpp/YumeGl/yumegl/src/engine/shader/shader_scripts/vertex_t.glsl",
        "C:/Users/mydat/Documents/_active_c/_cpp/YumeGl/yumegl/src/engine/shader/shader_scripts/fragment_t.glsl"
    );

    // LOAD TEXTURE
    render::Texture tex = render::Texture(
            mathy::vec3 {-0.5f, 0.2f, 0.0f},
            mathy::colorRGBA::BLUE(),
            0.4f
    );

    // SQUARE
    render::Square squ = render::Square(
        mathy::vec3{ -0.5f, -0.2f, 0.0f },
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
        squ.renderSquare();

        texturesShader.useShader();
        tex.renderTexture();

        GL::swapBuffersPollEvents();
    }

    // DE-INITIALIZATION
    shader.deleteShader();

    squ.deleteData();
    tex.deleteData();

    GL::cleanup();

    return 0;
}