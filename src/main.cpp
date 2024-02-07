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
    glEnable(GL_DEPTH_TEST);

    Shader cubeShader(
        "texture/vertex_t3d.glsl",
        "texture/fragment_t3d.glsl"
    );

    // CUBE
    render::Cube cube = render::Cube("textures\\sonic_grass.png");

    // MAIN LOOP
    while (yumegl::isWindowOpen()) {
        // INPUT SYSTEM
        input::updateInput();
        if (input::keyPressed(GLFW_KEY_ESCAPE)) {
            yumegl::setWindowStatus(false);
        }

        // RENDER
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // BIND TEXTURE -- TEMPORARY MANUAL SOLUTION OF RENDERING AND ROTATEING CUBE
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, cube.tex);

        // RENDER TEXTURE
        glBindVertexArray(cube.VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // ACTIVATE SHADER
        glUseProgram(cubeShader.ID);

        // ROTATE
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
        view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);

        unsigned int modelLoc = glGetUniformLocation(cubeShader.ID, "model");
        unsigned int viewLoc  = glGetUniformLocation(cubeShader.ID, "view");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

        cubeShader.setMat4("projection", projection);

        // SWAP POLL EVENTS
        yumegl::swapBuffersPollEvents();
    }

    // DE-INITIALIZATION
    yumeImGui::clear();

    glDeleteVertexArrays(1, &cube.VAO);
    glDeleteBuffers(1, &cube.VBO);

    glDeleteShader(cubeShader.ID);

    yumegl::eExit::close();
    return 0;
}