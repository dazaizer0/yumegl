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

    Shader textureShader(
        "C:/Users/mydat/Documents/_active_c/_cpp/YumeGl/yumegl/src/engine/shader/glshaders/vertex_t.glsl",
        "C:/Users/mydat/Documents/_active_c/_cpp/YumeGl/yumegl/src/engine/shader/glshaders/fragment_t.glsl"
    );

    Shader basicShader(
        "C:/Users/mydat/Documents/_active_c/_cpp/YumeGl/yumegl/src/engine/shader/glshaders/vertex.glsl",
        "C:/Users/mydat/Documents/_active_c/_cpp/YumeGl/yumegl/src/engine/shader/glshaders/fragment.glsl"
    );

    // SQUARE
    render::Square sq = render::Square(
        mathy::vec3{ -0.5f, -0.2f, 0.0f },
        mathy::colorRGBA::BLUE(),
        0.1f
    );

    // TEXTURE 
    render::Texture tex = render::Texture(
        "C:/Users/mydat/Documents/_active_c/_cpp/YumeGl/yumegl/assets/sonic.png",
        mathy::vec3<float>{ -1.0f, 0.7f, 0.0f },
        mathy::colorRGBA::WHITE(),
        0.2f
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

            tex.position.x += 0.1f;
            tex.updatePosition();
            tex.refresh();
        }
        else if (input::keyDown(GLFW_KEY_2)) {
            std::cerr << "Key down: 2\n";
        }

        if (input::keyDown(GLFW_KEY_D) && sq.position.x < 1.0f - sq.size) {
            sq.position.x += 0.001f;
            sq.updatePosition();
            sq.refresh();
        }
        else if (input::keyDown(GLFW_KEY_A) && sq.position.x > -1.0f + sq.size) {
            sq.position.x -= 0.001f;
            sq.updatePosition();
            sq.refresh();
        }
        if (input::keyDown(GLFW_KEY_W) && sq.position.y < 1.0f - sq.size) {
            sq.position.y += 0.001f;
            sq.updatePosition();
            sq.refresh();
        }
        else if (input::keyDown(GLFW_KEY_S) && sq.position.y > -1.0f + sq.size) {
            sq.position.y -= 0.001f;
            sq.updatePosition();
            sq.refresh();
        }

        // TEXTURE TRANSFORMATIONS
        if (tex.position.x < 0.7f) {
            tex.position.x += 0.0001f;
            tex.updatePosition();
            tex.refresh();
        }
        tex.rotateAroundOwnAxis(
            glm::vec3{ 0.0f, 0.0f, 1.0f },
            textureShader,
            1.0f
        );
        tex.refresh();

        // RENDER
        glClear(GL_COLOR_BUFFER_BIT);

        tex.render(textureShader.ID);
        sq.render(basicShader.ID);
        
        gl::swapBuffersPollEvents();
    }

    // DE-INITIALIZATION

    sq.deleteData();
    tex.deleteData();

    gl::close();

    return 0;
}