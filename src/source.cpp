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
    // chungus 
    Program::initialize();

    Program::update();

    Program::close();

    return 0;
}
