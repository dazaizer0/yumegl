cmake_minimum_required(VERSION 3.26)
project(yumegl_mp)

set(CMAKE_CXX_STANDARD 20)

if(WIN32)

    add_subdirectory(glfw)
    add_subdirectory(glm)

elseif(UNIX AND NOT APPLE)

    cmake_policy(SET CMP0072 NEW)
    find_package(OpenGL REQUIRED)

endif()

# PROJECT  ------------------------

add_executable(${PROJECT_NAME}
        source/dependences/glad/glad.c
        source/dependences/glad/glad.h
        source/dependences/stb/stb.cpp
        source/dependences/stb/stb_image.h

        source/yume_program.hpp

        source/kernel.cpp
        source/yume_elementary.h
        source/config.h
        source/engine/math/mathy.hpp
        source/engine/render/rd2/cube_rd2.hpp
        source/engine/render/rd2/elementary_objects.hpp
        source/engine/render/rd2/square_rd2.hpp
        source/engine/render/graphics.hpp
        source/engine/shader/shader.hpp
        source/yume_expanded.h
        source/engine/engine_properties.hpp
        source/engine/panic_handler.hpp
        source/engine/input/input.hpp
)

# PROJECT  ------------------------

if(WIN32)

    # OPENGL
    target_link_libraries(${PROJECT_NAME}
            PRIVATE
            glfw
            glm
    )

    target_include_directories(${PROJECT_NAME}
            PRIVATE
            source/dependences
    )

    # assets
    target_link_directories(${PROJECT_NAME}
            PRIVATE
            project
    )

    target_include_directories(${PROJECT_NAME} PRIVATE source/dependences/imgui source/dependences/imgui/backends ..)
    target_sources(${PROJECT_NAME}
            PRIVATE
            source/dependences/imgui/backends/imgui_impl_glfw.cpp
            source/dependences/imgui/backends/imgui_impl_opengl3.cpp
            source/dependences/imgui/imgui.cpp
            source/dependences/imgui/imgui_draw.cpp
            source/dependences/imgui/imgui_demo.cpp
            source/dependences/imgui/imgui_tables.cpp
            source/dependences/imgui/imgui_widgets.cpp
    )

elseif(UNIX AND NOT APPLE)

    target_link_libraries(${PROJECT_NAME}
            OpenGL::GL
    )

    # IN DEVELOPMENT
    #target_include_directories(${PROJECT_NAME}
    #        dep
    #)

    #target_link_directories(${PROJECT_NAME}
    #        project
    #)

endif()