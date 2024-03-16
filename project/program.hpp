#ifndef YUMEGL_PROGRAM_HPP
#define YUMEGL_PROGRAM_HPP

#include "../src/yume.h"

// :)

yumeSystem Program {
    rd1::Cube* cube_3D{ nullptr };

    yumeSubsystem SetUp() {
        yumegl::setWindowSize(720, 720);
        yumegl::init("yumegl");
    }

    yumeSubsystem Initialize() {
        cube_3D = new rd1::Cube("../project/textures/sonic_dirt.png", glm::vec3{ 0.0f, 0.0f, -3.0f }, glm::vec3{ 1.0f });
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

        cube_3D->rotate(glm::vec3{ 0.6f, 0.8f, 0.6f }, 1.0f);
    }

    yumeSubsystem Render() {
        cube_3D->shader.use();
        cube_3D->bindTexture();
        cube_3D->render_ownShader();
    }

    yumeSubsystem Close() {
        delete cube_3D;
    }
}

#endif
