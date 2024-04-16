#ifndef YUMEGL_MP_YUME_PROGRAM_HPP
#define YUMEGL_MP_YUME_PROGRAM_HPP

#include "config.h"
#include "yume_elementary.h"
#include "yume_expanded.h"

namespace program {
    rd2::Cube* cube_3D{ nullptr };

    void setup() {
        yumegl::setWindowSize(720, 720);
        yumegl::init("yumegl");
    }

    void start() {
        cube_3D = new rd2::Cube("../assets/textures/sonic_warning.png", mathy::vec3yu<>{ 0.0f, 0.0f, -3.0f }, mathy::vec3yu<>{ 0.0f, 1.0f, 0.0f }, mathy::vec3yu<>{ 1.0f, 1.0f, 1.0f }, true);
        cube_3D->shader.makeProgramFromPaths("../assets/shaders/3D/vertex.glsl", "../assets/shaders/3D/fragment.glsl");

        setWindowColor(colour::BLACK());
    }

    void update() {
        if (input::keyPressed(YINPUT_KEY_ESCAPE))
            yumegl::setWindowStatus(false);

        if (input::keyDown(YINPUT_KEY_RIGHT))
            cube_3D->rotationAngle += 100.0f * yumegl::dupaTime;

        if (input::keyDown(YINPUT_KEY_LEFT))
            cube_3D->rotationAngle -= 100.0f * yumegl::dupaTime;

        if (input::keyPressed(YINPUT_KEY_SPACE))
            cube_3D->enable = !cube_3D->enable;
    }

    void render() {
        cube_3D->render();
    }

    void close() {
        delete cube_3D;
    }
}

#endif
