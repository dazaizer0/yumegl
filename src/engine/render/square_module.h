#pragma once

#include "../../config.h"

namespace sqm {
    class classic_square {
    public:
        std::vector<float> data;
        classic_square();
        virtual void draw();
        virtual void del();

        unsigned int VBO, VAO, vertex_count;
    };

    class modern_square : public classic_square {
    public:
        math::vec3<float> position = math::vec3<float>::ZERO();
        math::color4 color = math::color4::BLACK();
        float size {};

        modern_square(math::vec3<float> position, math::color4 color, float size);

        void draw() override {
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, vertex_count);
        }

        void del() override {
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
        }

    };

    modern_square::modern_square(math::vec3<float> position, math::color4 color, float size) {
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
                position.a + -size/*0-x*/, position.b + -size /*1-y*/, position.c/*2-z*/,
                color.r/*3-r*/, color.g/*4-g*/, color.b/*5-b*/,

                position.a + size/*6-x*/, position.b + -size/*7-y*/, position.c/*8-z*/,
                color.r/*9-r*/, color.g/*10-g*/, color.b/*11-b*/,

                position.a + -size/*12-x*/, position.b + size/*13-y*/, position.c/*14-z*/,
                color.r/*15-r*/, color.g/*16-g*/, color.b/*17-b*/,

                position.a + size/*18-x*/, position.b + size/*19-y*/, position.c/*20-z*/,
                color.r/*21-r*/, color.g/*22-g*/, color.b/*23-b*/
        };

        vertex_count = 4;

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