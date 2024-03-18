#include "yume.h"

#include "../project/YumeLists.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

// IMPORTATNT
// 
// #include "SFML/Audio.hpp"
// 
// Due to the new library in our project added by FetchContent, the first debugging may take a little longer than usual.
// If you will see an error saying you don't have openal32.dll file, just find the file in _deps and copy it to your build directory. This should solve the problem.
// We had to remove the SFML library due to linking errors, SFML::Audio - Comming Soon

int main() {
    // chungus 
#pragma region INITIALIZATION_AND_STARTUP
    try {
        Program::SetUp();
        std::cout << "The SetUp() yumeSubsystem has been succesfully done.\n";
    }
    catch (const std::exception& e) {
        std::cerr << "The SetUp() yumeSubsystem filed!" << std::endl;
    }

    try {
        Program::Initialize();
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

    try {
        Program::Start();
        std::cout << "The Start() yumeSubsystem has been succesfully done.\n";
    }
    catch (const std::exception& e) {
        std::cerr << "The Start() yumeSubsystem filed!" << std::endl;
    }

    std::cout << "------------------ \n\n";
#pragma endregion

#pragma region UPDATE
    while (yumegl::isWindowOpen()) {
        // update
        yumegl::update();
        input::update();

        Program::Update();

        //render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Program::Render();

        yumegl::swapBuffersPollEvents();
    }
#pragma endregion

#pragma region DE-INITIALIZATION
    Program::Close();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    yumegl::eExit::close();

    return 0;
#pragma endregion
}
