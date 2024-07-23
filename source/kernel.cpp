#include "yume_program.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

int main() {
    try {
        program::setup();
        std::cout << "The SetUp() yumeSubsystem has been succesfully done.\n";
    }
    catch (const std::exception& e) {
        std::cerr << "The SetUp() yumeSubsystem filed!" << std::endl;
    }

    try {
        program::start();
        std::cout << "The Initialize() yumeSubsystem has been succesfully done.\n";
    }
    catch (const std::exception& e) {
        std::cerr << "The Initialize() yumeSubsystem filed!" << std::endl;
    }

    glEnable(GL_DEPTH_TEST);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(yumegl::_window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    while (yumegl::isWindowOpen()) {
        // update
        yumegl::update();
        input::update();

        program::update();

        //render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        program::render();

        yumegl::swapBuffersPollEvents();
    }

    std::cout << "\n\nfinishing processes...\n\n";

    //if (yumegl::audio_enabled)
        //audio::playBeep(600, 600);

    program::close();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    yumegl::eExit::close();

    return 0;
}
