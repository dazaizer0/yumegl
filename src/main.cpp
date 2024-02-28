#include "config.h"
#include "yume.h"
#include "project.h"

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

int main() {
#pragma region INITIALIZATION
    /* ------------------------------------------------
    ----------------- INITIALIZATION ------------------
    ------------------------------------------------ */
    yumegl::init("yumegl");
    yumegl::eFunc::setColor(colour::BLACK());
    glEnable(GL_DEPTH_TEST);

    // IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(yumegl::_window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    auto* tex = new rd::TexSquare("../assets/textures/cat.png", mathy::vec3yu<>{ 0.0f, 0.0f, 0.0f }, colour{ 0.0f, 0.0f, 0.0f, 1.0f }, mathy::vec2yu<>{ 0.45f, 0.9f });
    tex->shader.genShader("../assets/shaders/texture/vertex.glsl", "../assets/shaders/texture/fragment.glsl");
    tex->setRotation(mathy::vec3yu<>{ 0.0f, 0.0f, 1.0f}, 180.0f);

    audio::beep::BeepMusic startMusic {{
        audio::beep::BeepSound{500, 600},
        audio::beep::BeepSound{400, 700},
        audio::beep::BeepSound{800, 700},
        audio::beep::BeepSound{900, 1000},
        audio::beep::BeepSound{400, 900},
        audio::beep::BeepSound{760, 1200}
    }};

    // The "play" function plays the BeepMusic vector which has been set at BeepMusic's constructor
    startMusic.play();

#pragma endregion

#pragma region MAIN_LOOP
    /* ------------------------------------------------
    -------------------- MAIN LOOP --------------------
    ------------------------------------------------ */
    while (yumegl::isWindowOpen()) {
        // UPDATE
        yumegl::update();
        input::update();

        // std::thread playThread(&audio::beep::BeepMusic::play, &startMusic);
        // playThread.join();
        // I tried to apply BeepMusic's multithreading, but without success. The program stops if BeepMusic is playing or not playing at all.
        // TODO: BeepMusic's multithreading

        // INPUT
        if (input::keyPressed(GLFW_KEY_ESCAPE))
            yumegl::setWindowStatus(false);

        /* ------------------------------------------------
        --------------------- RENDER ----------------------
        ------------------------------------------------ */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        tex->render();

        /* ------------------------------------------------
        --------------------- OTHER -----------------------
        ------------------------------------------------ */

        // IMGUI - create frame for tex object
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Texture");

        ImGui::Text("Transform");

        ImGui::SliderFloat("size_x", &tex->size.container.x, 0.0f, 1.0f);
        ImGui::SliderFloat("size_y", &tex->size.container.y, 0.0f, 1.0f);

        ImGui::SliderFloat("pos_x", &tex->position.container.x, 1.0f, -1.0f);
        ImGui::SliderFloat("pos_y", &tex->position.container.y, 1.0f, -1.0f);
        ImGui::SliderFloat("pos_z", &tex->position.container.z, 1.0f, -1.0f);

        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // refresh the tex modified vertices
        tex->updateVertices();
        tex->refresh();

        // OTHER
        yumegl::swapBuffersPollEvents();
    }
#pragma endregion

#pragma region DE_INITIALIZATION
    /* ------------------------------------------------
    --------------- DE -INITIALIZATION ----------------
    ------------------------------------------------ */
    delete tex;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    yumegl::eExit::close();
    return 0;
#pragma endregion
}
