#pragma once // IN DEVELOPMENT HERE IS A LOT OF MESSSSS

#include "../../config.h"

namespace render {
    class square {
    public:
        std::vector<float> data;
        mathy::vec3<float> position = mathy::vec3<float>::ZERO();
        mathy::colorRGBA color = mathy::colorRGBA::BLACK();
        float size {};

        unsigned int VBO, VAO, vertex_count; 

        square(mathy::vec3<float> position, float size, mathy::colorRGBA color);

        void render_square() {
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, vertex_count);
        }

        void remove_data() {
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);

            std::cerr << "The object's data has been successfully removed" << std::endl;
        }
    };

    square::square(mathy::vec3<float> position, float size, mathy::colorRGBA color) {
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

                position.x + size/*6-x*/, position.y + -size/*7-y*/, position.z/*8-z*/,
                color.r/*9-r*/, color.g/*10-g*/, color.b/*11-b*/,

                position.x + -size/*12-x*/, position.y + size/*13-y*/, position.z/*14-z*/,
                color.r/*15-r*/, color.g/*16-g*/, color.b/*17-b*/,

                position.x + size/*18-x*/, position.y + size/*19-y*/, position.z/*20-z*/,
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