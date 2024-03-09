cmake_minimum_required(VERSION 3.25)
project(yumegl)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(glfw)
add_subdirectory(glm)

# project
add_executable(${PROJECT_NAME}
        # main
        src/source.cpp

        src/config.h
        src/yume.h
        project/YumeLists.h

        # math
        src/engine/math/mathy.hpp
        src/engine/math/colour.hpp

        # input
        src/engine/input/input.hpp

        # other
        src/engine/source/yume_kernel.hpp
        src/engine/source/panic_handler.hpp

        # deps
        dep/glad/glad.c
        dep/stb/stb_image.h
        dep/stb/stb.cpp

        # render
        src/engine/render/rd1/triangle.hpp
        src/engine/render/rd1/square.hpp
        src/engine/render/rd1/cube.hpp
        src/engine/shader/shader.hpp

        # objects
        src/engine/objects/camera.hpp

        # gui
        src/engine/gui/yumeGui.hpp

        # RENDER 2 / 2D
        src/engine/render/rd2/elementary_objects.hpp
        src/engine/render/rd2/square_rd2.hpp
        src/engine/render/rd2/cube_rd2.hpp
        src/engine/render/render.hpp
        src/engine/render/renderer.hpp

        src/engine/render/rd/tex_square.hpp

        # GAME
        project/program.hpp

        # audio
        src/engine/audio/beep_engine.hpp

)

# OPENGL
target_link_libraries(${PROJECT_NAME}
        PRIVATE
        glfw
        glm
)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        dep
)

# assets
target_link_directories(${PROJECT_NAME}
        PRIVATE
        assets
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