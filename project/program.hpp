#ifndef YUMEGL_PROGRAM_HPP
#define YUMEGL_PROGRAM_HPP

#include "../src/yume.h"

// :)

yumeSystem Program {
    // CREATE OBJECTS
    rd::TexSquare* player{ nullptr };

    yumeSubsystem SetUp() {
        yumegl::setWindowSize(650, 780);
        yumegl::init("yumegl");
    }

    yumeSubsystem Initialize() {
        player = new rd::TexSquare("../project/textures/plane.png", { 0.0f, 0.8f, 0.0f }, { 0.0f, 0.0f, 0.0f, 1.0f }, { 0.16f, 0.16f });
        player->shader.makeProgramFromPaths("../project/shaders/texture/vertex.glsl", "../project/shaders/texture/fragment.glsl");
    }

    // -----------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------
    yumeSubsystem Start() {
        // window
        yumegl::eFunc::setColor(colour::BLACK());

        // INTRO
        // audio::beep::playBeepSound(audio::beep::BeepSound::MIDRANGE());
        // audio::beep::playBeepSound(audio::beep::BeepSound{ 500, 500 });
        // audio::beep::playBeepSound(audio::beep::BeepSound{ 700, 500 });

        // player
        player->setRotation(mathy::vec3yu<>{ 0.0f, 0.0f, 1.0f}, 180.0f);
    }

    yumeSubsystem Update() {
        // UPDATE SYSTEMS
        yumegl::update();
        input::update();

        // CLOSE WINDOW
        if (input::keyPressed(GLFW_KEY_ESCAPE))
            yumegl::setWindowStatus(false);

        // MOVEMENT
        if (input::keyDown(GLFW_KEY_RIGHT) && player->position.x() > -1.0f + player->size.x()) {
            player->position.container.x -= 1.0f * yumegl::dupaTime;
        }
        else if (input::keyDown(GLFW_KEY_LEFT) && player->position.x() < 1.0f - player->size.x()) {
            player->position.container.x += 1.0f * yumegl::dupaTime;
        }
    }

    yumeSubsystem Render() {
        player->simpleRender();
    }
    // -----------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------

    yumeSubsystem Close() {
        delete player;
    }
}

#endif
