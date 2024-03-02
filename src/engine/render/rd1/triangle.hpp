#ifndef YUMEGL_TRIANGLE_HPP
#define YUMEGL_TRIANGLE_HPP

#include "../../../config.h"
#include "../../../yume.h"

namespace rd1 {
    // TRIANGLE
    class Triangle {
    public:
        // PROPERTIES
        glm::vec3 position{ 0.0f, 0.0f, 0.0f };
        colour color = colour::WHITE();

        float size{};
        bool enable{};

        // CONSTRUCTOR
        Triangle(glm::vec3 position_value, colour color_value, float size_value);

        // RENDER
        void render() const;

        // DECONSTRUCT
        ~Triangle();

    private:
        // VBO, VAO
        unsigned int VBO{}, VAO{};

        // DATA 
        std::vector<float> data;
    };

    Triangle::Triangle(glm::vec3 position_value, colour color_value, float size_value) {
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

    void Triangle::render() const {
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    Triangle::~Triangle() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);

        std::cerr << "Triangles data successfully deleted" << std::endl;
    }
}
#endif