cmake_minimum_required(VERSION 3.25)
project(yumegl)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(glfw)
add_subdirectory(glm)

set(SFML_VERSION "2.6.1")

include(FetchContent)
FetchContent_Declare(
    sfml
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"
    GIT_TAG        "${SFML_VERSION}"
)

FetchContent_GetProperties(sfml)
if(NOT sfml_POPULATED)
    FetchContent_Populate(sfml)
    add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR})
endif()

set(SOURCE
    src/main.cpp
)

# project
add_executable(${PROJECT_NAME}
        # main
        src/main.cpp
        src/config.h
        src/yume.h
        src/project.h

        # math
        src/engine/math/mathy.hpp
        src/engine/math/colour.hpp

        # input
        src/engine/input/input.hpp

        # other
        src/engine/source/yume_kernel.hpp

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
        src/engine/render/rd2/module.hpp
        src/engine/render/rd2/square_rd2.hpp
        src/engine/render/rd2/cube_rd2.hpp

        src/engine/render/rd/tex_square.hpp

        # GAME
        assets/game.hpp

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

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        sfml-audio
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall)
