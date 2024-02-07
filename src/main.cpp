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
        mathy::vec3<float> {0.0f, 0.0f, -3.0f},
        mathy::vec3<float> {0.5f, 0.5f, 0.5f}
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
        /*cube.rotate(
                mathy::vec3<float>{0.3f, 0.4f, 0.3f},
                cubeShader,
                1.2f
        );*/

        cube.setRotation(
                mathy::vec3<float>{1.0f, 0.0f, 0.2f},
                cubeShader,
                30.0f
        );

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