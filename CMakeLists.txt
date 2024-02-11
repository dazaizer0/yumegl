cmake_minimum_required(VERSION 3.25)
project(yumegl)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(glfw)
add_subdirectory(glm)

# project
add_executable(${PROJECT_NAME}
        # main
        src/main.cpp
        src/config.h
        src/yume.h

        # math
        src/engine/math/mathy.hpp

        # input
        src/engine/input/input.hpp

        # other
        src/engine/source/yume_kernel.hpp

        # deps
        dep/glad/glad.c
        dep/stb/stb_image.h
        dep/stb/stb.cpp

        # render
        src/engine/render/triangle.hpp
        src/engine/render/square.hpp
        src/engine/shader/shader.hpp
        src/engine/render/texture.hpp
        src/engine/gui/yume_imgui.hpp
        src/engine/render/cube.hpp
        src/engine/objects/camera.hpp
        src/engine/gui/yumeGui.hpp
        src/engine/renderer/module.hpp
)

# OPENGL
target_include_directories(${PROJECT_NAME}
        PRIVATE
        dep
)

target_include_directories(${PROJECT_NAME} PRIVATE dep/imgui dep/imgui/backends ..)
target_sources(${PROJECT_NAME}
        PRIVATE
        dep/imgui/backends/imgui_impl_glfw.cpp
        dep/imgui/backends/imgui_impl_opengl3.cpp
        dep/imgui/imgui.cpp
        dep/imgui/imgui_draw.cpp
        dep/imgui/imgui_demo.cpp
        dep/imgui/imgui_tables.cpp
        dep/imgui/imgui_widgets.cpp
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        glfw
        glm
)