#ifndef YUMEGL_CUBE_HPP
#define YUMEGL_CUBE_HPP

#include "../../config.h"
#include "../../yume.h"

namespace rd1 {
	class Cube { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>> IN DEVELOPMENT <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    public:
        glm::vec3 position{ 0.0f, 0.0f, 0.0f };
        glm::vec3 size{ 0.0f, 0.0f, 0.0f };
        shaderSystem::Shader shader;

        bool enable{};

        // CONSTRUCTOR
        Cube(const std::string& path, glm::vec3 position_value, glm::vec3 size_value);

        // UPDATE
        void updatePosition();
        void refresh() const;

        // RENDER
        void bindTexture() const;
        void render_ownShader() const;
        void render_getShader(const shaderSystem::Shader& other_shader) const;
        void render_foregoingShader() const;

        // OPERATIONS
        void rotate(glm::vec3 axis, float rotationSpeed) const;
        void setRotation_ownShader(glm::vec3 axis, float angle) const;
        void setRotation_getShader(glm::vec3 axis, const shaderSystem::Shader& other_shader, float angle) const;

        // DATA
        void setWindowSize(unsigned int window_w, unsigned int window_h);

        // DECONSTRUCT
        ~Cube();

    private:
        // GPU
        unsigned int VBO{}, VAO{};

        // TEXTURE
        unsigned int tex{};
        const char* texPath;
        unsigned char* texData;

        // ORIENTATION
        unsigned int window_width{};
        unsigned int window_height{};

        // DATA
        std::vector<float> vertices;
	};

	Cube::Cube(const std::string& path, glm::vec3 position_value, glm::vec3 size_value) {
        // SET PROPERTIES
        std::string path2 = yumegl::eFunc::yumePath() + "/assets/" + path;
        texPath = path2.c_str();

        if (texPath == nullptr) {
            std::cerr << "ERROR:LOADING:TEXTURE" << std::endl;
        }
        else {
            std::cout << "texture loaded correctly\n";
        }

        size = size_value;
        position = position_value;

        // CUBE
        vertices = {
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
                position.x + size.x, position.y + size.y, position.z + size.z, 1.0f, 0.0f,
                position.x + size.x, position.y + size.y, position.z + size.z, 1.0f, 0.0f,
                position.x + -size.x, position.y + size.y, position.z + size.z, 0.0f, 0.0f,
                position.x + -size.x, position.y + size.y, position.z + -size.z, 0.0f, 1.0f
        };

        // CREATE CUBE
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
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
    }

    void Cube::updatePosition() {
        vertices = {
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
                position.x + size.x, position.y + size.y, position.z + size.z, 1.0f, 0.0f,
                position.x + size.x, position.y + size.y, position.z + size.z, 1.0f, 0.0f,
                position.x + -size.x, position.y + size.y, position.z + size.z, 0.0f, 0.0f,
                position.x + -size.x, position.y + size.y, position.z + -size.z, 0.0f, 1.0f
        };

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
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

        // RENDER TEXTURE
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    void Cube::render_getShader(const shaderSystem::Shader& other_shader) const {
        // ACTIVATE SHADER
        other_shader.use();

        // RENDER TEXTURE
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    void Cube::render_foregoingShader() const {
        // RENDER TEXTURE
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    void Cube::rotate(glm::vec3 axis, float rotationSpeed) const {
        // ROTATE
        auto model = glm::mat4(1.0f);
        auto view = glm::mat4(1.0f);
        auto projection = glm::mat4(1.0f);

        auto rotationAxis = axis;

        model = glm::translate(model, glm::vec3(position.x, position.y, position.z));

        model = glm::rotate(model, (float)glfwGetTime() * rotationSpeed, rotationAxis);

        model = glm::translate(model, -glm::vec3(position.x, position.y, position.z));

        view = glm::translate(view, glm::vec3(position.x, position.y, position.z));
        projection = glm::perspective(glm::radians(45.0f), (float)window_width / (float)window_height, 0.1f, 100.0f);

        unsigned int modelLoc = glGetUniformLocation(shader.ID, "model");
        unsigned int viewLoc = glGetUniformLocation(shader.ID, "view");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

        shader.setMat4("projection", projection);
    }

    void Cube::setRotation_ownShader(glm::vec3 axis, float angle) const {
        auto view = glm::mat4(1.0f);
        auto projection = glm::mat4(1.0f);

        auto rotationAxis = axis;

        projection = glm::perspective(glm::radians(45.0f), (float)window_width / (float)window_height, 0.1f, 100.0f);
        view = glm::translate(view, glm::vec3(position.x, position.y, position.z));

        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        auto model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(angle), rotationAxis);
        shader.setMat4("model", model);
    }

    void Cube::setRotation_getShader(glm::vec3 axis, const shaderSystem::Shader& other_shader, float angle) const {
        auto view = glm::mat4(1.0f);
        auto projection = glm::mat4(1.0f);

        auto rotationAxis = axis;

        projection = glm::perspective(glm::radians(45.0f), (float)window_width / (float)window_height, 0.1f, 100.0f);
        view = glm::translate(view, glm::vec3(position.x, position.y, position.z));

        other_shader.setMat4("projection", projection);
        other_shader.setMat4("view", view);

        auto model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(angle), rotationAxis);
        other_shader.setMat4("model", model);
    }

    void Cube::setWindowSize(const unsigned int window_w, const unsigned int window_h) {
        window_width = window_w;
        window_height = window_h;
    }

    Cube::~Cube() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);

        shaderSystem::deleteShader(shader);

        std::cerr << "textures data successfully deleted" << std::endl;
    }
}
#endif
