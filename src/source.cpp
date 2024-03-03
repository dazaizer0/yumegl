#include "yume.h"

#include "../project/YumeLists.h"

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
    // chungus 
    Program::initialize();

    glEnable(GL_DEPTH_TEST);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(yumegl::_window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    Program::start();

    while (yumegl::isWindowOpen()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Program::update();
        yumegl::swapBuffersPollEvents();
    }

    Program::close();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    yumegl::eExit::close();

    return 0;
}
