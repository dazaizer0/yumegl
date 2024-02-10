#ifndef SQUARE_H
#define SQUARE_H

#include "../../config.h"

namespace render {
    // SQUARE
    class Square {
    public:
        // PROPERTIES
        glm::vec3 position = {0.0f, 0.0f, 0.0f};
        mathy::colorRGBA color = mathy::colorRGBA::BLACK();
        float size{};
        bool enable{};

        // CONSTRUCTOR
        Square(glm::vec3 position_value, mathy::colorRGBA color_value, float size_value);
        ~Square();

        // FUNCTIONS
        void updatePosition();
        void refresh() const;
        void render(unsigned int shader) const;

    private:
        // MAIN DATA VECTOR
        std::vector<float> data;

        // VBO, VAO
        unsigned int VBO{}, VAO{};
        int vertex_count;
    };

    Square::Square(glm::vec3 position_value, mathy::colorRGBA color_value, float size_value) {
        // SET PROPERTIES
        position = position_value;
        color = color_value;
        size = size_value;

        // SET UP VERTEX DATA AND BUFFERS DATA
        data = {
                // down-left
                position.x + -size, position.y + -size, position.z,
                color.r, color.g, color.b,

                // down-right
                position.x + size, position.y + -size, position.z,
                color.r, color.g, color.b,

                // top-left
                position.x + -size, position.y + size, position.z,
                color.r, color.g, color.b,

                // top-right
                position.x + size, position.y + size, position.z,
                color.r, color.g, color.b,
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

    // FUNCS
    void Square::updatePosition() { // TO OPTIMIZE
        data = {
                // down-left
                position.x + -size, position.y + -size, position.z,
                color.r, color.g, color.b,

                // down-right
                position.x + size, position.y + -size, position.z,
                color.r, color.g, color.b,

                // top-left
                position.x + -size, position.y + size, position.z,
                color.r, color.g, color.b,

                // top-right
                position.x + size, position.y + size, position.z,
                color.r, color.g, color.b,
        };

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        auto buffer_size = static_cast<GLsizeiptr>(data.size() * sizeof(float));
        glBufferData(GL_ARRAY_BUFFER, buffer_size, data.data(), GL_STATIC_DRAW);
    }

    void Square::refresh() const {
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
    }

    // RENDER
    void Square::render(unsigned int shader) const {
        glUseProgram(shader);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, vertex_count);
    }

    // DELETE
    Square::~Square() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);

        std::cerr << "squares data successfully deleted" << std::endl;
    }
}
#endif