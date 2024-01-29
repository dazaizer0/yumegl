#pragma once // IN DEVELOPMENT HERE IS A LOT OF MESSSSS

#include "../../config.h"
#include "stb/stb_image.h"

namespace render {
    class texture {
    public:
        std::vector<float> data;
        mathy::vec3<float> position = mathy::vec3<float>::ZERO();
        mathy::colorRGBA color = mathy::colorRGBA::BLACK();
        float size {};

        unsigned int texture_object;
        const char* texture_path;

        unsigned int VBO, VAO;
        int width, height, nrChannels;

        texture(mathy::vec3<float> position, float size, mathy::colorRGBA color, const char* texture_path);

        void render_texture() {
            glBindTexture(GL_TEXTURE_2D, texture_object);
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

        void remove_data() {
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
            glDeleteTextures(1, &texture_object);

            std::cerr << "The object's data has been successfully removed" << std::endl;
        }
    };

    texture::texture(mathy::vec3<float> position, float size, mathy::colorRGBA color, const char* texture_path) {
        // ... (bez zmian)
        //data = {
        //        position.a - size/*0-x*/, position.b - size /*1-y*/,position.c/*2-z*/,
        //        color.r/*3-r*/, color.g/*4-g*/, color.b/*5-b*/,

        //        position.a + size/*6-x*/, position.b - size/*7-y*/, position.c/*8-z*/,
        //        color.r/*9-r*/, color.g/*10-g*/, color.b/*11-b*/,

        //        position.a - size/*12-x*/,  position.b + size/*13-y*/, position.c/*14-z*/,
        //        color.r/*15-r*/, color.g/*16-g*/, color.b/*17-b*/,

        //        position.a + size/*18-x*/,  position.b + size/*19-y*/, position.c/*20-z*/,
        //        color.r/*21-r*/, color.g/*22-g*/, color.b/*23-b*/
        //};

        data = {
                position.x + -size/*0-x*/, position.y + -size /*1-y*/, position.z/*2-z*/,
                color.r/*3-r*/, color.g/*4-g*/, color.b/*5-b*/,
                0.0f, 1.0f,

                position.x + size/*6-x*/, position.y + -size/*7-y*/, position.z/*8-z*/,
                color.r/*9-r*/, color.g/*10-g*/, color.b/*11-b*/,
                1.0f, 0.0f,

                position.x + -size/*12-x*/, position.y + size/*13-y*/, position.z/*14-z*/,
                color.r/*15-r*/, color.g/*16-g*/, color.b/*17-b*/,
                0.0f, 0.0f,

                position.x + size/*18-x*/, position.y + size/*19-y*/, position.z/*20-z*/,
                color.r/*21-r*/, color.g/*22-g*/, color.b/*23-b*/,
                1.0f, 1.0f
        };

        // GENERATE TEXTURE
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

        //position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, (void*)0);
        glEnableVertexAttribArray(0);

        //color
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, (void*)12);
        glEnableVertexAttribArray(1);

        float borderColor[] = { color.a, color.g, color.b, color.a };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

        glGenTextures(1, &texture_object);
        glBindTexture(GL_TEXTURE_2D, texture_object);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        std::cout << "loading texture: " << texture_path << "\n";

        FILE *file = fopen(texture_path, "r");
        if (!file) {
            perror("Error opening file");
        }

        unsigned char* texture_data = stbi_load(texture_path, &width, &height, &nrChannels, 0);

        if (texture_data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);
            glGenerateMipmap(GL_TEXTURE_2D);

            std::cout << "texture loaded correctly\n";
        }
        else {
            std::cout << "Failed to load texture: " << stbi_failure_reason() << "\n";
        }

        if (!texture_data) {
            std::cout << "Failed to load texture: " << stbi_failure_reason() << "\n";
        }

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(texture_data);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }
}