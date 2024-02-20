#include "config.h"
#include "yume.h"

int main() {
#pragma region INITIALIZATION
    /* ------------------------------------------------
    * ---------------- INITIALIZATION -----------------
    * ------------------------------------------------ */
    yumegl::init("Yume");
    yumegl::eFunc::setColor(colour{0.72f, 0.72f, 0.72f, 1.0f});

    // DEPTH
    glEnable(GL_DEPTH_TEST);

    // OBJECTS
    auto* bat = new rd1::Texture("../assets/textures/sonic_disco.png", mathy::vec3yu<>{ 0.6f, 0.0f, 0.0f }, colour{ 0.0f, 0.0f, 0.0f, 1.0f }, mathy::vec2yu<>{ 0.045f, 0.08f });
    bat->shader.genShader("../assets/shaders/texture/vertex.glsl", "../assets/shaders/texture/fragment.glsl");

    auto* bug = new rd1::Texture("../assets/textures/sonic_warning.png", mathy::vec3yu<>{ -0.6f, 0.2f, 0.0f }, colour{ 0.0f, 0.0f, 0.0f, 1.0f }, mathy::vec2yu<>{ 0.022f, 0.04f });
    bug->shader.genShader("../assets/shaders/texture/vertex.glsl", "../assets/shaders/texture/fragment.glsl");

    float batTimer{ 0.0f };
    float batMax{ 1.0f };
#pragma endregion

#pragma region MAIN_LOOP
    /* ------------------------------------------------
    * ------------------ MAIN LOOP --------------------
    * ------------------------------------------------ */
    //int frameCounter = 0;
    //auto startTime = std::chrono::high_resolution_clock::now();

    while (yumegl::isWindowOpen()) {
        //auto frameStartTime = std::chrono::high_resolution_clock::now();

        // UPDATE
        yumegl::update();
        input::update();

        // INPUT SYSTEM
        if (input::keyPressed(GLFW_KEY_ESCAPE))
            yumegl::setWindowStatus(false);

        /* ------------------------------------------------
         * ------------------- RENDER ---------------------
         * ------------------------------------------------ */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ROOM
        bat->bindTexture();
        bat->render_ownShader();
        bat->setRotation(mathy::vec3yu{ 0.0f, 0.0f, 1.0f }, 180.0f);

        if (bat->position.y() < 1.0f - bat->size.y()) {
            bat->position.container.y += 1.0f * yumegl::deltaTime;
        }

        if (!input::keyDown(GLFW_KEY_SPACE)) batTimer = 0.0f;
        if (input::keyDown(GLFW_KEY_SPACE) && batTimer < batMax) {
            bat->position.container.y -= 2.0f * yumegl::deltaTime;
            batTimer += 1.0f * yumegl::deltaTime;
        }

        bat->updateVertices();
        bat->refresh();

        if (bat->position.distance(bug->position) < bat->size.y()) {
            bug->enable = false;
        }

        if (bug->enable) {
            bug->bindTexture();
            bug->render_ownShader();
            bug->setRotation(mathy::vec3yu{ 0.0f, 0.0f, 1.0f }, 180.0f);

            bug->position.container.x += 0.5f * yumegl::deltaTime;
            if (bug->position.x() > 1.0f) {
                bug->position.container.x = -1.0f;
            }

            bug->updateVertices();
            bug->refresh();
        }

        // SWAP POLL EVENTS
        yumegl::swapBuffersPollEvents();

        /* ------------------------------------------------
         * -------------------- STATS ---------------------
         * ------------------------------------------------ */
        /*
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
        */
    }
#pragma endregion

#pragma region DE_INITIALIZATION
    /* ------------------------------------------------
    * -------------- DE-INITIALIZATION ----------------
    * ------------------------------------------------ */
    delete bat;
    delete bug;

    yumegl::eExit::close();

    return 0;
#pragma endregion
}
