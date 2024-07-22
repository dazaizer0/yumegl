#ifndef YUMEGL_MP_YUME_PROGRAM_HPP
#define YUMEGL_MP_YUME_PROGRAM_HPP

#include "config.h"
#include "yume_elementary.h"
#include "yume_expanded.h"

namespace program {
    rd2::Cube* cube_3D{ nullptr };
    rd2::Cube* smiglo{ nullptr };
    float power = 0;

    void setup() {
        yumegl::setWindowSize(720, 720);
        yumegl::init("yumegl");
    }

    void start() {
        cube_3D = new rd2::Cube("../assets/textures/sonic_warning.png", mathy::vec3yu<>{ 0.0f, -0.75f, -3.0f }, mathy::vec3yu<>{ 0.0f, 1.0f, 0.0f }, mathy::vec3yu<>{ 1.0f, 0.5f, 1.0f }, true);
        cube_3D->shader.makeProgramFromPaths("../assets/shaders/3D/vertex.glsl", "../assets/shaders/3D/fragment.glsl");
        smiglo = new rd2::Cube("../assets/textures/sonic_grass.png", mathy::vec3yu<>{ cube_3D->position.x(), cube_3D->position.y() + 0.2f, cube_3D->position.z() }, mathy::vec3yu<>{ 0.0f, 1.0f, 0.0f }, mathy::vec3yu<>{ 0.35f, 0.2f, 1.2f }, true);
        smiglo->shader.makeProgramFromPaths("../assets/shaders/3D/vertex.glsl", "../assets/shaders/3D/fragment.glsl");

        setWindowColor(colour::BLACK());
    }

    void update() {
        if (input::keyPressed(KEY_ESCAPE))
            yumegl::setWindowStatus(false);

        if (input::keyDown(KEY_D))
            cube_3D->rotationAngle -= 90.0f * yumegl::dupaTime;

        if (input::keyDown(KEY_A))
            cube_3D->rotationAngle += 90.0f * yumegl::dupaTime;

        if (input::keyPressed(KEY_SPACE))
            cube_3D->enable = !cube_3D->enable;

        if (input::keyDown(KEY_W) && power < 0.5f) {
            power += 2 * yumegl::dupaTime;
        }
        if (input::keyDown(KEY_S)) {
            power -= 0.4 * yumegl::dupaTime;
        }
        if (power < 0.0f) { power = 0.0f; }

        if (cube_3D->position.y() < -0.75) { cube_3D->position.container.y = -0.75f; }
        if (cube_3D->position.y() > power) { cube_3D->position.container.y = power; }

        if (power > 0.0f) {
            cube_3D->position.container.y += power * 1.2f * yumegl::dupaTime;
        }
        else if (power == 0.0f) {
            cube_3D->position.container.y -= 0.91f * yumegl::dupaTime;
        }

        smiglo->rotationAngle += power * 2137.0f * yumegl::dupaTime;
        smiglo->position = mathy::vec3yu<>{ cube_3D->position.x(), cube_3D->position.y() + 0.3f, cube_3D->position.z() };

        if (input::keyDown(KEY_RIGHT)) {
            cube_3D->position.container.x += power * yumegl::dupaTime;
        }
        else if (input::keyDown(KEY_LEFT)) {
            cube_3D->position.container.x -= power * yumegl::dupaTime;
        }
    }

    void render() {
        cube_3D->render();
        smiglo->render();
    }

    void close() {
        delete cube_3D;
        delete smiglo;
    }
}

#endif