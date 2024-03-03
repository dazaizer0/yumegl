#pragma once

#include "../src/yume.h"

namespace Program {
    // CREATE OBJECTS
    rd::TexSquare* tex{ nullptr };
    audio::beep::BeepMusic* startMusic{ nullptr };

    void Initialize() {
        yumegl::init("yumegl");
        yumegl::eFunc::setColor(colour::PURPLE());

        tex = new rd::TexSquare("../project/textures/chungus.png", mathy::vec3yu<>{ 0.0f, 0.0f, 0.0f }, colour{ 0.0f, 0.0f, 0.0f, 1.0f }, mathy::vec2yu<>{ 0.45f, 0.9f });
        tex->shader.makeProgramFromPaths("../project/shaders/texture/vertex.glsl", "../project/shaders/texture/fragment.glsl");
        tex->setRotation(mathy::vec3yu<>{ 0.0f, 0.0f, 1.0f}, 180.0f);

        startMusic = new audio::beep::BeepMusic{ {
            audio::beep::BeepSound{500, 500},
            audio::beep::BeepSound{400, 400},
            audio::beep::BeepSound{800, 500},
            audio::beep::BeepSound{900, 1000}
        } };
    }

    void Start() {
        std::cout << "yumegl 0.0.0.2\n";

        startMusic->play();
    }

    void Update() {
        yumegl::update();
        input::update();

        // std::thread playThread(&audio::beep::BeepMusic::play, &startMusic);
        // playThread.join();
        // I tried to apply BeepMusic's multithreading, but without success. The program stops if BeepMusic is playing or not playing at all.
        // TODO: BeepMusic's multithreading

        // INPUT
        if (input::keyPressed(GLFW_KEY_ESCAPE))
            yumegl::setWindowStatus(false);

        if (input::keyPressed(GLFW_KEY_P))
            std::cout << "pressed\n";

        /* ------------------------------------------------
        --------------------- RENDER ----------------------
        ------------------------------------------------ */
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
    }

    void Close() {
        delete tex;
    }
}
