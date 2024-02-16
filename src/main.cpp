#include "config.h"
#include "yume.h"

int main() {
    // TODO: Simple, optimal, flexible 2D rendering based on your own solutions
#pragma region INITIALIZATION
    /*-------------------------------------------------
    * ---------------- INITIALIZATION -----------------
    * -------------------------------------------------*/
    yumegl::init("Yume");
    yumegl::eFunc::setColor(colour::BLACK());

    // DEPTH
    glEnable(GL_DEPTH_TEST);

    // OBJECTS (musialem dodac cos bo puste okno dolujace)
    auto* panel = new rd1::Texture("textures/sonic_warning.png", glm::vec3{ 0.0f }, colour{ 0.0f, 0.0f, 0.0f, 1.0f }, glm::vec2{ 0.45f, 0.8f });
    panel->shader.genShader("texture/vertex_t.glsl", "texture/fragment_t.glsl");

#pragma endregion

#pragma region MAIN_LOOP
    /*-------------------------------------------------
    * ------------------ MAIN LOOP --------------------
    * -------------------------------------------------*/
    int frameCounter = 0;
    auto startTime = std::chrono::high_resolution_clock::now();

    while (yumegl::isWindowOpen()) {
        auto frameStartTime = std::chrono::high_resolution_clock::now();

        // UPDATE
        yumegl::update();
        input::update();

        // INPUT SYSTEM
        if (input::keyPressed(GLFW_KEY_ESCAPE))
            yumegl::setWindowStatus(false);

        /*-------------------------------------------------
         * ------------------- RENDER ---------------------
         * ------------------------------------------------*/
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        panel->bindTexture();
        panel->render_ownShader();
        panel->setRotation(glm::vec3{ 0.0f, 0.0f, 1.0f }, 180.0f);

        // SWAP POLL EVENTS
        yumegl::swapBuffersPollEvents();

        /*-------------------------------------------------
         * -------------------- STATS ---------------------
         * ------------------------------------------------*/
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
    /*-------------------------------------------------
    * -------------- DE-INITIALIZATION ----------------
    * -------------------------------------------------*/
    delete panel;

    yumegl::eExit::close();

    return 0;
#pragma endregion
}
