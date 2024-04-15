#ifndef YUMEGL_CUBE_RD2_HPP
#define YUMEGL_CUBE_RD2_HPP

#include "../../../config.h"
#include "../../../yume.h"

#include "elementary_objects.hpp"
#include "dep/stb/stb_image.h"
#include "../../shader/shader.hpp"

std::vector<float> convertPropertiesToVector(glm::vec3 position, glm::vec3 size) {
    return {
                position.x + -size.x, position.y + -size.y, position.z + -size.z, 0.0f, 0.0f,
                position.x + size.x, position.y + -size.y, position.z + -size.z, 1.0f, 0.0f,
                position.x + size.x, position.y + size.y, position.z + -size.z, 1.0f, 1.0f,
                position.x + size.x, position.y + size.y, position.z + -size.z, 1.0f, 1.0f,
                position.x + -size.x, position.y + size.y, position.z + -size.z, 0.0f, 1.0f,
                position.x + -size.x, position.y + -size.y, position.z + -size.z, 0.0f, 0.0f,

                position.x + -size.x, position.y + -size.y, position.z + size.z, 0.0f, 0.0f,
                position.x + size.x, position.y + -size.y, position.z + size.z, 1.0f, 0.0f,
                position.x + size.x, position.y + size.y, position.z + size.z, 1.0f, 1.0f,
                position.x + size.x, position.y + size.y, position.z + size.z, 1.0f, 1.0f,
                position.x + -size.x, position.y + size.y, position.z + size.z, 0.0f, 1.0f,
                position.x + -size.x, position.y + -size.y, position.z + size.z, 0.0f, 0.0f,

                position.x + -size.x, position.y + size.y, position.z + size.z, 1.0f, 0.0f,
                position.x + -size.x, position.y + size.y, position.z + -size.z, 1.0f, 1.0f,
                position.x + -size.x, position.y + -size.y, position.z + -size.z, 0.0f, 1.0f,
                position.x + -size.x, position.y + -size.y, position.z + -size.z, 0.0f, 1.0f,
                position.x + -size.x, position.y + -size.y, position.z + size.z, 0.0f, 0.0f,
                position.x + -size.x, position.y + size.y, position.z + size.z, 1.0f, 0.0f,

                position.x + size.x, position.y + size.y, position.z + size.z, 1.0f, 0.0f,
                position.x + size.x, position.y + size.y, position.z + -size.z, 1.0f, 1.0f,
                position.x + size.x, position.y + -size.y, position.z + -size.z, 0.0f, 1.0f,
                position.x + size.x, position.y + -size.y, position.z + -size.z, 0.0f, 1.0f,
                position.x + size.x, position.y + -size.y, position.z + size.z, 0.0f, 0.0f,
                position.x + size.x, position.y + size.y, position.z + size.z, 1.0f, 0.0f,

                position.x + -size.x, position.y + -size.y, position.z + -size.z, 0.0f, 1.0f,
                position.x + size.x, position.y + -size.y, position.z + -size.z, 1.0f, 1.0f,
                position.x + size.x, position.y + -size.y, position.z + size.z, 1.0f, 0.0f,
                position.x + size.x, position.y + -size.y, position.z + size.z, 1.0f, 0.0f,
                position.x + -size.x, position.y + -size.y, position.z + size.z, 0.0f, 0.0f,
                position.x + -size.x, position.y + -size.y, position.z + -size.z, 0.0f, 1.0f,

                position.x + -size.x, position.y + size.y, position.z + -size.z, 0.0f, 1.0f,
                position.x + size.x, position.y + size.y, position.z + -size.z, 1.0f, 1.0f,
                position.x + size.x, position.y + size.y,  position.z + size.z, 1.0f, 0.0f,
                position.x + size.x, position.y + size.y, position.z + size.z, 1.0f, 0.0f,
                position.x + -size.x, position.y + size.y, position.z + size.z, 0.0f, 0.0f,
                position.x + -size.x, position.y + size.y, position.z + -size.z, 0.0f, 1.0f
    };
}

namespace rd2 {
    class Cube : public ExtendedObject {
    public:
        shaderSystem::GlProgram shader;

        mathy::vec3yu<> rotationAxis;
        float rotationAngle{};

        Cube(const std::string& path, mathy::vec3yu<> positionV, mathy::vec3yu<> rotation, mathy::vec3yu<> sizeV, bool enableV);

        virtual void render() override;

        void rotate_otherAxis(mathy::vec3yu<> otherAxis, float rotationSpeed) const;

        ~Cube();
    private:
        struct PanicHandler panic { false };
        unsigned int VBO{}, VAO{};

        unsigned int tex{};
        const char* texPath;
        unsigned char* texData;

        unsigned int window_width{};
        unsigned int window_height{};

        std::vector<float> vertices;

        mathy::vec3yu<> prevPosition{};

        // UPDATE
        void updateVertices();
        void refresh() const;

        // RENDER
        void bindTexture() const;
        void render_ownShader() const;
        void render_getShader(const shaderSystem::GlProgram& other_shader) const;
        void render_foregoingShader() const;

        void setRotation() const;
    };

    Cube::Cube(const std::string& path, mathy::vec3yu<> positionV, mathy::vec3yu<> rotation, mathy::vec3yu<> sizeV, bool enableV)
        : ExtendedObject(position, size, enableV) {
        try {
            position = positionV;
            prevPosition = position;
            rotationAxis = rotation;
            size = sizeV;
            enable = enableV;

            window_width = yumegl::WINDOW_WIDTH;
            window_height = yumegl::WINDOW_HEIGHT;

            texPath = path.c_str();

            if (texPath == nullptr) {
                std::cerr << "ERROR:LOADING:TEXTURE" << std::endl;
            }
            else {
                std::cout << "texture loaded correctly\n";
            }

            vertices = convertPropertiesToVector(position.container, size.container);

            // CREATE CUBE
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);

            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(vertices.size() * sizeof(float)), vertices.data(), GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)nullptr);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            // TEXTURE
            glGenTextures(1, &tex);
            glBindTexture(GL_TEXTURE_2D, tex);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            int width, height, nrChannels;
            texData = stbi_load(texPath, &width, &height, &nrChannels, 0);

            if (texData) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            stbi_image_free(texData);

            //setRotation({0.0f, 0.0f, 1.0f}, 360.0f);
        }
        catch (const std::exception& e) {
            std::cerr << "An error occurred during initialization: " << e.what();
            panic.turnOnPanicMode();
        }
    }

    void Cube::updateVertices() {
        vertices = convertPropertiesToVector(position.container, size.container);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(vertices.size() * sizeof(float)), vertices.data(), GL_STATIC_DRAW);
    }

    void Cube::refresh() const {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
    }

    void Cube::bindTexture() const {
        // BIND TEXTURE
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex);
    }

    void Cube::render_ownShader() const {
        // ACTIVATE SHADER
        shader.use();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    void Cube::render_getShader(const shaderSystem::GlProgram& other_shader) const {
        // ACTIVATE SHADER
        other_shader.use();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    void Cube::render_foregoingShader() const {
        // RENDER TEXTURE
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    void Cube::render() {
        if (enable) {
            if (shader.getId()) {
                shader.use();
            }

            bindTexture();
            render_ownShader();

            if (prevPosition.container != position.container) {
                updateVertices();
                refresh();
                prevPosition = position;
            }

            setRotation();
        }
    }

    void Cube::rotate_otherAxis(mathy::vec3yu<> otherAxis, float rotationSpeed) const {
        // ROTATE
        auto model = glm::mat4(1.0f);
        auto view = glm::mat4(1.0f);
        auto projection = glm::mat4(1.0f);

        model = glm::translate(model, glm::vec3(position.x(), position.y(), position.z()));

        model = glm::rotate(model, (float)glfwGetTime() * rotationSpeed, otherAxis.container);

        model = glm::translate(model, -glm::vec3(position.x(), position.y(), position.z()));

        view = glm::translate(view, glm::vec3(position.x(), position.y(), position.z()));
        projection = glm::perspective(glm::radians(45.0f), (float)window_width / (float)window_height, 0.1f, 100.0f);

        unsigned int modelLoc = glGetUniformLocation(shader.getId(), "model");
        unsigned int viewLoc = glGetUniformLocation(shader.getId(), "view");

        glUniformMatrix4fv((GLint)modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv((GLint)viewLoc, 1, GL_FALSE, &view[0][0]);

        shader.setMat4("projection", projection);
    }

    void Cube::setRotation() const {
        auto view = glm::mat4(1.0f);
        auto projection = glm::mat4(1.0f);
        auto model = glm::mat4(1.0f);

        projection = glm::perspective(glm::radians(45.0f), (float)window_width / (float)window_height, 0.1f, 100.0f);
        view = glm::translate(view, glm::vec3(position.x(), position.y(), position.z()));

        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        model = glm::translate(model, glm::vec3(position.x(), position.y(), position.z()));
        model = glm::rotate(model, glm::radians(rotationAngle), rotationAxis.container);
        model = glm::translate(model, -glm::vec3(position.x(), position.y(), position.z()));

        shader.setMat4("model", model);
    }

    Cube::~Cube() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);

        shader.~GlProgram();

        std::cerr << "textures data successfully deleted" << std::endl;
    }
}

#endif
