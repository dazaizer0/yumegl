#include "config.h"
#include "yume.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

int main() {
    // INITIALIZATION
    yumegl::init(WINDOW_WIDTH, WINDOW_HEIGHT, "Yume");
    yumegl::eFunc::setColor(mathy::colorRGBA::BLACK());

    // IMGUI INITIALIZATION
    yumeImGui::init();

    // SHADER
    glEnable(GL_DEPTH_TEST);

    Shader cubeShader(
        "texture/vertex_t3d.glsl",
        "texture/fragment_t3d.glsl"
    );

    // CUBE
    render::Cube cube = render::Cube(
        "textures/sonic_dirt.png",
        0.6f
    );

    cube.setWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    // MAIN LOOP
    while (yumegl::isWindowOpen()) {
        // INPUT SYSTEM
        input::updateInput();
        if (input::keyPressed(GLFW_KEY_ESCAPE)) {
            yumegl::setWindowStatus(false);
        }

        // RENDER
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cube.render(cubeShader);
        cube.rotate(cubeShader);

        yumeImGui::cube::yumeImGui_CreateFrame(cube);

        // SWAP POLL EVENTS
        yumegl::swapBuffersPollEvents();
    }

    // DE-INITIALIZATION
    yumeImGui::clear();

    glDeleteShader(cubeShader.ID);
    cube.deleteData();

    yumegl::eExit::close();
    return 0;
}