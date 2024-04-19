#ifndef YUMEGL_MP_YUME_PROGRAM_HPP
#define YUMEGL_MP_YUME_PROGRAM_HPP

#include "config.h"
#include "yume_elementary.h"
#include "yume_expanded.h"

namespace program {
    rd::TexSquare* player{ nullptr };

    void setup() {
        yumegl::setWindowSize(720, 720);
        yumegl::init("yumegl");
    }

    void start() {
        player = new rd::TexSquare("../assets/textures/sonic_grass.png", mathy::vec3yu<>{ 0.0f, 0.0f, 0.0f }, colour{ 0.0f, 0.0f, 0.0f, 1.0f }, mathy::vec2yu<>{ 0.16f, 0.16f });
        player->shader.makeProgramFromPaths("../assets/shaders/texture/vertex.glsl", "../assets/shaders/texture/fragment.glsl");
        player->setRotation(mathy::vec3yu<>{ 0.0f, 0.0f, 1.0f}, 180.0f);

        setWindowColor(colour::BLACK());
    }

    void update() {
        if (input::keyPressed(YINPUT_KEY_ESCAPE))
            yumegl::setWindowStatus(false);

        if (input::keyDown(YINPUT_KEY_UP)) {
            player->position.container.y -= 1.0f * yumegl::dupaTime;
        }
        if (input::keyDown(YINPUT_KEY_DOWN)) {
            player->position.container.y += 1.0f * yumegl::dupaTime;
        }
        if (input::keyDown(YINPUT_KEY_RIGHT)) {
            player->position.container.x -= 1.0f * yumegl::dupaTime;
        }
        if (input::keyDown(YINPUT_KEY_LEFT)) {
            player->position.container.x += 1.0f * yumegl::dupaTime;
        }
    }

    void render() {
        player->simpleRender();
    }

    void close() {
        delete player;
    }
}

#endif
