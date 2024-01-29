cmake_minimum_required(VERSION 3.26)
project(yumegl)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(glfw)

add_executable(${PROJECT_NAME}
        src/main.cpp
        dep/glad/glad.c
        src/config.h
        src/engine/math/mathy.h
        src/engine/input/input.h
        src/engine/source/glImprovements.h
        dep/stb/stb_image.h
        dep/stb/stb.cpp
        src/engine/render/triangle.h
        src/engine/render/square.h
        src/engine/render/texture.h
        src/engine/render/texture.h
  )

target_include_directories(${PROJECT_NAME}
        PRIVATE
        dep
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        glfw
)
