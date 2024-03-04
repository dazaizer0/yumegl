#pragma once

#include "../src/yume.h"

yumeSystem Program {
    // CREATE OBJECTS
    rd::TexSquare* player{ nullptr };

    yumeSubsystem Initialize() {
        yumegl::setWindowSize(650, 780);
        yumegl::init("yumegl");

        player = new rd::TexSquare("../project/textures/plane.png", mathy::vec3yu<>{ 0.0f, 0.8f, 0.0f }, colour{ 0.0f, 0.0f, 0.0f, 1.0f }, mathy::vec2yu<>{ 0.16f, 0.16f });
        player->shader.makeProgramFromPaths("../project/shaders/texture/vertex.glsl", "../project/shaders/texture/fragment.glsl");
    }

    yumeSubsystem Start() {
        // window
        yumegl::eFunc::setColor(colour::BLACK());

        // INTRO
        //audio::beep::playBeepSound(audio::beep::BeepSound::MIDRANGE());
        //audio::beep::playBeepSound(audio::beep::BeepSound{ 500, 500 });
        //audio::beep::playBeepSound(audio::beep::BeepSound{ 700, 500 });

        // player
        player->setRotation(mathy::vec3yu<>{ 0.0f, 0.0f, 1.0f}, 180.0f);
    }

    yumeSubsystem Update() {
        yumegl::update();
        input::update();

        // INPUT
        if (input::keyPressed(GLFW_KEY_ESCAPE))
            yumegl::setWindowStatus(false);

        if (input::keyDown(GLFW_KEY_RIGHT)) {
            player->position.container.x -= 1.0f * yumegl::dupaTime;
        }
        else if (input::keyDown(GLFW_KEY_LEFT)) {
            player->position.container.x += 1.0f * yumegl::dupaTime;
        }

        /* ------------------------------------------------
        --------------------- RENDER ----------------------
        ------------------------------------------------ */
        player->simpleRender();
    }

    yumeSubsystem Close() {
        delete player;
    }
}
