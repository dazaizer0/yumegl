#include "config.h"
#include "yume.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int main() {
    // INITIALIZATION
    yumegl::init(WINDOW_WIDTH, WINDOW_HEIGHT, "Yume");
    yumegl::eFunc::setColor(mathy::colorRGBA::BLACK());

    // CAMERA
    object::Camera3D cam({0.0f, 0.0f, 3.0f}, WINDOW_WIDTH, WINDOW_HEIGHT);

    // DEPTH
    glEnable(GL_DEPTH_TEST);

    // OBJECTS
    shaderSystem::Shader default3DShader;
    default3DShader.genShader("texture/vertex_t3d.glsl", "texture/fragment_t3d.glsl");

    auto* cube = new render::Cube("textures/sonic_warning.png", glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(1.0f));
    cube->shader.genShader("texture/vertex_t3d.glsl", "texture/fragment_t3d.glsl");

    auto* room = new render::Cube("textures/sonic_dirt.png", glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(20.0f, 10.0f, 20.0f));

    auto* panel = new render::Square(glm::vec3(0.0f), {0.0f, 0.0f, 1.0f, 1.0f}, 0.5f);
    panel->shader.genShader("shape/vertex.glsl", "shape/fragment.glsl");
    bool active{false};

    cube->setWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    room->setWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    // MAIN LOOP
    while (yumegl::isWindowOpen()) {
        // INPUT SYSTEM
        input::updateInput();
        if (input::keyPressed(GLFW_KEY_ESCAPE)) {
            yumegl::setWindowStatus(false);
        }
        if (input::keyPressed(GLFW_KEY_C)) {
            cam.changeCursorVisibility();
        }

        // UPDATE
        yumegl::update();
        cam.update(yumegl::deltaTime);

        // RENDER
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ROOM
        default3DShader.use();

        cam.update(default3DShader);
        room->bindTexture();
        room->render_activeShader();
        room->setRotation_getShader(glm::vec3(0.1f, 0.1f, 0.1f), default3DShader, 0.1f);

        // CUBE
        cube->shader.use();
        cam.update(cube->shader);
        cube->bindTexture();
        cube->render_activeShader();
        cube->rotate(glm::vec3(0.4f, 0.5f, 0.4f), 1.0f);

        // PANEL
        if (!cam.active) {
            panel->shader.use();
            cam.update(panel->shader);
            panel->render();
        }

        // SWAP POLL EVENTS
        yumegl::swapBuffersPollEvents();

    }

    // DE-INITIALIZATION
    delete cube;
    delete room;
    delete panel;

    yumegl::eExit::close();

    return 0;
}
