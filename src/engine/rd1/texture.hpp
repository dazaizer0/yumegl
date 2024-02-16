#ifndef TEXTURE_H
#define TEXTURE_H

#include "../../config.h"
#include "../../yume.h"
#include "stb/stb_image.h"

namespace rd1 {
    class Texture {
    public:
        glm::vec3 position{ 0.0f, 0.0f, 0.0f };
        colour color = colour::BLACK();
        shaderSystem::Shader shader;

        glm::vec2 size{};
        bool enable{};

        // CONSTRUCTOR
        Texture(const std::string& path, glm::vec3 position_value, colour color_value, glm::vec2 size_value);
        ~Texture();

        //FUNCTIONS
        void updatePosition();
        void refresh() const;

        void bindTexture() const;
        void render_ownShader() const;
        void render_getShader(const shaderSystem::Shader& other_shader) const;
        void render_foregoingShader() const;

        void rotate(glm::vec3 axis, float rotationSpeed) const;
        void setRotation(glm::vec3 axis, float angle) const;

    private:
        unsigned int VBO{}, VAO{}, EBO{};

        unsigned int tex{};
        const char* texPath;
        unsigned char* texData;

        std::vector<float> vertices;
        std::vector<unsigned int> indices;
    };

    Texture::Texture(const std::string& path, glm::vec3 position_value, colour color_value, glm::vec2 size_value) {
        // SET PROPERTIES
        std::string path2 = yumegl::eFunc::yumePath() + "/assets/" + path;
        texPath = path2.c_str();

        if (texPath == nullptr) {
            std::cerr << "ERROR:LOADING:TEXTURE" << std::endl;
        }
        else {
            std::cout << "texture loaded correctly\n";
        }

        // texPath = yumegl::convertToAsssetsPath(path);

        position = position_value;
        color = color_value;
        size = size_value;

        // SET UP VERTEX AND BUFFERS DATA. CONFIGURE VERTEX 
        vertices = {
            // position, position, position
            // tex coords, tex coords, tex coords

             position.x + size.x, position.y + size.y, position.z,
             color.r, color.g, color.b,
             1.0f, 1.0f,

             position.x + size.x, position.y + -size.y, position.z,
             color.r, color.g, color.b,
             1.0f, 0.0f,

            position.x + -size.x, position.y + -size.y, position.z,
            color.r, color.g, color.b,
            0.0f, 0.0f,

            position.x + -size.x, position.y + size.y, position.z,
            color.r, color.g, color.b,
            0.0f, 1.0f
        };
        indices = {
            // triangle 1
            // triangle 2

            0, 1, 3,
            1, 2, 3
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr )(vertices.size() * sizeof(float)), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr )(indices.size() * sizeof(float)), indices.data(), GL_STATIC_DRAW);

        // POSITION
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)nullptr);
        glEnableVertexAttribArray(0);

        // COLOR
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // TEXTURE COORD
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // LOADING TEXTURE
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);

        // TEXTURE PARAMETERS
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // FILTER
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        int width, height, nrChannels;
        texData = stbi_load(
            texPath,
            &width,
            &height,
            &nrChannels,
            0
        );

        if (texData) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(texData);

        setRotation({ 0.0f, 0.0f, 1.0f }, 180.0f);
    }

    // FUNCTIONS
    void Texture::updatePosition() {
        vertices = {
            // position, position, position
            // tex coords, tex coords, tex coords

             position.x + size.x, position.y + size.y, position.z,
             color.r, color.g, color.b,
             1.0f, 1.0f,

             position.x + size.x, position.y + -size.y, position.z,
             color.r, color.g, color.b,
             1.0f, 0.0f,

            position.x + -size.x, position.y + -size.y, position.z,
            color.r, color.g, color.b,
            0.0f, 0.0f,

            position.x + -size.x, position.y + size.y, position.z,
            color.r, color.g, color.b,
            0.0f, 1.0f
        };

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr )(vertices.size() * sizeof(float)), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr )(indices.size() * sizeof(float)), indices.data(), GL_STATIC_DRAW);
    }

    void Texture::refresh() const {
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    }

    // RENDER
    void Texture::bindTexture() const {
        glBindTexture(GL_TEXTURE_2D, tex);
    }

    void Texture::render_ownShader() const {
        shader.use();

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

    void Texture::render_getShader(const shaderSystem::Shader& other_shader) const {
        other_shader.use();

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

    void Texture::render_foregoingShader() const {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

    void Texture::rotate(glm::vec3 axis, float rotationSpeed) const {
        auto transform = glm::mat4(1.0f);
        auto rotationAxis = axis;

        transform = glm::translate(transform, glm::vec3(position.x, position.y, position.z));
        transform = glm::rotate(transform, rotationSpeed * (float)glfwGetTime(), rotationAxis);
        transform = glm::translate(transform, -glm::vec3(position.x, position.y, position.z));

        shader.use();
        unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
        glUniformMatrix4fv((GLint)transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
    }

    void Texture::setRotation(glm::vec3 axis, float angle) const {
        auto transform = glm::mat4(1.0f);

        glm::vec3 rotationAxis = axis;

        transform = glm::rotate(transform, glm::radians(angle), rotationAxis);
        //transform = glm::scale(transform, glm::vec3(0.5, 0.5, 0.5));

        shader.use();
        unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
        glUniformMatrix4fv((GLint)transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
    }

    // DELETE
    Texture::~Texture() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);

        shaderSystem::deleteShader(shader);

        std::cerr << "Textures data successfully deleted" << std::endl;
    }
}
#endif