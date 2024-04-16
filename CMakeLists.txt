cmake_minimum_required(VERSION 3.25)
project(yumegl VERSION 0.0.2)

set(CMAKE_CXX_STANDARD 20)

if(WIN32)

    add_subdirectory(glfw)
    add_subdirectory(glm)

elseif(UNIX AND NOT APPLE)

    cmake_policy(SET CMP0072 NEW)
    find_package(OpenGL REQUIRED)

endif()

# project
add_executable(${PROJECT_NAME}
        dep/glad/glad.c
        dep/stb/stb_image.h
        dep/stb/stb.cpp

        src/kernel.cpp
        src/config.h
        src/yume.h

        project/program.hpp
        project/YumeLists.h

        src/engine/math/mathy.hpp

        src/engine/input/input.hpp

        src/engine/source/yume_source.hpp
        src/engine/source/panic_handler.hpp

        src/engine/objects/camera.hpp

        src/engine/render/graphics.hpp
        src/engine/render/rd1/triangle.hpp
        src/engine/render/rd1/square.hpp
        src/engine/render/rd1/cube.hpp
        src/engine/render/rd2/elementary_objects.hpp
        src/engine/render/rd2/square_rd2.hpp
        src/engine/render/rd2/cube_rd2.hpp
        src/engine/render/rd/tex_square.hpp

        src/engine/audio/beep_engine.hpp

)

if(WIN32)

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
            project
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

elseif(UNIX AND NOT APPLE)

    target_link_libraries(${PROJECT_NAME}
            glfw
            glm
            OpenGL::GL
    )

    target_include_directories(${PROJECT_NAME}
            dep
    )

    # assets
    target_link_directories(${PROJECT_NAME}
            project
    )

endif()