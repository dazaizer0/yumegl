cmake_minimum_required(VERSION 3.26)
project(YumeGL)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(glfw)

add_executable(${PROJECT_NAME}
        src/main.cpp
        dep/glad/glad.c
        src/config.h
        src/engine/shaders/shader.h
        src/engine/shaders/shader.h
        src/engine/render/triangle_modules.h
        src/engine/render/square_template.h
        src/engine/source/yume_math.h
        src/engine/source/yume_math.h
        src/engine/input/input.h
        src/engine/input/input.h
        src/engine/source/gl_improvements.h
        src/engine/source/gl_improvements.h
        src/engine/render/triangle_template.h
        src/engine/render/square_module.h
        dep/stb/stb_image.h
        src/engine/render/textures.h
        dep/stb/stb.cpp
)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        dep
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        glfw
)
