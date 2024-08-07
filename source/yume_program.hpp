#ifndef YUMEGL_MP_YUME_PROGRAM_HPP
#define YUMEGL_MP_YUME_PROGRAM_HPP

#include "config.h"
#include "yume_elementary.h"
#include "yume_expanded.h"

namespace program {
    rd::TexSquare* player{ nullptr };
    bool jumping = false;
    float velocity = 0.0f;
    const float gravity = 0.001f;
    const float jumpForce = -0.02f;

    void setup() {
        yumegl::setWindowSize(720, 720);
        yumegl::init("flappy bird");
    }

    void start() {
        player = new rd::TexSquare("../assets/textures/player.png", mathy::vec3yu<>{ 0.0f, 0.0f, 0.0f }, colour{ 0.0f, 0.0f, 0.0f, 1.0f }, mathy::vec2yu<>{ 0.12f, 0.12f });
        player->shader.makeProgramFromPaths("../assets/shaders/texture/vertex.glsl", "../assets/shaders/texture/fragment.glsl");
        player->setRotation(mathy::vec3yu<>{ 0.0f, 0.0f, 1.0f}, 180.0f);

        setWindowColor(colour::BLACK());
    }

    void update() {
        if (input::keyPressed(KEY_ESCAPE))
            yumegl::setWindowStatus(false);

        if (player->position.y() < 0.8f) {
            velocity += gravity;
        }
        else {
            velocity = 0;
            player->position.container.y = 0.8f;
        }

        if (input::keyPressed(KEY_SPACE)) {
            velocity = jumpForce;
        }

        player->position.container.y += velocity;
    }

    void render() {
        player->simpleRender();
    }

    void close() {
        delete player;
    }
}

#endif
