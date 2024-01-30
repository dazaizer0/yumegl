#pragma once // IN DEVELOPMENT HERE IS A LOT OF MESSSSS

#include "../../config.h"

namespace render {
    // SQUARE
    class Square {
    public:
        // PROPERTIES
        mathy::vec3<float> position = mathy::vec3<float>::ZERO();
        mathy::colorRGBA color = mathy::colorRGBA::BLACK();
        float size{};

        // CONSTRUCTOR
        Square(mathy::vec3<float> position_valuE, mathy::colorRGBA color_value, float size_value);

        void render_square() const; /* {
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, vertex_count);
        }*/

        void remove_data(); /*{
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);

            std::cerr << "The object's data has been successfully removed" << std::endl;
        }*/

    private:
        // MAIN DATA VECTOR
        std::vector<float> data;

        // VBO, VAO
        unsigned int VBO{}, VAO{};
        int vertex_count;
    };

    Square::Square(mathy::vec3<float> position_value, mathy::colorRGBA color_value, float size_value) {
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
    }

    // RENDER
    void Square::render_square() const {
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, vertex_count);
    }

    // REMOVE
    void Square::remove_data() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);

        std::cerr << "The object's data has been successfully removed" << std::endl;
    }
}