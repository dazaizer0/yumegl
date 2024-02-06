#include "config.h"
#include "yume.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

int main() {
    // INITIALIZATION
    yumegl::init(WINDOW_WIDTH, WINDOW_HEIGHT, "Yume");
    yumegl::eFunc::setColor(mathy::colorRGBA::BLACK());

    // IMGUI INITIALIZATION
    yumeImGui::init();

    // SHADER
    Shader textureShader(
        "texture/vertex_t.glsl",
        "texture/fragment_t.glsl"
    );

    // TEXTURE 
    render::Texture tex = render::Texture(
        "sonic_grass",
        "textures/sonic_grass.png",
        mathy::vec3<float>::ZERO(),
        mathy::colorRGBA::WHITE(),
        textureShader,
        0.6f
    );

    // MAIN LOOP
    while (yumegl::isWindowOpen()) {
        // INPUT SYSTEM
        input::updateInput();
        if (input::keyPressed(GLFW_KEY_ESCAPE)) {
            yumegl::setWindowStatus(false);
        }

        tex.angle += 0.01f;
        tex.updateRotation(textureShader);

        // RENDER
        glClear(GL_COLOR_BUFFER_BIT);

        tex.render(textureShader.ID);
        
        // YUMEIMGUI
        yumeImGui::texture::yumeImGui_CreateFrame(tex);

        // SWAP POLL EVENTS
        yumegl::swapBuffersPollEvents();
    }

    // DE-INITIALIZATION
    yumeImGui::clear();

    tex.deleteData();
    glDeleteShader(textureShader.ID);

    yumegl::eExit::close();
    return 0;
}