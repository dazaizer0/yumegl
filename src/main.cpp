#include "config.h"
#include "yume.h"
#include "engine/objects/camera.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main() {
    // INITIALIZATION
    yumegl::init(WINDOW_WIDTH, WINDOW_HEIGHT, "Yume");
    yumegl::eFunc::setColor(mathy::colorRGBA::BLACK());

    // IMGUI INITIALIZATION
    // yumeImGui::init();

    // CAMERA
    object::Camera3D cam = object::Camera3D(WINDOW_WIDTH, WINDOW_HEIGHT);

    // SHADER
    glEnable(GL_DEPTH_TEST);

    Shader staticShader(
        "texture/vertex_t3d.glsl",
        "texture/fragment_t3d.glsl"
    );

    // CUBE
    render::Cube cube = render::Cube(
        "textures/sonic_grass.png",
        glm::vec3 {0.0f, 0.0f, -3.0f},
        glm::vec3 {1.0f, 1.0f, 1.0f}
    );

    cube.setWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    // MAIN LOOP
    while (yumegl::isWindowOpen()) {
        auto currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // INPUT SYSTEM
        input::updateInput();
        if (input::keyPressed(GLFW_KEY_ESCAPE)) {
            yumegl::setWindowStatus(false);
        }

        cam.updateCameraInput(deltaTime);

        // RENDER
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cube.render(staticShader);
        cube.rotate(
            glm::vec3{0.4f, 0.5f, 0.4f},
            staticShader,
            1.0f
        );

        // CAMERA
        cam.update(staticShader);

        // SWAP POLL EVENTS
        yumegl::swapBuffersPollEvents();
    }
    // DE-INITIALIZATION
    // yumeImGui::clear();

    glDeleteShader(staticShader.ID);
    cube.deleteData();

    yumegl::eExit::close();
    return 0;
}
