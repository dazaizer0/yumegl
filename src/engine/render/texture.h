#pragma once // IN DEVELOPMENT HERE IS A LOT OF MESSSSS

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
        Texture(mathy::vec3<float> position_valuE, mathy::colorRGBA color_value, float size_value);

        void renderTexture() const; /* {
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, vertex_count);
        }*/

        void deleteData(); /*{
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);

            std::cerr << "The object's data has been successfully removed" << std::endl;
        }*/

        // MAIN DATA VECTOR
        std::vector<float> data;
        unsigned int _texture;

        // VBO, VAO
        unsigned int VBO{}, VAO{};
        int vertex_count;
    };

    Texture::Texture(mathy::vec3<float> position_value, mathy::colorRGBA color_value, float size_value) {
        // SET PROPERTIES
        position = position_value;
        color = color_value;
        size = size_value;

        // CREATE DATA
        //data = {
        //        position.a - size/*0-x*/, position.b - size /*1-y*/,position.c/*2-z*/,
        //        color.r/*3-r*/, color.g/*4-g*/, color.b/*5-b*/,
        // TEXTURE VERTICASES

        //        position.a + size/*6-x*/, position.b - size/*7-y*/, position.c/*8-z*/,
        //        color.r/*9-r*/, color.g/*10-g*/, color.b/*11-b*/,
        // TEXTURE VERTICASES

        //        position.a - size/*12-x*/,  position.b + size/*13-y*/, position.c/*14-z*/,
        //        color.r/*15-r*/, color.g/*16-g*/, color.b/*17-b*/,
        // TEXTURE VERTICASES

        //        position.a + size/*18-x*/,  position.b + size/*19-y*/, position.c/*20-z*/,
        //        color.r/*21-r*/, color.g/*22-g*/, color.b/*23-b*/
        // TEXTURE VERTICASES
        //};

        data = {
                // positions          // colors           // texture coords
                0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
                0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
                -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
                -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
        };

        vertex_count = 4;

        // GENERATE OBJECT
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        // SEND DATA TO BUFFER
        auto buffer_size = static_cast<GLsizeiptr>(data.size() * sizeof(float));
        glBufferData(GL_ARRAY_BUFFER, buffer_size, data.data(), GL_STATIC_DRAW);

        // POSITION
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, (void*)nullptr);
        glEnableVertexAttribArray(0);

        // COLOR
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, (void*)12);
        glEnableVertexAttribArray(1);

        // TEXTURE
        glGenTextures(1, &_texture);
        glBindTexture(GL_TEXTURE_2D, _texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        int width, height, nrChannels;
        unsigned char* data2 = stbi_load(
            "C:/Users/mydat/Documents/_active_c/_cpp/YumeGl/yumegl/assets/sonic.png",
            &width,
            &height,
            &nrChannels,
            0
        );

        if (data2)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data2);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }

    // RENDER
    void Texture::renderTexture() const {
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, vertex_count);

        glBindTexture(GL_TEXTURE_2D, _texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, nullptr);
    }

    // DELETE
    void Texture::deleteData() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
}