#ifndef YUMEGL_TEX_SQUARE_HPP
#define YUMEGL_TEX_SQUARE_HPP

#include "../../../config.h"
#include "../../../yume_elementary.h"

namespace rd {
    class TexSquare {
    public:
        mathy::vec3yu<> position{ 0.0f, 0.0f, 0.0f };
        colour color = colour::BLACK();
        shaderSystem::GlProgram shader;

        mathy::vec2yu<> size{};
        bool enable{ true };

        // CONSTRUCTOR
        TexSquare(const std::string& path, mathy::vec3yu<> position_value, colour color_value, mathy::vec2yu<> size_value);
        ~TexSquare();

        // FUNCTIONS
        void updateVertices();
        void refresh() const;

        void simpleRender();
        void bindTexture() const;
        void render_getShader(const shaderSystem::GlProgram& other_shader) const;

        void rotate(mathy::vec3yu<> axis, float rotationSpeed) const;
        void setRotation(mathy::vec3yu<> axis, float angle) const;

    private:
        void textureErrorHandler();
        void render_ownShader() const;
        void render_foregoingShader() const;

        unsigned int VBO{}, VAO{}, EBO{};

        unsigned int tex{};
        const char* texPath;
        unsigned char* texData;
        int nrChannels;

        struct PanicHandler panic { false };

        int texWidth{}, texHeight{};

        std::vector<float> vertices;
        std::vector<unsigned int> indices;

        mathy::vec3yu<> prevPosition{};
    };

    TexSquare::TexSquare(const std::string& path, mathy::vec3yu<> position_value, colour color_value, mathy::vec2yu<> size_value) {
        // SET PROPERTIES
        // std::string path2 = yumegl::eFunc::yumePath() + "/assets/" + path;
        texPath = path.c_str();

        if (texPath == nullptr) {
            std::cerr << "ERROR:LOADING:TEXTURE" << std::endl;
        }
        else {
            std::cout << "Texture loaded correctly\n";
        }

        // texPath = yumegl::convertToAsssetsPath(path);

        position = position_value;
        prevPosition = position;
        color = color_value;
        size = size_value;

        // SET UP VERTEX AND BUFFERS DATA. CONFIGURE VERTEX 
        try {
            vertices = {
                // position, color, tex coords
                position.x() + size.x(), position.y() + size.y(), position.z(),
                color.r, color.g, color.b,
                0.0f, 1.0f,

                position.x() + size.x(), position.y() + -size.y(), position.z(),
                color.r, color.g, color.b,
                0.0f, 0.0f,

                position.x() + -size.x(), position.y() + -size.y(), position.z(),
                color.r, color.g, color.b,
                1.0f, 0.0f,

                position.x() + -size.x(), position.y() + size.y(), position.z(),
                color.r, color.g, color.b,
                1.0f, 1.0f
            };
            indices = {
                // triangle 1
                0, 1, 3,
                // triangle 2
                1, 2, 3
            };

            // CREATE TEX-SQUARE
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
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            texData = stbi_load(
                texPath,
                &texWidth,
                &texHeight,
                &nrChannels,
                0
            );

            if (texData) {
                GLenum format = GL_RGB;
                if (nrChannels == 1)
                    format = GL_RED;
                else if (nrChannels == 3)
                    format = GL_RGB;
                else if (nrChannels == 4)
                    format = GL_RGBA;

                glTexImage2D(GL_TEXTURE_2D, 0, format, texWidth, texHeight, 0, format, GL_UNSIGNED_BYTE, texData);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else {
                std::cerr << "Failed to load texture" << std::endl;
                panic.turnOnPanicMode();
            }
            stbi_image_free(texData);
            std::cout << "An object has been created successfully\n";
        }
        catch (const std::exception& e) {
            std::cerr << "An error occurred during initialization: " << e.what();
        }

        std::cout << "Checking panic mode...\n";
        panic.considerPanicMode();
        std::cout << "The object has been successfully initialized\n";
    }

    // FUNCTIONS
    void TexSquare::updateVertices() {
        vertices = {
            // position, color, tex coords
            position.x() + size.x(), position.y() + size.y(), position.z(),
            color.r, color.g, color.b,
            0.0f, 1.0f,

            position.x() + size.x(), position.y() + -size.y(), position.z(),
            color.r, color.g, color.b,
            0.0f, 0.0f,

            position.x() + -size.x(), position.y() + -size.y(), position.z(),
            color.r, color.g, color.b,
            1.0f, 0.0f,

            position.x() + -size.x(), position.y() + size.y(), position.z(),
            color.r, color.g, color.b,
            1.0f, 1.0f
        };

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(vertices.size() * sizeof(float)), vertices.data(), GL_STATIC_DRAW);
    }

    void TexSquare::refresh() const {
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    }

    // RENDER
    void TexSquare::textureErrorHandler() {
        if (texData) {
            GLenum format = GL_RGB;
            if (nrChannels == 1)
                format = GL_RED;
            else if (nrChannels == 3)
                format = GL_RGB;
            else if (nrChannels == 4)
                format = GL_RGBA;

            glTexImage2D(GL_TEXTURE_2D, 0, format, texWidth, texHeight, 0, format, GL_UNSIGNED_BYTE, texData);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            panic.turnOnPanicMode();
        }
    }

    void TexSquare::simpleRender() {
        glBindTexture(GL_TEXTURE_2D, tex);

        if (shader.getId()) {
            shader.use();
        }

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        if (prevPosition.container != position.container) {
            this->updateVertices();
            this->refresh();

            prevPosition = position;
        }
    }

    void TexSquare::bindTexture() const {
        glBindTexture(GL_TEXTURE_2D, tex);
    }

    void TexSquare::render_ownShader() const {
        shader.use();

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

    void TexSquare::render_getShader(const shaderSystem::GlProgram& other_shader) const {
        other_shader.use();

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

    void TexSquare::render_foregoingShader() const {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

    void TexSquare::rotate(mathy::vec3yu<> axis, float rotationSpeed) const {
        auto transform = glm::mat4{ 1.0f };

        transform = glm::translate(transform, position.container);
        transform = glm::rotate(transform, rotationSpeed * (float)glfwGetTime(), axis.container);
        transform = glm::translate(transform, -position.container);

        shader.use();
        shader.setMat4("transform", transform);
    }

    void TexSquare::setRotation(mathy::vec3yu<> axis, float angle) const {
        auto transform = glm::mat4{ 1.0f };

        transform = glm::rotate(transform, glm::radians(angle), axis.container);
        shader.use();
        shader.setMat4("transform", transform);
    }

    // DELETE
    TexSquare::~TexSquare() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);

        shader.~GlProgram();

        std::cout << "Textures data successfully deleted" << std::endl;
    }
}
#endif