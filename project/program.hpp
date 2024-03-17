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
        cube_3D = new rd2::Cube("../project/textures/sonic_dirt.png", mathy::vec3yu<>{ 0.0f, 0.0f, -3.0f }, colour{ 0.0f, 0.0f, 0.0f, 1.0f }, mathy::vec3yu<>{ 1.0f, 1.0f, 1.0f }, true);
        cube_3D->shader.makeProgramFromPaths("../project/shaders/3D/vertex.glsl", "../project/shaders/3D/fragment.glsl");
        cube_3D->setWindowSize(yumegl::WINDOW_WIDTH, yumegl::WINDOW_HEIGHT);
    }

    yumeSubsystem Start() {
        // window
        yumegl::eFunc::setColor(colour::BLACK());
    }

    yumeSubsystem Update() {
        // UPDATE SYSTEMS
        yumegl::update();
        input::update();

        // CLOSE WINDOW
        if (input::keyPressed(GLFW_KEY_ESCAPE))
            yumegl::setWindowStatus(false);

        cube_3D->setRotation(mathy::vec3yu<>{ 0.7f, 0.7f, 0.9f }, 100.0f);
    }

    yumeSubsystem Render() {
        cube_3D->render();
    }

    yumeSubsystem Close() {
        delete cube_3D;
    }
}

#endif
