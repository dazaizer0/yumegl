#pragma once

#include "../../config.h"

namespace rtr {
    class triangle{
    public:
        // main data
        std::vector<float> data;

        // properties
        math::vec3<float> position = math::vec3<float>::ZERO();
        math::colorRGBA color = math::colorRGBA::WHITE();

        float size {};

        unsigned int VBO, VAO;

        triangle(math::vec3<float> position, float size, math::colorRGBA color);

        void draw() {
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

        void del() {
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
        }
    };

    triangle::triangle(math::vec3<float> position, float size, math::colorRGBA color) {
        data = {
                position.a + -size, position.b + -size, position.c,
                color.r, color.b, color.g,

                position.a + size, position.b + -size, position.c,
                color.r, color.b, color.g,

                position.a + size, position.b + size, position.c,
                color.r, color.b, color.g,
        };

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
    }
}