#ifndef YUMEGL_PROGRAM_HPP
#define YUMEGL_PROGRAM_HPP

#include "../src/yume.h"

// :)

yumeSystem Program {
    rd2::Cube* cube_3D{ nullptr };

    yumeSubsystem SetUp() {
        yumegl::setWindowSize(720, 720);
        yumegl::init("yumegl");
    }

    yumeSubsystem Initialize() {
        cube_3D = new rd2::Cube("../project/textures/sonic_dirt.png", mathy::vec3yu<>{ 0.0f, 0.0f, -3.0f }, mathy::vec3yu<>{ 0.0f, 1.0f, 0.0f }, mathy::vec3yu<>{ 1.0f, 1.0f, 1.0f }, true);
        cube_3D->shader.makeProgramFromPaths("../project/shaders/3D/vertex.glsl", "../project/shaders/3D/fragment.glsl");
    }

    yumeSubsystem Start() {
        yumegl::eFunc::setColor(colour::BLACK());
    }

    yumeSubsystem Update() {
        if (input::keyPressed(YINPUT_KEY_ESCAPE))
            yumegl::setWindowStatus(false);

        // ROTATE CUBE
        if (input::keyDown(YINPUT_KEY_RIGHT))
            cube_3D->rotationAngle += 10 * yumegl::dupaTime;
        if (input::keyDown(YINPUT_KEY_LEFT))
            cube_3D->rotationAngle -= 10 * yumegl::dupaTime;

        if (input::keyPressed(YINPUT_KEY_SPACE))
            cube_3D->enable = !cube_3D->enable;
    }

    yumeSubsystem Render() {
        cube_3D->render();
    }

    yumeSubsystem Close() {
        delete cube_3D;
    }
}
#endif