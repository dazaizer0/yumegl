#include "config.h"
#include "yume.h"

int main() {
#pragma region INITIALIZATION
    /* ------------------------------------------------
    * ---------------- INITIALIZATION -----------------
    * ------------------------------------------------- */

    // I had to bring my son back to life v^v^v^v^v^
    // texture had come back to templates

    yumegl::init("Yume");
    yumegl::eFunc::setColor(colour::BLACK());

    // CAMERA
    object::Camera3D cam({ 0.0f, 0.0f, 3.0f }, yumegl::WINDOW_WIDTH, yumegl::WINDOW_HEIGHT, false);

    // DEPTH
    glEnable(GL_DEPTH_TEST);

    // OBJECTS
    shaderSystem::Shader default3DShader;
    default3DShader.genShader("texture/vertex_t3d.glsl", "texture/fragment_t3d.glsl");

    auto* cube = new rd1::Cube("textures/sonic_warning.png", glm::vec3{ 0.0f, 0.0f, -3.0f }, glm::vec3{ 1.0f });
    cube->shader.genShader("texture/vertex_t3d.glsl", "texture/fragment_t3d.glsl");
    cube->setWindowSize(yumegl::WINDOW_WIDTH, yumegl::WINDOW_HEIGHT);

    auto* room = new rd1::Cube("textures/sonic_dirt.png", glm::vec3{ 0.0f, 5.0f, 0.0f }, glm::vec3{ 20.0f, 10.0f, 20.0f });
    room->setWindowSize(yumegl::WINDOW_WIDTH, yumegl::WINDOW_HEIGHT);

    auto* room1 = new rd1::Cube("textures/sonic_ice.png", glm::vec3{ 0.0f, 5.0f, -30.1f }, glm::vec3{ 10.0f, 10.0f, 10.0f });
    room1->setWindowSize(yumegl::WINDOW_WIDTH, yumegl::WINDOW_HEIGHT);

    auto* panel = new rd1::Texture("textures/sonic_ice.png", glm::vec3{ 0.0f }, colour{ 0.0f, 0.0f, 0.0f, 1.0f }, glm::vec2{ 0.8f, 0.8f });
    panel->shader.genShader("texture/vertex_t.glsl", "texture/fragment_t.glsl");

#pragma endregion

#pragma region MAIN_LOOP
    /* ------------------------------------------------
    * ------------------ MAIN LOOP --------------------
    * ------------------------------------------------ */
    int frameCounter = 0;
    auto startTime = std::chrono::high_resolution_clock::now();

    while (yumegl::isWindowOpen()) {
        auto frameStartTime = std::chrono::high_resolution_clock::now();

        // UPDATE
        yumegl::update();
        input::update();
        cam.update(yumegl::deltaTime);

        // INPUT SYSTEM
        if (input::keyPressed(GLFW_KEY_ESCAPE))
            yumegl::setWindowStatus(false);

        /* ------------------------------------------------
         * ------------------- RENDER ---------------------
         * ------------------------------------------------ */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ROOM
        default3DShader.use();

        cam.update(default3DShader);
        room->bindTexture();
        room->render_foregoingShader();
        room->setRotation_getShader(glm::vec3{ 0.1f, 0.1f, 0.1f }, default3DShader, 0.1f);

        cam.update(default3DShader);
        room1->bindTexture();
        room1->render_foregoingShader();
        room1->setRotation_getShader(glm::vec3{ 0.1f, 0.1f, 0.1f }, default3DShader, 0.1f);

        // CUBE
        cube->shader.use();
        cam.update(cube->shader);
        cube->bindTexture();
        cube->render_ownShader();
        cube->rotate(glm::vec3{ 0.6f, 0.8f, 0.6f }, 1.0f);

        // GUI
        if (!cam.active) {
            panel->bindTexture();
            panel->render_ownShader();
            panel->setRotation(glm::vec3{ 0.0f, 0.0f, 1.0f }, 180.0f);
        }

        // SWAP POLL EVENTS
        yumegl::swapBuffersPollEvents();

        /* ------------------------------------------------
         * -------------------- STATS ---------------------
         * ------------------------------------------------ */
        frameCounter++;

        if (frameCounter == 60) {
            auto endTime = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
            std::cout << "\nThe time it takes to generate 60 frames: >" << duration.count() << "< ms\n";
            std::cout << "The limit od milliseconds to generate 60 frames: >960/1000<\n";

            frameCounter = 0;
            startTime = std::chrono::high_resolution_clock::now();
        }

        auto frameEndTime = std::chrono::high_resolution_clock::now();
        auto frameDuration = std::chrono::duration_cast<std::chrono::milliseconds>(frameEndTime - frameStartTime);
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
