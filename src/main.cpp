#include "config.h"
#include "yume.h"
#include "project.h"

int main() {
#pragma region INITIALIZATION
    /* ------------------------------------------------
    * ---------------- INITIALIZATION -----------------
    * ------------------------------------------------- */
    yumegl::init("yumegl");
    yumegl::eFunc::setColor(colour::YELLOW());

    // DEPTH
    glEnable(GL_DEPTH_TEST);

    // OBJECTS
    auto* panel = new rd1::Texture("../assets/textures/sonic_disco.png", mathy::vec3yu<>{ 0.0f, 0.0f, 0.0f }, colour{ 0.0f, 0.0f, 0.0f, 1.0f }, mathy::vec2yu<>{ 0.18f, 0.32f });
    panel->shader.genShader("../assets/shaders/texture/vertex.glsl", "../assets/shaders/texture/fragment.glsl");
#pragma endregion

#pragma region MAIN_LOOP
    /* ------------------------------------------------
    * ------------------ MAIN LOOP --------------------
    * ------------------------------------------------- */
    while (yumegl::isWindowOpen()) {
        // UPDATE
        yumegl::update();
        input::update();

        // INPUT SYSTEM
        if (input::keyPressed(GLFW_KEY_ESCAPE))
            yumegl::setWindowStatus(false);

        if (input::keyDown(GLFW_KEY_UP)) 
            panel->position.container.y -= 1.0f * yumegl::deltaTime;
        else if (input::keyDown(GLFW_KEY_DOWN))
            panel->position.container.y += 1.0f * yumegl::deltaTime;
        if (input::keyDown(GLFW_KEY_RIGHT))
            panel->position.container.x -= 1.0f * yumegl::deltaTime;
        else if (input::keyDown(GLFW_KEY_LEFT))
            panel->position.container.x += 1.0f * yumegl::deltaTime;

        panel->updateVertices();
        panel->refresh();

        /* ------------------------------------------------
         * ------------------- RENDER ---------------------
         * ------------------------------------------------ */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // TEXTURE
        panel->bindTexture();
        panel->render_ownShader();
        panel->setRotation(mathy::vec3yu<>{ 0.0f, 0.0f, 1.0f }, 180.0f);

        // SWAP POLL EVENTS
        yumegl::swapBuffersPollEvents();
    }
#pragma endregion

#pragma region DE_INITIALIZATION
    /* ------------------------------------------------
    * -------------- DE-INITIALIZATION ----------------
    * ------------------------------------------------- */
    delete panel;

    yumegl::eExit::close();
    return 0;
#pragma endregion
}
