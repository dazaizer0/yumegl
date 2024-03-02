#ifndef YUMEGL_SQUARE_HPP
#define YUMEGL_SQUARE_HPP

#include "../../../config.h"
#include "../../../yume.h"

namespace rd1 {
    // SQUARE
    class Square {
    public:
        // PROPERTIES
        glm::vec3 position{ 0.0f, 0.0f, 0.0f };
        glm::vec2 size{ 1.0f, 1.0f };
        colour color = colour::BLACK();
        shaderSystem::GlProgram shader;

        bool enable{};

        // CONSTRUCTOR
        Square(glm::vec3 position_value, colour color_value, glm::vec2 size_value);

        //UPDATE
        void updatePosition();
        void refresh() const;

        // RENDER
        void render_ownShader() const;
        void render_getShader(const shaderSystem::GlProgram& other_shader) const;
        void render_foregoingShader() const;

        // DECONSTRUCTOR
        ~Square();

    private:
        // VBO, VAO
        unsigned int VBO{}, VAO{};
        int vertex_count;

        // DATA
        std::vector<float> data;
    };

    Square::Square(glm::vec3 position_value, colour color_value, glm::vec2 size_value) {
        // SET PROPERTIES
        position = position_value;
        color = color_value;
        size = size_value;

        // SET UP VERTEX DATA AND BUFFERS DATA
        data = {
                // down-left
                position.x + -size.x, position.y + -size.y, position.z,
                color.r, color.g, color.b,

                // down-right
                position.x + size.x, position.y + -size.y, position.z,
                color.r, color.g, color.b,

                // top-left
                position.x + -size.x, position.y + size.y, position.z,
                color.r, color.g, color.b,

                // top-right
                position.x + size.x, position.y + size.y, position.z,
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
            position.x + -size.x, position.y + -size.y, position.z,
            color.r, color.g, color.b,

            // down-right
            position.x + size.x, position.y + -size.y, position.z,
            color.r, color.g, color.b,

            // top-left
            position.x + -size.x, position.y + size.y, position.z,
            color.r, color.g, color.b,

            // top-right
            position.x + size.x, position.y + size.y, position.z,
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
    void Square::render_ownShader() const {
        shader.use();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, vertex_count);
    }

    void Square::render_getShader(const shaderSystem::GlProgram& other_shader) const {
        other_shader.use();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, vertex_count);
    }

    void Square::render_foregoingShader() const {
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, vertex_count);
    }

    // DELETE
    Square::~Square() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);

        shader.~GlProgram();

        std::cerr << "squares data successfully deleted" << std::endl;
    }
}
#endif