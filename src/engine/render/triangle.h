#pragma once

#include "../../config.h"

namespace render {
    // TRIANGLE
    class Triangle {
    public:
        // PROPERTIES
        mathy::vec3<float> position = mathy::vec3<float>::ZERO();
        mathy::colorRGBA color = mathy::colorRGBA::WHITE();
        float size{};

        // CONSTRUCTOR
        Triangle(mathy::vec3<float> position_value, mathy::colorRGBA color_value, float size_value);

        // FUNCTIONS
        void renderTriangle() const;

        void deleteData();

    private:
        // MAIN DATA VECTOR
        std::vector<float> data;

        // VBO, VAO
        unsigned int VBO{}, VAO{};
    };

    Triangle::Triangle(mathy::vec3<float> position_value, mathy::colorRGBA color_value, float size_value) {
        // SET PROPERTIES
        position = position_value;
        color = color_value;
        size = size_value;

        // SET UP VERTEX DATA AND BUFFERS DATA
        data = {
                position.x + -size, position.y + -size, position.z,
                color.r, color.g, color.b,

                position.x + size, position.y + -size, position.z,
                color.r, color.g, color.b,

                position.x + size, position.y + size, position.z,
                color.r, color.g, color.b,
        };

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
    void Triangle::renderTriangle() const {
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    // DELETE
    void Triangle::deleteData() {
        std::cerr << "Triangles data successfully deleted" << std::endl;

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
}