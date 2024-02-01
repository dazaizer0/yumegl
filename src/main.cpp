#include "config.h"
#include "stb/stb_image.h"

#include "engine/render/triangle.h"
#include "engine/render/square.h"
#include "engine/input/input.h"
#include "engine/shader/shader.h"

#include "engine/render/texture.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

int main() {
    // INITIALIZATION
    GL::init(WINDOW_WIDTH, WINDOW_HEIGHT, "Yume");
    setColor(mathy::colorRGBA::BLACK());

    // SHADERS
    shader::Shader shader = shader::Shader(
            "C:/Users/mydat/Documents/_active_c/_cpp/YumeGl/yumegl/src/engine/shader/shader_scripts/vertex.glsl",
            "C:/Users/mydat/Documents/_active_c/_cpp/YumeGl/yumegl/src/engine/shader/shader_scripts/fragment.glsl"
    );

    // SQUARE
    render::Texture tex = render::Texture(
            mathy::vec3 {-0.5f, 0.2f, 0.0f},
            mathy::colorRGBA::BLUE(),
            0.4f
    );

    // TEXTURE
    unsigned int _texture;
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    unsigned char *data2 = stbi_load(
        "C:/Users/mydat/Documents/_active_c/_cpp/YumeGl/yumegl/assets/sonic.png",
        &width,
        &height,
        &nrChannels,
        0
    );

    if (data2)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data2);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // MAIN LOOP
    while (GL::windowIsOpen()) {
        // UPDATE
        // TODO: SOME COOL STUFF

        // INPUT
        input::updateInput();

        if (input::keyPressed(GLFW_KEY_ESCAPE)) {
            GL::setWindowShouldClose(true);
        }

        if (input::keyPressed(GLFW_KEY_1)) {
            std::cerr << "Key pressed: 1\n";
        }
        else if (input::keyDown(GLFW_KEY_2)) {
            std::cerr << "Key down: 2\n";
        }

        // RENDER
        glClear(GL_COLOR_BUFFER_BIT);
        shader.useShader();

        glBindTexture(GL_TEXTURE_2D, _texture);
        glBindVertexArray(tex.VAO);
        glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, nullptr);

        tex.renderTexture();

        GL::swapBuffersPollEvents();
    }

    // DE-INITIALIZATION
    shader.deleteShader();

    tex.deleteData();

    GL::cleanup();

    return 0;
}