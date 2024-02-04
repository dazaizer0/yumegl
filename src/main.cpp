#include "config.h"
#include "engine/render/triangle.h"
#include "engine/render/square.h"
#include "engine/input/input.h"
#include "engine/shader/shader.h"
#include "engine/render/texture.h"

// TODO: SWITCH TO GLM

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

int main() {
    // INITIALIZATION
    yumegl::init(WINDOW_WIDTH, WINDOW_HEIGHT, "Yume");
    yumegl::setColor(mathy::colorRGBA::BLACK());

    Shader textureShader( // path, path
        "/src/engine/shader/glshaders/texture/vertex_t.glsl",
        "/src/engine/shader/glshaders/texture/fragment_t.glsl"
    );

    Shader basicShader( // path, path
        "/src/engine/shader/glshaders/shape/vertex.glsl",
        "/src/engine/shader/glshaders/shape/fragment.glsl"
    );

    // SQUARE
    render::Square sq = render::Square(
        mathy::vec3{ -0.5f, -0.2f, 0.0f },
        mathy::colorRGBA::BLUE(),
        0.1f
    );

    // TEXTURE 
    render::Texture tex = render::Texture(
        "/assets/sonic.png", // win path
        mathy::vec3<float>{ -1.0f, 0.7f, 0.0f },
        mathy::colorRGBA::WHITE(),
        0.2f
    );
    bool right{true};

    std::cout << yumegl::yumePath() << '\n';

    // MAIN LOOP
    while (yumegl::isWindowOpen()) {
        // INPUT
        input::updateInput();

        if (input::keyPressed(GLFW_KEY_ESCAPE)) {
            yumegl::setWindowStatus(false);
        }

        if (input::keyPressed(GLFW_KEY_1)) {
            std::cerr << "Key pressed: 1\n";

            tex.position.x -= 0.1f;
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
        if (right) {
            tex.position.x += 0.0001f;
        } else {
            tex.position.x -= 0.0001f;
        }

        tex.rotateAroundOwnAxis(
                glm::vec3{(right ? 0.25f : -0.25f), (right ? 0.5f : -0.5f), (right ? 0.25f : -0.25f)},
                textureShader,
                1.32f
        );

        tex.updatePosition();
        tex.refresh();

        if (right && tex.position.x > 0.8f) {
            right = false;
        }
        else if (!right && tex.position.x < -0.8f) {
            right = true;
        }


        // RENDER
        glClear(GL_COLOR_BUFFER_BIT);

        tex.render(textureShader.ID);
        sq.render(basicShader.ID);
        
        yumegl::swapBuffersPollEvents();
    }

    // DE-INITIALIZATION
    sq.deleteData();
    tex.deleteData();

    glDeleteShader(textureShader.ID);
    glDeleteShader(basicShader.ID);

    yumegl::close();
    return 0;
}