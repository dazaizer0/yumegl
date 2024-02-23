#ifndef YUMEGL_ELEMENT_HPP
#define YUMEGL_ELEMENT_HPP

#include "../../../config.h"
#include "../../../yume.h"
#include "module.hpp"

namespace rd2 {
    class Square : public rd2::ExtendedModule { // THE MODULE IS MORE EXPENSIVE THAN ORDINARY SQUARE/TEXTURE
        // BECAUSE IT SUPPORTS BOTH SHAPE AND TEXTURE DEPENDING ON THE TEXTURE YOU HAVE
        // TODO: NEW BETTER, UNIVERSAL AND CROSS PLATFORM 2D SQUARE BASED ON OWN SOLUTIONS

        // PROPERTIES
    public:
        shaderSystem::Shader shader;

    private:
        const unsigned int vertex_count{ 4 };
        unsigned int VBO{}, VAO{}, EBO{};

        unsigned int tex{};
        const char* texPath{};
        unsigned char* texData{};

        std::vector<float> vertices;
        std::vector<unsigned int> indices;

        std::string type{};

        // LOGIC
        Square(const std::string& path, mathy::vec3yu<> positionV, colour colorV, mathy::vec3yu<> sizeV, bool enableV);

        void updatePosition();
        void refresh();

        void bindTexture();
        void render_ownShader() const;
        void render_getShader(const shaderSystem::Shader& other_shader) const;
        void render_foregoingShader() const;

        void rotate(glm::vec3 axis, float rotationSpeed);
        void setRotation(glm::vec3 axis, float angle);

        ~Square();

    };

    Square::Square(const std::string& path, mathy::vec3yu<> positionV, colour colorV, mathy::vec3yu<> sizeV, bool enableV) : ExtendedModule(
            positionV, sizeV, enableV) {
        std::string path2 = yumegl::eFunc::yumePath() + "/assets/" + path;
        texPath = path2.c_str();

        if (texPath == nullptr) {
            std::cerr << "ERROR:LOADING:TEXTURE" << std::endl;
        }
        else {
            std::cout << "texture loaded correctly\n";
        }

        position = positionV;
        color = colorV;
        size = sizeV;

        int width, height, nrChannels;
        texData = stbi_load(
                texPath,
                &width,
                &height,
                &nrChannels,
                0
        );

        if (texData) {
            // SET UP VERTEX AND BUFFERS DATA. CONFIGURE VERTEX
            vertices = {
                    // position, position, position
                    // tex coords, tex coords, tex coords

                    position.x() + size.x(), position.y() + size.y(), position.z(),
                    color.r, color.g, color.b,
                    1.0f, 1.0f,

                    position.x() + size.x(), position.y() + -size.y(), position.z(),
                    color.r, color.g, color.b,
                    1.0f, 0.0f,

                    position.x() + -size.x(), position.y() + -size.y(), position.z(),
                    color.r, color.g, color.b,
                    0.0f, 0.0f,

                    position.x() + -size.x(), position.y() + size.y(), position.z(),
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
            glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(vertices.size() * sizeof(float)), vertices.data(), GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(indices.size() * sizeof(float)), indices.data(), GL_STATIC_DRAW);

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

            if (texData) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
                glGenerateMipmap(GL_TEXTURE_2D);

                type = "tex";
            }
            else {
                std::cout << "Failed to load texture" << std::endl;
            }

            setRotation({ 0.0f, 0.0f, 1.0f }, 180.0f);
        }
        else {
            vertices = {
                    // position, position, position
                    // tex coords, tex coords, tex coords

                    position.x() + size.x(), position.y() + size.y(), position.z(),
                    color.r, color.g, color.b,
                    1.0f, 1.0f,

                    position.x() + size.x(), position.y() + -size.y(), position.z(),
                    color.r, color.g, color.b,
                    1.0f, 0.0f,

                    position.x() + -size.x(), position.y() + -size.y(), position.z(),
                    color.r, color.g, color.b,
                    0.0f, 0.0f,

                    position.x() + -size.x(), position.y() + size.y(), position.z(),
                    color.r, color.g, color.b,
                    0.0f, 1.0f
            };

            // GENERATE OBJECT
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);

            // SEND DATA TO BUFFER
            auto buffer_size = static_cast<GLsizeiptr>(vertices.size() * sizeof(float));
            glBufferData(GL_ARRAY_BUFFER, buffer_size, vertices.data(), GL_STATIC_DRAW);

            // POSITION
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, (void*)nullptr);
            glEnableVertexAttribArray(0);

            // COLOR
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, (void*)12);
            glEnableVertexAttribArray(1);

            type = "sq";
        }
        stbi_image_free(texData);
    }

    void Square::updatePosition() {
        if(type == "tex") {

        }
        else if (type == "sq") {

        }
        else {

        }
    }

    void Square::refresh() {
        if(type == "tex") {

        }
        else if (type == "sq") {

        }
        else {

        }
    }

    void Square::bindTexture() {
        if(type == "tex") {

        }
        else if (type == "sq") {

        }
        else {

        }
    }

    void Square::render_ownShader() const {
        if(type == "tex") {

        }
        else if (type == "sq") {

        }
        else {

        }
    }

    void Square::render_getShader(const shaderSystem::Shader &other_shader) const {
        if(type == "tex") {

        }
        else if (type == "sq") {

        }
        else {

        }
    }

    void Square::render_foregoingShader() const {
        if(type == "tex") {

        }
        else if (type == "sq") {

        }
        else {

        }
    }

    void Square::rotate(glm::vec3 axis, float rotationSpeed) {
        if(type == "tex") {

        }
        else if (type == "sq") {

        }
        else {

        }
    }

    void Square::setRotation(glm::vec3 axis, float angle) {
        if(type == "tex") {

        }
        else if (type == "sq") {

        }
        else {

        }
    }

    Square::~Square() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);

        shaderSystem::deleteShader(shader);
    }
}
#endif