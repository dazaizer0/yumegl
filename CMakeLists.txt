cmake_minimum_required(VERSION 3.25)
project(yumegl)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(glfw)
add_subdirectory(glm)

#set(SDL_SHARED ON)

#include(FetchContent)
#FetchContent_Declare(
#        SDL
#        GIT_REPOSITORY https://github.com/libsdl-org/SDL
#        GIT_TAG release-2.30.0
#)
#FetchContent_MakeAvailable(SDL)

#FetchContent_Declare(
#        SDL_mixer
#        GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer
#        GIT_TAG release-2.8.0
#)
#FetchContent_MakeAvailable(SDL_mixer)

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
        src/engine/shader/shader.hpp
        src/engine/render/rd1/triangle.hpp
        src/engine/render/rd1/square.hpp
        src/engine/render/rd1/cube.hpp

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
)

# OPENGL
target_link_libraries(${PROJECT_NAME}
        PRIVATE
        glfw
        glm
        #SDL2::SDL2
        #SDL2_mixer
)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        dep
        ${sdl_BINARY_DIR}/include
)

target_link_directories(${PROJECT_NAME}
        PRIVATE
        assets
)

#target_include_directories(${PROJECT_NAME} PRIVATE dep/imgui dep/imgui/backends ..)
#target_sources(${PROJECT_NAME}
#        PRIVATE
#        dep/imgui/backends/imgui_impl_glfw.cpp
#        dep/imgui/backends/imgui_impl_opengl3.cpp
#        dep/imgui/imgui.cpp
#        dep/imgui/imgui_draw.cpp
#        dep/imgui/imgui_demo.cpp
#        dep/imgui/imgui_tables.cpp
#        dep/imgui/imgui_widgets.cpp
#)