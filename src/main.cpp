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
    gl::init(WINDOW_WIDTH, WINDOW_HEIGHT, "Yume");
    setColor(mathy::colorRGBA::BLACK());

    // SHADERS
    shader::Shader shader = shader::Shader(
        "C:/Users/mydat/Documents/_active_c/_cpp/YumeGl/yumegl/src/engine/shader/glshaders/vertex.glsl",
        "C:/Users/mydat/Documents/_active_c/_cpp/YumeGl/yumegl/src/engine/shader/glshaders/fragment.glsl"
    );

    shader::Shader texturesShader = shader::Shader(
        "C:/Users/mydat/Documents/_active_c/_cpp/YumeGl/yumegl/src/engine/shader/glshaders/vertex_t.glsl",
        "C:/Users/mydat/Documents/_active_c/_cpp/YumeGl/yumegl/src/engine/shader/glshaders/fragment_t.glsl"
    );

    // SQUARE
    render::Square sq = render::Square(
        mathy::vec3{ -0.5f, -0.2f, 0.0f },
        mathy::colorRGBA::BLUE(),
        0.4f
    );

    // TEXTURE
    render::Texture tex = render::Texture(
        "C:/Users/mydat/Documents/_active_c/_cpp/YumeGl/yumegl/assets/sonic.png",
        mathy::vec3<float>::ZERO(),
        mathy::colorRGBA::WHITE(),
        0.8f
    );

    // MAIN LOOP
    while (gl::isWindowOpen()) {
        // UPDATE
        // TODO: SOME COOL STUFF

        // INPUT
        input::updateInput();

        if (input::keyPressed(GLFW_KEY_ESCAPE)) {
            gl::setWindowStatus(false);
        }

        if (input::keyPressed(GLFW_KEY_1)) {
            std::cerr << "Key pressed: 1\n";
        }
        else if (input::keyDown(GLFW_KEY_2)) {
            std::cerr << "Key down: 2\n";
        }

        // RENDER
        glClear(GL_COLOR_BUFFER_BIT);

        tex.renderTexture(texturesShader.getShader()); // TEXTURE
        sq.renderSquare(shader.getShader()); // SQUARE
        
        gl::swapBuffersPollEvents();
    }

    // DE-INITIALIZATION
    shader.deleteShader();
    texturesShader.deleteShader();

    sq.deleteData();
    tex.deleteData();

    gl::close();

    return 0;
}