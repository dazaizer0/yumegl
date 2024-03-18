#ifndef YUMEGL_ELEMENT_HPP
#define YUMEGL_ELEMENT_HPP

#include "../../../config.h"
#include "../../../yume.h"
#include "elementary_objects.hpp"

namespace rd2 {
    class Square : public rd2::ExtendedObject { // THE MODULE IS MORE EXPENSIVE THAN ORDINARY SQUARE/TEXTURE
        // BECAUSE IT SUPPORTS BOTH SHAPE AND TEXTURE DEPENDING ON THE TEXTURE YOU HAVE
        // TODO: NEW BETTER, UNIVERSAL AND CROSS PLATFORM 2D SQUARE BASED ON OWN SOLUTIONS

        // PROPERTIES
    public:
        shaderSystem::GlProgram shader;
        colour color = colour::PURPLE();

        void render();

        void rotate(mathy::vec3yu<> axis, float rotationSpeed);
        void setRotation(mathy::vec3yu<> axis, float angle);

    private:
        const unsigned int vertex_count{ 4 };
        unsigned int VBO{}, VAO{}, EBO{};

        unsigned int tex{};
        const char* texPath{};
        unsigned char* texData{};

        struct PanicHandler panic { false };

        std::vector<float> vertices;
        std::vector<float> prevVertices;
        std::vector<unsigned int> indices;

        // LOGIC
        Square(const std::string& path, mathy::vec3yu<> positionV, colour colorV, mathy::vec3yu<> sizeV, bool enableV);

        void updatePosition();
        void refresh();

        void bindTexture();
        void render_ownShader() const;
        void render_getShader(const shaderSystem::GlProgram& other_shader) const;
        void render_foregoingShader() const;

        ~Square();

    };

    Square::Square(const std::string& path, mathy::vec3yu<> positionV, colour colorV, mathy::vec3yu<> sizeV, bool enableV) 
        : ExtendedObject(positionV, sizeV, enableV) {
        position = positionV;
        color = colorV;
        size = sizeV;

        // ...
        // ...
        // ...

        setRotation(mathy::vec3yu<>{ 0.0f, 0.0f, 1.0f }, 180.0f);
        panic.considerPanicMode();
    }

    void Square::updatePosition() {
        // update previous vertices
        prevVertices = vertices;

        // update vertices
        // .........
        // ......
        // ...
    }

    void Square::refresh() {
    }

    void Square::bindTexture() {
    }

    void Square::render_ownShader() const {
    }

    void Square::render_getShader(const shaderSystem::GlProgram &other_shader) const {
    }

    void Square::render_foregoingShader() const {
    }

    void Square::render() {
        // render universal square rd2 with only one function
        bindTexture();
        if (shader.getId()) {
            shader.use();
            render_ownShader();
        }
        else {
            render_foregoingShader();
        }

        if (vertices != prevVertices) {
            updatePosition();
            refresh();

            prevVertices = vertices;
        }

    }

    void Square::rotate(mathy::vec3yu<> axis, float rotationSpeed) {
    }

    void Square::setRotation(mathy::vec3yu<> axis, float angle) {
    }

    Square::~Square() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);

        shader.~GlProgram();
    }
}
#endif