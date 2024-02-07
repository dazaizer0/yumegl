#ifndef YUMEGL_YUME_IMGUI_H
#define YUMEGL_YUME_IMGUI_H

#include "../../config.h"
#include "../../yume.h"  

namespace yumeImGui {
	void init() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(yumegl::_window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
	}

    namespace texture {
        void yumeImGui_CreateFrame(render::Texture obj) {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::Begin(obj.name);

            ImGui::Text("Transform");

            ImGui::SliderFloat("size", &obj.size, 0.0f, 1.0f);

            ImGui::SliderFloat("pos_x", &obj.position.x, -1.0f, 1.0f);
            ImGui::SliderFloat("pos_y", &obj.position.y, -1.0f, 1.0f);
            ImGui::SliderFloat("pos_z", &obj.position.z, -1.0f, 1.0f);

            obj.updatePosition();

            ImGui::End();
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }
    }

    namespace cube {
        void yumeImGui_CreateFrame(render::Cube obj) {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::Begin("Cube");

            ImGui::Text("Transform");

            ImGui::SliderFloat("size", &obj.size, 0.0f, 1.0f);

            ImGui::SliderFloat("pos_x", &obj.position.x, -1.0f, 1.0f);
            ImGui::SliderFloat("pos_y", &obj.position.y, -1.0f, 1.0f);
            ImGui::SliderFloat("pos_z", &obj.position.z, -1.0f, 1.0f);

            obj.updatePosition();

            ImGui::End();
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }
    }

    void clear() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}

#endif //YUMEGL_YUME_IMGUI_H
