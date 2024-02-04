#include "config.h"
#include "engine/input/input.h"
#include "engine/shader/shader.h"
#include "engine/render/texture.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

int main() {
    // INITIALIZATION
    yumegl::init(WINDOW_WIDTH, WINDOW_HEIGHT, "Yume");
    yumegl::setColor(mathy::colorRGBA::BLACK());

    // SHADER
    Shader textureShader( // path, path
        "texture/vertex_t.glsl",
        "texture/fragment_t.glsl"
    );

    // TEXTURE 
    render::Texture tex = render::Texture(
        "textures/sonic_grass.png", // win path
        mathy::vec3<float>::ZERO(),
        mathy::colorRGBA::WHITE(),
        0.6f
    );

    // MAIN LOOP
    while (yumegl::isWindowOpen()) {
        // INPUT SYSTEM
        input::updateInput();
        if (input::keyPressed(GLFW_KEY_ESCAPE)) {
            yumegl::setWindowStatus(false);
        }

        // TEXTURE ROTATION
        tex.rotate(
                glm::vec3{0.2f , 0.4f, 0.2f},
                textureShader,
                1.2f
        );

        // RENDER
        glClear(GL_COLOR_BUFFER_BIT);

        tex.render(textureShader.ID);
        
        yumegl::swapBuffersPollEvents();
    }

    // DE-INITIALIZATION
    tex.deleteData();
    glDeleteShader(textureShader.ID);

    yumegl::close();
    return 0;
}