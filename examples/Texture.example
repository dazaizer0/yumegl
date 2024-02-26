#include "config.h"
#include "yume.h"
#include "project.h"

int main() {
#pragma region INITIALIZATION
    /* ------------------------------------------------
    ----------------- INITIALIZATION ------------------
    ------------------------------------------------ */
    yumegl::init("yumegl");
    yumegl::eFunc::setColor(colour::BLACK());
    glEnable(GL_DEPTH_TEST);

    auto* tex = new rd::TexSquare("../assets/textures/cat.png", mathy::vec3yu<>{ 0.0f, 0.0f, 0.0f }, colour{ 0.0f, 0.0f, 0.0f, 1.0f }, mathy::vec2yu<>{ 0.45f, 0.9f });
    tex->shader.genShader("../assets/shaders/texture/vertex.glsl", "../assets/shaders/texture/fragment.glsl");
    tex->setRotation(mathy::vec3yu<>{ 0.0f, 0.0f, 1.0f}, 180.0f);
#pragma endregion

#pragma region MAIN_LOOP
    /* ------------------------------------------------
    -------------------- MAIN LOOP --------------------
    ------------------------------------------------ */
    while (yumegl::isWindowOpen()) {
        // UPDATE
        yumegl::update();
        input::update();

        // INPUT
        if (input::keyPressed(GLFW_KEY_ESCAPE))
            yumegl::setWindowStatus(false);

        /* ------------------------------------------------
        --------------------- RENDER ----------------------
        ------------------------------------------------ */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        tex->bindTexture();
        tex->render_ownShader();

        /* ------------------------------------------------
        --------------------- OTHER -----------------------
        ------------------------------------------------ */
        yumegl::swapBuffersPollEvents();
    }
#pragma endregion

#pragma region DE_INITIALIZATION
    /* ------------------------------------------------
    --------------- DE -INITIALIZATION ----------------
    ------------------------------------------------ */
    delete tex;

    yumegl::eExit::close();
    return 0;
#pragma endregion
}
