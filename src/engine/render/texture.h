#pragma once // IN DEVELOPMENT

#include "../../config.h"

#include "stb/stb_image.h"

namespace render {
    // SQUARE
    class Texture {
    public:
        // PROPERTIES
        mathy::vec3<float> position = mathy::vec3<float>::ZERO();
        mathy::colorRGBA color = mathy::colorRGBA::BLACK();
        float size{};

        // CONSTRUCTOR
        Texture(const char* path, mathy::vec3<float> position_value, mathy::colorRGBA color_value, float size_value);

        //FUNCTIONS
        void updatePosition();
        void refresh();
        void render(unsigned int shader) const;
        void deleteData();

    private:
        unsigned int VBO, VAO, EBO;

        const char *texPath;
        unsigned int tex;
        unsigned char* texData;
    };

    Texture::Texture(const char* path, mathy::vec3<float> position_value, mathy::colorRGBA color_value, float size_value) {
        // SET PROPERTIES
        texPath = path;
        position = position_value;
        color = color_value;
        size = size_value;

        // SET UP VERTEX AND BUFFERS DATA. CONFIGURE VERTEX 
        float vertices[] = {
            // position, position, position
            // color, color, color
            // tex coords, tex coords, tex coords

             position.x + size, position.y + size, position.z,
             color.r, color.g, color.b,
             1.0f, 1.0f,

             position.x + size, position.y + -size, position.z,
             0.0f, 1.0f, 0.0f,
             1.0f, 0.0f,

            position.x + -size, position.y + -size, position.z,
            color.r, color.g, color.b,
            0.0f, 0.0f,

            position.x + -size, position.y + size, position.z,
            color.r, color.g, color.b,
            0.0f, 1.0f
        };
        unsigned int indices[] = {
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
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // POSITION
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
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
            //example: "C:/Users/mydat/Documents/_active_c/_cpp/YumeGl/yumegl/assets/sonic.png",
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
    }

    // FUNCTIONS
    void Texture::updatePosition() {

    }

    void Texture::refresh() {

    }

    // RENDER
    void Texture::render(unsigned int shader) const {
        glBindTexture(GL_TEXTURE_2D, tex);

        glUseProgram(shader);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    // DELETE
    void Texture::deleteData() {
        std::cerr << "Textures data successfully deleted" << std::endl;

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
}