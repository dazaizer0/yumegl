#ifndef YUMEGL_PROGRAM_HPP
#define YUMEGL_PROGRAM_HPP

#include "../src/yume.h"
#include "../src/engine/render/rd2/cube_rd2.hpp"
#include "../src/engine/input/input.hpp"
#include "../src/engine/render/renderer.hpp"
// :)

#define SPEED 100

yumeSystem Program {
    rd2::Cube* cube_3D{ nullptr };
    rd::mng::Renderer renderer;

    yumeSubsystem SetUp() {
        yumegl::setWindowSize(720, 720);
        yumegl::init("yumegl");
    }

    yumeSubsystem Initialize() {
        cube_3D = new rd2::Cube("../project/textures/sonic_dirt.png", mathy::vec3yu<>{ 0.0f, 0.0f, -3.0f }, mathy::vec3yu<>{ 0.0f, 1.0f, 0.0f }, mathy::vec3yu<>{ 1.0f, 1.0f, 1.0f }, true);
        cube_3D->shader.makeProgramFromPaths("../project/shaders/3D/vertex.glsl", "../project/shaders/3D/fragment.glsl");
        renderer.append(*cube_3D);

        yumegl::eFunc::setColor(colour::BLACK());
    }

    yumeSubsystem Update() {
        if (input::keyPressed(YINPUT_KEY_ESCAPE))
            yumegl::setWindowStatus(false);

        // ROTATE CUBE
        if (input::keyDown(YINPUT_KEY_RIGHT)) {
            cube_3D->rotationAngle += SPEED * yumegl::dupaTime;
        }
        if (input::keyDown(YINPUT_KEY_LEFT)) {
            cube_3D->rotationAngle -= SPEED * yumegl::dupaTime;
        }

        if (input::keyDown(YINPUT_KEY_UP)) {
            cube_3D->rotationAngle += SPEED * yumegl::dupaTime;
        }
        if (input::keyDown(YINPUT_KEY_DOWN)) {
            cube_3D->rotationAngle -= SPEED * yumegl::dupaTime;
        }

        if (input::keyPressed(YINPUT_KEY_SPACE))
            cube_3D->enable = !cube_3D->enable;
    }

    yumeSubsystem Render() {
        // renderer.render(); does not work...
        cube_3D->render();
    }

    yumeSubsystem Close() {
        delete cube_3D;
    }
}
#endif