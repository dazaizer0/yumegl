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

        # math
        src/engine/math/mathy.h

        # input
        src/engine/input/input.h

        # other
        src/engine/source/yume_kernel.h

        # deps
        dep/glad/glad.c
        dep/stb/stb_image.h
        dep/stb/stb.cpp

        # render
        src/engine/render/triangle.h
        src/engine/render/square.h
        src/engine/shader/shader.h
        src/engine/render/texture.h
)

# OPENGL
target_include_directories(${PROJECT_NAME}
        PRIVATE
        dep
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        glfw
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        glm
)


