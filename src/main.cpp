#include "config.h"
#include "yume.h"
#include "project.h"

int main() {
#pragma region INITIALIZATION
    /* ------------------------------------------------
    * ---------------- INITIALIZATION -----------------
    * ------------------------------------------------- */
    yumegl::init("yumegl");
    yumegl::eFunc::setColor(colour::BLACK());

    // DEPTH
    glEnable(GL_DEPTH_TEST);

    // OBJECTS
    auto* panel = new rd1::Texture("../assets/textures/sonic_warning.png", mathy::vec3yu<>{ 0.5f, 0.59f, 0.0f }, colour{ 0.0f, 0.0f, 0.0f, 1.0f }, mathy::vec2yu<>{ 0.09f, 0.16f });
    panel->shader.genShader("../assets/shaders/texture/vertex.glsl", "../assets/shaders/texture/fragment.glsl");

    auto* ground = new rd1::Texture("../assets/textures/sonic_dirt.png", mathy::vec3yu<>{ 0.0f, 1.75f, 0.0f }, colour{ 0.0f, 0.0f, 0.0f, 1.0f }, mathy::vec2yu<>{ 1.00f, 1.0f });
    ground->shader.genShader("../assets/shaders/texture/vertex.glsl", "../assets/shaders/texture/fragment.glsl");

    auto* ground1 = new rd1::Texture("../assets/textures/sonic_dirt.png", mathy::vec3yu<>{ -2.0f, 1.75f, 0.0f }, colour{ 0.0f, 0.0f, 0.0f, 1.0f }, mathy::vec2yu<>{ 1.00f, 1.0f });
    ground1->shader.genShader("../assets/shaders/texture/vertex.glsl", "../assets/shaders/texture/fragment.glsl");
#pragma endregion

#pragma region MAIN_LOOP
    /* ------------------------------------------------
    * ------------------ MAIN LOOP --------------------
    * ------------------------------------------------- */
    while (yumegl::isWindowOpen()) {
        // UPDATE
        yumegl::update();
        input::update();

        ground->position.container.x += 0.4f * yumegl::deltaTime;
        ground->updateVertices();
        ground->refresh();

        if (ground->position.x() > 1.0f + ground->size.x()) {
            ground->position.container.x = -1.0f - ground->size.x();
        }

        ground1->position.container.x += 0.4f * yumegl::deltaTime;
        ground1->updateVertices();
        ground1->refresh();

        if (ground1->position.x() > 1.0f + ground1->size.x()) {
            ground1->position.container.x = -1.0f - ground1->size.x();
        }

        // INPUT SYSTEM
        if (input::keyPressed(GLFW_KEY_ESCAPE))
            yumegl::setWindowStatus(false);

        if (input::keyDown(GLFW_KEY_SPACE)) 
            // JUMP

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

        ground->bindTexture();
        ground->render_ownShader();
        ground->setRotation(mathy::vec3yu<>{ 0.0f, 0.0f, 1.0f }, 180.0f);

        ground1->bindTexture();
        ground1->render_ownShader();
        ground1->setRotation(mathy::vec3yu<>{ 0.0f, 0.0f, 1.0f }, 180.0f);

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
