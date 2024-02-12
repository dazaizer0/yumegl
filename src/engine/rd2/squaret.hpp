#ifndef YUMEGL_ELEMENT_HPP
#define YUMEGL_ELEMENT_HPP

#include "../../config.h"
#include "../../yume.h"
#include "module.hpp"

namespace rd2 {
    class Squaret : public rd2::ExtendedModule {
    public:
        // PROPERTIES
        shaderSystem::Shader shader;

        // LOGIC
        [[maybe_unused]] Squaret(glm::vec3 positionV, glm::vec3 sizeV, bool enableV);

        void updatePosition();
        void refresh();

        void bindTexture();
        void render_ownShader() const;
        void render_getShader(const shaderSystem::Shader& other_shader) const;
        void render_foregoingShader() const;

        void rotate(glm::vec3 axis, float rotationSpeed);
        void setRotation(glm::vec3 axis, float angle);

        ~Squaret();

    private:
        const unsigned int vertex_count{ 4 };
        unsigned int VBO{}, VAO{}, EBO{};

        unsigned int tex{};
        const char* texPath{};
        unsigned char* texData{};

        std::vector<float> vertices;
        std::vector<unsigned int> indices;
    };

    [[maybe_unused]] Squaret::Squaret(glm::vec3 positionV, glm::vec3 sizeV, bool enableV) : ExtendedModule(positionV, sizeV, enableV) {
    }

    void Squaret::updatePosition() {

    }

    void Squaret::refresh() {

    }

    void Squaret::bindTexture() {

    }

    void Squaret::render_ownShader() const {

    }

    void Squaret::render_getShader(const shaderSystem::Shader &other_shader) const {

    }

    void Squaret::render_foregoingShader() const {

    }

    void Squaret::rotate(glm::vec3 axis, float rotationSpeed) {

    }

    void Squaret::setRotation(glm::vec3 axis, float angle) {

    }

    Squaret::~Squaret() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);

        shaderSystem::deleteShader(shader);
    }
}

#endif