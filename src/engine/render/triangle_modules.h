#pragma once

#include "../../config.h"

namespace trm {
    class classic_triangle {
    public:
        std::vector<float> data;
        classic_triangle();
        virtual void draw();
        virtual void del();

        unsigned int VBO, VAO, vertex_count;
    };

    class modern_triangle : public classic_triangle {
    public:
        modern_triangle();

        void draw() override {
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, vertex_count);
        }
        void del() override {
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
        }
    };

    modern_triangle::modern_triangle() {
        data = {
                -0.5f/*x*/, -0.5f /*y*/, -0.0f/*z*/, 1.0f/*r*/, 1.0f/*g*/, 1.0f/*b*/,
                0.5f/*x*/, -0.5f/*y*/, 0.0f/*z*/, 1.0f/*r*/, 1.0f/*g*/, 1.0f/*b*/,
                -0.5f/*x*/,  0.5f/*y*/, 0.0f/*z*/, 1.0f/*r*/, 1.0f/*g*/, 1.0f/*b*/
        };
        vertex_count = 3;

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