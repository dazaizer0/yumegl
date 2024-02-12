#include "config.h"
#include "yume.h"
#include "engine/rd1/texture.hpp"

int main() {
#pragma region INITIALIZATION
    /* ------------------------------------------------
    * ---------------- INITIALIZATION -----------------
    * ------------------------------------------------ */
    yumegl::init("Yume");
    yumegl::eFunc::setColor(mathy::color::BLACK());

    // CAMERA
    object::Camera3D cam({0.0f, 0.0f, 3.0f}, yumegl::WINDOW_WIDTH, yumegl::WINDOW_HEIGHT);

    // DEPTH
    glEnable(GL_DEPTH_TEST);

    // OBJECTS
    shaderSystem::Shader default3DShader;
    default3DShader.genShader("texture/vertex_t3d.glsl", "texture/fragment_t3d.glsl");

    auto* cube = new rd1::Cube("textures/sonic_warning.png", glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(1.0f));
    cube->shader.genShader("texture/vertex_t3d.glsl", "texture/fragment_t3d.glsl");

    auto* room = new rd1::Cube("textures/sonic_dirt.png", glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(20.0f, 10.0f, 20.0f));
    auto* room1 = new rd1::Cube("textures/sonic_ice.png", glm::vec3(0.0f, 5.0f, -30.1f), glm::vec3(10.0f, 10.0f, 10.0f));

    auto* panel = new rd1::Texture("textures/sonic_ice.png", glm::vec3{ 0.0f }, mathy::color{ 0.0f, 0.0f, 0.0f, 1.0f }, glm::vec2{ 0.8f, 0.8f });
    panel->shader.genShader("texture/vertex_t.glsl", "texture/fragment_t.glsl");

    cube->setWindowSize(yumegl::WINDOW_WIDTH, yumegl::WINDOW_HEIGHT);
    room->setWindowSize(yumegl::WINDOW_WIDTH, yumegl::WINDOW_HEIGHT);
    room1->setWindowSize(yumegl::WINDOW_WIDTH, yumegl::WINDOW_HEIGHT);
#pragma endregion

#pragma region MAIN_LOOP
    /* ------------------------------------------------
    * ------------------ MAIN LOOP --------------------
    * ------------------------------------------------ */
    while (yumegl::isWindowOpen()) {
        // UPDATE
        yumegl::update();
        input::update();
        cam.update(yumegl::deltaTime);

        // INPUT SYSTEM
        if (input::keyPressed(GLFW_KEY_ESCAPE))
            yumegl::setWindowStatus(false);

        if (input::keyPressed(GLFW_KEY_C))
            cam.changeCursorVisibility();

        /* ------------------------------------------------
         * ------------------- RENDER ---------------------
         * ------------------------------------------------ */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ROOM
        default3DShader.use();

        cam.update(default3DShader);
        room->bindTexture();
        room->render_foregoingShader();
        room->setRotation_getShader(glm::vec3(0.1f, 0.1f, 0.1f), default3DShader, 0.1f);

        cam.update(default3DShader);
        room1->bindTexture();
        room1->render_foregoingShader();
        room1->setRotation_getShader(glm::vec3(0.1f, 0.1f, 0.1f), default3DShader, 0.1f);

        // CUBE
        cube->shader.use();
        cam.update(cube->shader);
        cube->bindTexture();
        cube->render_foregoingShader();
        cube->rotate(glm::vec3(0.4f, 0.5f, 0.4f), 1.0f);

        // GUI
        if (!cam.active) {
            cam.update(panel->shader);
            panel->bindTexture();
            panel->render_ownShader();
            panel->setRotation(glm::vec3(0.0f, 0.0f, 1.0f), 180.0f);
        }

        // SWAP POLL EVENTS
        yumegl::swapBuffersPollEvents();
    }
#pragma endregion

#pragma region DE_INITIALIZATION
    /* ------------------------------------------------
    * -------------- DE-INITIALIZATION ----------------
    * ------------------------------------------------ */
    delete cube;
    delete room;
    delete room1;
    delete panel;

    shaderSystem::deleteShader(default3DShader);
    yumegl::eExit::close();

    return 0;
#pragma endregion
}
