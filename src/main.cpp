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

    // IMGUI INITIALIZATION TEST
#pragma region imgui_test
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(yumegl::_window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
#pragma endregion

    // SHADER
    Shader textureShader(
        "texture/vertex_t.glsl",
        "texture/fragment_t.glsl"
    );

    // TEXTURE 
    render::Texture tex = render::Texture(
        "textures/sonic_grass.png",
        mathy::vec3<float>::ZERO(),
        mathy::colorRGBA::WHITE(),
        0.6f
    );
    bool rotating = true;

    // MAIN LOOP
    while (yumegl::isWindowOpen()) {

        // INPUT SYSTEM
        input::updateInput();
        if (input::keyPressed(GLFW_KEY_ESCAPE)) {
            yumegl::setWindowStatus(false);
        }

        if (rotating) {
            tex.rotate(
                    mathy::vec3{0.4f, 0.4f, 0.3f},
                    textureShader,
                    1.5f
            );
        }

        // RENDER
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        tex.render(textureShader.ID);

        ImGui::Begin("Texture");
        ImGui::Text("Change texture rotation");

        if (ImGui::Button("rotating", ImVec2{100.0f, 25.0f})) {
            rotating = !rotating;
        }

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        yumegl::swapBuffersPollEvents();
    }

    // DE-INITIALIZATION
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    tex.deleteData();
    glDeleteShader(textureShader.ID);

    yumegl::close();
    return 0;
}