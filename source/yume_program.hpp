#ifndef YUMEGL_MP_YUME_PROGRAM_HPP
#define YUMEGL_MP_YUME_PROGRAM_HPP

#include "config.h"
#include "yume_elementary.h"
#include "yume_expanded.h"

double MOUSEX = 0;
double MOUSEY = 0;

void movement_handler(rd::TexSquare* player, int* direction);

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    MOUSEX = xpos;
    MOUSEY = ypos;
}

namespace program {
    rd::TexSquare* player{ nullptr };
    int direction;

    void setup() {
        yumegl::setWindowSize(720, 720);
        yumegl::init("yumegl");
        yumegl::audio_enabled = false;
    }

    void start() {
        player = new rd::TexSquare("../assets/textures/sonic_grass.png", mathy::vec3yu<>{ 0.0f, 0.0f, 0.0f }, colour{ 0.0f, 0.0f, 0.0f, 1.0f }, mathy::vec2yu<>{ 0.16f, 0.16f });
        player->shader.makeProgramFromPaths("../assets/shaders/texture/vertex.glsl", "../assets/shaders/texture/fragment.glsl");
        player->setRotation(mathy::vec3yu<>{ 0.0f, 0.0f, 1.0f}, 180.0f);

        setWindowColor(colour::BLACK());

        yumegl::setCursorPosCallback(mouse_callback);
    }

    void update() {
        if (input::keyPressed(KEY_ESCAPE))
            yumegl::setWindowStatus(false);

        movement_handler(player, &direction);
    }

    void render() {
        player->simpleRender();
    }

    void close() {
        delete player;
    }
}

void movement_handler(rd::TexSquare* player, int* direction) {
    if (input::keyDown(KEY_UP))
        *direction = 1;
    else if (input::keyDown(KEY_DOWN))
        *direction = 2;
    else if (input::keyDown(KEY_RIGHT))
        *direction = 3;
    else if (input::keyDown(KEY_LEFT))
        *direction = 4;
    else
        *direction = 0;

    switch (*direction) {
    case 1: // up
        player->position.container.y -= 1.0f * yumegl::dupaTime;
        break;
    
    case 2: // down
        player->position.container.y += 1.0f * yumegl::dupaTime;
        break;
    
    case 3: // right
        player->position.container.x -= 1.0f * yumegl::dupaTime;
        break;
    
    case 4: // left
        player->position.container.x += 1.0f * yumegl::dupaTime;
        break;
    
    default:
        break;
    }
}
#endif
