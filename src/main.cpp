#include "config.h"
#include "yume.h"

const unsigned int WINDOW_WIDTH = 1280;
const unsigned int WINDOW_HEIGHT = 720;

int main() {
    // INITIALIZATION
    yumegl::init(WINDOW_WIDTH, WINDOW_HEIGHT, "Yume");
    yumegl::eFunc::setColor(mathy::colorRGBA::BLACK());

    // CAMERA
    object::Camera3D cam({0.0f, 0.0f, 3.0f}, WINDOW_WIDTH, WINDOW_HEIGHT);

    // DEPTH
    glEnable(GL_DEPTH_TEST);

    // OBJECTS
    auto* cube = new render::Cube("textures/sonic_warning.png", glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(1.0f));
    cube->shader.genShader("texture/vertex_t3d.glsl", "texture/fragment_t3d.glsl");

    auto* room = new render::Cube("textures/sonic_dirt.png", glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(20.0f, 10.0f, 20.0f));
    room->shader.genShader("texture/vertex_t3d.glsl", "texture/fragment_t3d.glsl");

    cube->setWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    room->setWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    // MAIN LOOP
    while (yumegl::isWindowOpen()) {
        // UPDATE
        yumegl::update();
        cam.update(yumegl::deltaTime);

        // INPUT SYSTEM
        input::updateInput();
        if (input::keyPressed(GLFW_KEY_ESCAPE)) {
            yumegl::setWindowStatus(false);
        }
        if (input::keyPressed(GLFW_KEY_C)) {
            cam.changeCursorVisibility();
        }

        // RENDER
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // CUBE
        cam.update(cube->shader);
        cube->render();
        cube->rotate(glm::vec3(0.4f, 0.5f, 0.4f), 1.0f);
        
        // ROOM
        cam.update(room->shader);
        room->render();
        room->setRotation(glm::vec3(0.1f, 0.1f, 0.1f), 0.1f);

        // SWAP POLL EVENTS
        yumegl::swapBuffersPollEvents();
    }
    // DE-INITIALIZATION
    delete cube;
    delete room;

    yumegl::eExit::close();

    return 0;
}
