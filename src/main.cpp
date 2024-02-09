#include "config.h"
#include "yume.h"
#include "engine/objects/camera.h"

const unsigned int WINDOW_WIDTH = 1280;
const unsigned int WINDOW_HEIGHT = 720;

int main() {
    // INITIALIZATION
    yumegl::init(WINDOW_WIDTH, WINDOW_HEIGHT, "Yume");
    yumegl::eFunc::setColor(mathy::colorRGBA::BLACK());

    // CAMERA
    object::Camera3D cam = object::Camera3D(WINDOW_WIDTH, WINDOW_HEIGHT);

    // DEPTH AND SHADERS
    glEnable(GL_DEPTH_TEST);

    Shader iceShader(
        "texture/vertex_t3d.glsl",
        "texture/fragment_t3d.glsl"
    );
    Shader dirtShader(
        "texture/vertex_t3d.glsl",
        "texture/fragment_t3d.glsl"
    );

    // OBJECTS
    render::Cube ice = render::Cube(
        "textures/sonic_ice.png",
        glm::vec3 {0.0f, 0.0f, -3.0f},
        glm::vec3 {1.0f, 1.0f, 1.0f}
    );

    render::Cube dirt = render::Cube(
        "textures/sonic_dirt.png",
        glm::vec3 {0.0f, 0.0f, -7.0f},
        glm::vec3 {1.0f, 1.0f, 1.0f}
    );

    ice.setWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    dirt.setWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    // MAIN LOOP
    while (yumegl::isWindowOpen()) {
        // DELTA TIME
        yumegl::update();

        // INPUT SYSTEM
        input::updateInput();
        if (input::keyPressed(GLFW_KEY_ESCAPE)) {
            yumegl::setWindowStatus(false);
        }
        if (input::keyPressed(GLFW_KEY_C)) {
            cam.changeCursorVisibility();
        }

        cam.updateCameraInput(yumegl::deltaTime);

        // RENDER
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ICE CUBE
        cam.update(iceShader);
        ice.render(iceShader);
        ice.rotate(
            glm::vec3{0.4f, 0.5f, 0.4f},
            iceShader,
            1.0f
        );

        // DIRT CUBE
        cam.update(dirtShader);
        dirt.render(dirtShader);
        dirt.setRotation(
            glm::vec3{0.4f, 0.5f, 0.4f},
            dirtShader,
            1.0f
        );

        // SWAP POLL EVENTS
        yumegl::swapBuffersPollEvents();
    }
    // DE-INITIALIZATION
    glDeleteShader(iceShader.ID);
    glDeleteShader(dirtShader.ID);

    ice.deleteData();
    dirt.deleteData();

    yumegl::eExit::close();

    return 0;
}
