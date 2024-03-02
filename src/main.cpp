#include "config.h"
#include "yume.h"
#include "project.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

// IMPORTATNT
// 
//#include "SFML/Audio.hpp"
// 
// Due to the new library in our project added by FetchContent, the first debugging may take a little longer than usual.
// If you will see an error saying you don't have openal32.dll file, just find the file in _deps and copy it to your build directory. This should solve the problem.
// We had to remove the SFML library due to linking errors, SFML::Audio - Comming Soon

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

    // OBJECTS
    auto* tex = new rd::TexSquare("../assets/textures/cadst.png", mathy::vec3yu<>{ 0.0f, 0.0f, 0.0f }, colour{ 0.0f, 0.0f, 0.0f, 1.0f }, mathy::vec2yu<>{ 0.45f, 0.9f });
    tex->shader.makeProgramFromPaths("../assets/shaders/texture/vertex.glsl", "../assets/shaders/texture/fragment.glsl");
    tex->setRotation(mathy::vec3yu<>{ 0.0f, 0.0f, 1.0f}, 180.0f);

    audio::beep::BeepMusic startMusic {{
        audio::beep::BeepSound{500, 500},
        audio::beep::BeepSound{400, 400},
        audio::beep::BeepSound{800, 500},
        audio::beep::BeepSound{900, 1000}
    }};

    // The "play" function plays the BeepMusic vector which has been set at BeepMusic's constructor
    // YUMEGL INTRO beep_engine
    startMusic.play();

    // SFML::Audio Music
    // SOON...
    /*sf::Music jojoMusic;
    if (!jojoMusic.openFromFile("../assets/audio/jojo.wav")) {
        std::cerr << "Couldn't find music file." << std::endl;
        std::cerr << "Try to upload the new assets folder to your build directory." << std::endl;
        return -1;
    }
    else {
        std::cout << "The music file has been successfully loaded.\n";
    }
    jojoMusic.setVolume(50.0f);
    jojoMusic.setPitch(1.0f);
    jojoMusic.play();*/

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

        tex->simpleRender();

        /* ------------------------------------------------
        --------------------- OTHER -----------------------
        ------------------------------------------------ */

        // IMGUI - create frame for tex object
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("TexSquare");

        if (ImGui::BeginTabBar("Transform")) {
            if (ImGui::BeginTabItem("size")) {
                ImGui::SliderFloat("X", &tex->size.container.x, 0.0f, 1.0f);
                ImGui::SliderFloat("Y", &tex->size.container.y, 0.0f, 1.0f);
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("position")) {
                ImGui::SliderFloat("X", &tex->position.container.x, 1.0f, -1.0f);
                ImGui::SliderFloat("Y", &tex->position.container.y, 1.0f, -1.0f);
                ImGui::SliderFloat("Z", &tex->position.container.z, 1.0f, -1.0f);
                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }

        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // refresh the tex modified vertices
        tex->updateVertices();
        tex->refresh();

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
