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
    panicShader.genShader("../assets/shaders/shape/vertex.glsl", "../assets/shaders/shape/fragment.glsl");

    auto* player = new rd::TexSquare("../assets/textures/sonic_grass.png", mathy::vec3yu<>{ 0.5f, 0.6f, 0.0f }, colour::BLUE(), mathy::vec2yu<>{ 0.09f, 0.16f });
    player->shader.genShader("../assets/shaders/texture/vertex.glsl", "../assets/shaders/texture/fragment.glsl");
    float jumpTime{ 0.6f };
    float jumpTimer{ jumpTime };
    float jumpForce{ 1.1f };
    bool jumping{ false };
    bool canJump{ true };

    auto* ground = new rd::TexSquare("../assets/textures/sonic_dirt.png", mathy::vec3yu<>{ 0.0f, 1.75f, 0.0f }, colour{ 0.0f, 0.0f, 0.0f, 1.0f }, mathy::vec2yu<>{ 1.00f, 1.0f });
    ground->shader.genShader("../assets/shaders/texture/vertex.glsl", "../assets/shaders/texture/fragment.glsl");

    auto* ground1 = new rd::TexSquare("../assets/textures/sonic_dirt.png", mathy::vec3yu<>{ -2.0f, 1.75f, 0.0f }, colour{ 0.0f, 0.0f, 0.0f, 1.0f }, mathy::vec2yu<>{ 1.00f, 1.0f });
    ground1->shader.genShader("../assets/shaders/texture/vertex.glsl", "../assets/shaders/texture/fragment.glsl");

    auto* obstacle = new rd::TexSquare("../assets/textures/sonic_warning.png", mathy::vec3yu<>{ 0.2f, 0.65f, 0.0f }, colour::BLUE(), mathy::vec2yu<>{ 0.06f, 0.11f });
    obstacle->shader.genShader("../assets/shaders/texture/vertex.glsl", "../assets/shaders/texture/fragment.glsl");

    auto* obstacle1 = new rd::TexSquare("../assets/textures/sonic_warning.png", mathy::vec3yu<>{ -0.9f, 0.65f, 0.0f }, colour::BLUE(), mathy::vec2yu<>{ 0.06f, 0.11f });
    obstacle1->shader.genShader("../assets/shaders/texture/vertex.glsl", "../assets/shaders/texture/fragment.glsl");

    auto* lost = new rd::TexSquare("../assets/textures/sonic_ice.png", mathy::vec3yu<>{ 0.0f, -0.2f, 0.0f }, colour::BLUE(), mathy::vec2yu<>{ 1.0f, 0.8f });
    lost->shader.genShader("../assets/shaders/texture/vertex.glsl", "../assets/shaders/texture/fragment.glsl");

    float gameTimer{ 0.0f };
    float gameSpeed{ 0.4f };
    float finalScore{ 0.0f };

#pragma endregion

#pragma region MAIN_LOOP
    /* ------------------------------------------------
    * ------------------ MAIN LOOP --------------------
    * ------------------------------------------------- */
    while (yumegl::isWindowOpen()) {
        // UPDATE
        yumegl::update();
        input::update();
        player->PanicHandler();
        gameTimer += 1.0f * yumegl::deltaTime;
        gameSpeed += 0.01f * yumegl::deltaTime;

        // PLATFORM MOVEMENT
        ground->position.container.x += gameSpeed * yumegl::deltaTime;
        ground->updateVertices();
        ground->refresh();

        if (ground->position.x() > 1.0f + ground->size.x()) {
            ground->position.container.x = -1.0f - ground->size.x();
        }

        ground1->position.container.x += gameSpeed * yumegl::deltaTime;
        ground1->updateVertices();
        ground1->refresh();

        if (ground1->position.x() > 1.0f + ground1->size.x()) {
            ground1->position.container.x = -1.0f - ground1->size.x();
        }

        obstacle->position.container.x += gameSpeed * yumegl::deltaTime;
        obstacle->updateVertices();
        obstacle->refresh();

        if (obstacle->position.x() > 1.0f + obstacle->size.x()) {
            obstacle->position.container.x = -1.0f - obstacle->size.x();
        }

        obstacle1->position.container.x += gameSpeed * yumegl::deltaTime;
        obstacle1->updateVertices();
        obstacle1->refresh();

        if (obstacle1->position.x() > 1.0f + obstacle1->size.x()) {
            obstacle1->position.container.x = -1.0f - obstacle1->size.x();
        }

        // PLAYER JUMPING
        if (!jumping) {
            if (player->position.y() <= 0.59f)
                player->position.container.y += 0.8f * yumegl::deltaTime;
            else
                jumping = false;
        }
        else {
            if (jumpTimer > 0.0f) {
                player->position.container.y -= jumpForce * yumegl::deltaTime;
                jumpTimer -= 1.0f * yumegl::deltaTime;
            }
            else {
                jumping = false;
                jumpTimer = jumpTime;
            }
        }

        if (player->position.y() > 0.50f)
            canJump = true;
        else
            canJump = false;

        // INPUT SYSTEM
        if (input::keyPressed(GLFW_KEY_ESCAPE))
            yumegl::setWindowStatus(false);

        if (input::keyPressed(GLFW_KEY_SPACE) && canJump)
            jumping = true;

        player->updateVertices();
        player->refresh();

        /* ------------------------------------------------
         * ------------------- RENDER ---------------------
         * ------------------------------------------------ */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // TEXTURE
        player->bindTexture();
        player->render_ownShader();
        player->setRotation(mathy::vec3yu<>{ 0.0f, 0.0f, 1.0f }, 180.0f);

        ground->bindTexture();
        ground->render_ownShader();
        ground->setRotation(mathy::vec3yu<>{ 0.0f, 0.0f, 1.0f }, 180.0f);

        ground1->bindTexture();
        ground1->render_ownShader();
        ground1->setRotation(mathy::vec3yu<>{ 0.0f, 0.0f, 1.0f }, 180.0f);

        if (gameTimer > 2.0f) {
            obstacle->bindTexture();
            obstacle->render_ownShader();
            obstacle->setRotation(mathy::vec3yu<>{ 0.0f, 0.0f, 1.0f }, 180.0f);
        }

        obstacle1->bindTexture();
        obstacle1->render_ownShader();
        obstacle1->setRotation(mathy::vec3yu<>{ 0.0f, 0.0f, 1.0f }, 180.0f);

        if ((int)gameTimer % 5 == 0)
            std::cout << "score/timer: " << gameTimer << '\n';

        if ((player->position.distance(obstacle->position) < player->size.x() + obstacle->size.x() || player->position.distance(obstacle1->position) < player->size.x() + obstacle1->size.x()) && gameTimer > 2.0f) {
            lost->bindTexture();
            lost->render_ownShader();
            lost->setRotation(mathy::vec3yu<>{ 0.0f, 0.0f, 1.0f }, 180.0f);

            gameSpeed = 0.0f;
            if (finalScore == 0.0f)
                finalScore = gameTimer;
            else
                gameTimer = finalScore;

            std::cout << "score : " << finalScore << '\n';
        }

        // SWAP POLL EVENTS
        yumegl::swapBuffersPollEvents();
    }
#pragma endregion

#pragma region DE_INITIALIZATION
    /* ------------------------------------------------
    * -------------- DE-INITIALIZATION ----------------
    * ------------------------------------------------- */
    delete player;
    delete ground;
    delete ground1;

    yumegl::eExit::close();
    return 0;
#pragma endregion
}
