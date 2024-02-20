#include "config.h"
#include "yume.h"
#include "project.h"

int main() {
#pragma region INITIALIZATION
    /* ------------------------------------------------
    * ---------------- INITIALIZATION -----------------
    * ------------------------------------------------- */
    yumegl::init("Yume");
    yumegl::eFunc::setColor(colour::BLACK());

    // CAMERA
    object::Camera3D cam({ 0.0f, 4.0f, 3.0f }, yumegl::WINDOW_WIDTH, yumegl::WINDOW_HEIGHT, false);

    // DEPTH
    glEnable(GL_DEPTH_TEST);

    // OBJECTS
    shaderSystem::Shader default3DShader;
    default3DShader.genShader("../assets/shaders/3D/vertex.glsl", "../assets/shaders/3D/fragment.glsl");

    auto* cube = new rd1::Cube("../assets/textures/sonic_disco.png", glm::vec3{ 0.0f, 4.0f, -3.0f }, glm::vec3{ 1.0f });
    cube->shader.genShader("../assets/shaders/3D/vertex.glsl", "../assets/shaders/3D/fragment.glsl");
    cube->setWindowSize(yumegl::WINDOW_WIDTH, yumegl::WINDOW_HEIGHT);

    auto* room = new rd1::Cube("../assets/textures/sonic_forest.png", glm::vec3{ 0.0f, 5.0f, 0.0f }, glm::vec3{ 20.0f, 10.0f, 20.0f });
    room->setWindowSize(yumegl::WINDOW_WIDTH, yumegl::WINDOW_HEIGHT);

    auto* floor = new rd1::Cube("../assets/textures/sonic_floor.png", glm::vec3{ 0.0f, -5.0f, 0.0f }, glm::vec3{ 20.0f, 0.1f, 20.0f });
    floor->setWindowSize(yumegl::WINDOW_WIDTH, yumegl::WINDOW_HEIGHT);

    auto* panel = new rd1::Texture("../assets/textures/sonic_ice.png", mathy::vec3yu<>{ 0.0f, 0.0f, 0.0f }, colour{ 0.0f, 0.0f, 0.0f, 1.0f }, mathy::vec2yu<>{ 0.8f, 0.8f });
    panel->shader.genShader("../assets/shaders/texture/vertex.glsl", "../assets/shaders/texture/fragment.glsl");
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
        floor->bindTexture();
        floor->render_foregoingShader();
        floor->setRotation_getShader(glm::vec3{ 0.1f, 0.1f, 0.1f }, default3DShader, 0.1f);

        // CUBE
        cube->shader.use();
        cam.update(cube->shader);
        cube->bindTexture();
        cube->render_ownShader();
        cube->rotate(glm::vec3{ 0.6f, 0.8f, 0.6f }, 1.0f);

        // GUI
        if (!cam.active) {
            // MATHY TRANSFORMATIONS | YUME MATH IMPLEMENTATION AND USE EXAMPLE
            if (input::keyDown(GLFW_KEY_RIGHT)) {
                panel->size.container.x = panel->size.x() + 0.0005f;
                panel->updateVertices();
                panel->refresh();
            }
            else if (input::keyDown(GLFW_KEY_LEFT)) {
                panel->size.container.x = panel->size.x() - 0.0005f;
                panel->updateVertices();
                panel->refresh();
            }
            if (input::keyDown(GLFW_KEY_UP)) {
                panel->size.container.y = panel->size.y() + 0.0005f;
                panel->updateVertices();
                panel->refresh();
            }
            else if (input::keyDown(GLFW_KEY_DOWN)) {
                panel->size.container.y = panel->size.y() - 0.0005f;
                panel->updateVertices();
                panel->refresh();
            }

            if (input::keyDown(GLFW_KEY_R)) {
                panel->rotate(mathy::vec3yu<>{0.0f, 0.0f, 1.0f}, 1.0f);
                panel->updateVertices();
                panel->refresh();
            }

            panel->bindTexture();
            panel->render_ownShader();
            panel->setRotation(mathy::vec3yu<>{ 0.0f, 0.0f, 1.0f }, 180.0f);
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
            std::cout << yumegl::deltaTime << ": deltaTime\n";

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
    delete floor;
    delete panel;

    shaderSystem::deleteShader(default3DShader);
    yumegl::eExit::close();

    return 0;
#pragma endregion
}
