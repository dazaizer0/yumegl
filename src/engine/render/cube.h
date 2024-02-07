#ifndef YUMEGL_CUBE_H
#define YUMEGL_CUBE_H

#include "../../config.h"
#include "../../yume.h"

namespace render {
	class Cube { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>> IN DEVELOPMENT <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    public:
        mathy::vec3<float> position = mathy::vec3<float>::ZERO();
        mathy::vec3<float> size = mathy::vec3<float>::ZERO();
        //float size{};

        Cube(std::string path, mathy::vec3<float> position_value, mathy::vec3<float> size_value);
        void updatePosition();
        void refresh();
        void render(Shader shader);
        void rotate(mathy::vec3<float> axis, Shader shader, float rotationSpeed);
        void setRotation(mathy::vec3<float> axis, Shader shader, float angle);
        void setWindowSize(const unsigned int window_w, const unsigned int window_h);
        void deleteData();

    private:
        unsigned int VBO{}, VAO{};

        unsigned int tex{};
        const char* texPath;
        unsigned char* texData;

        unsigned int window_width{};
        unsigned int window_height{};

        std::vector<float> vertices;
	};

	Cube::Cube(std::string path, mathy::vec3<float> position_value, mathy::vec3<float> size_value) {
        // SET PROPERTIES
        std::string path2 = yumegl::eFunc::yumePath() + "/assets/" + path;
        texPath = path2.c_str();

        if (texPath == nullptr) {
            std::cerr << "ERROR:LOADING:TEXTURE" << std::endl;
        }
        else {
            std::cout << "texture loaded correctly\n";
        }

        size = size_value;
        position = position_value;

        // CUBE
        /*
         * vertices = {
                position.x + -size.x, position.y + -size.y, position.z + -size.z,  0.0f, 0.0f,
                position.x + size.x, position.y + -size.y, position.z + -size.z,  1.0f, 0.0f,
                position.x + size.x, position.y + size.y, position.z + -size.z,  1.0f, 1.0f,
                position.x + size.x, position.y + size.y, position.z + -size.z,  1.0f, 1.0f,
                position.x + -size.x, position.y + size.y, position.z + -size.z,  0.0f, 1.0f,
                position.x + -size.x, position.y + -size.y, position.z + -size.z,  0.0f, 0.0f,

                position.x + -size.x, position.y + -size.y, position.z + size.z,  0.0f, 0.0f,
                position.x + size.x, position.y + -size.y, position.z + size.z,  1.0f, 0.0f,
                position.x + size.x, position.y + size.y, position.z + size.z,  1.0f, 1.0f,
                position.x + size.x, position.y + size.y, position.z + size.z,  1.0f, 1.0f,
                position.x + -size.x, position.y + size.y, position.z + size.z,  0.0f, 1.0f,
                position.x + -size.x, position.y + -size.y, position.z + size.z,  0.0f, 0.0f,

                position.x + -size.x, position.y + size.y, position.z + size.z,  1.0f, 0.0f,
                position.x + -size.x, position.y + size.y, position.z + -size.z,  1.0f, 1.0f,
                position.x + -size.x, position.y + -size.y, position.z + -size.z,  0.0f, 1.0f,
                position.x + -size.x, position.y + -size.y, position.z + -size.z,  0.0f, 1.0f,
                position.x + -size.x, position.y + -size.y, position.z + size.z,  0.0f, 0.0f,
                position.x + -size.x, position.y + size.y, position.z + size.z,  1.0f, 0.0f,

                position.x + size.x, position.y + size.y, position.z + size.z,  1.0f, 0.0f,
                position.x + size.x, position.y + size.y, position.z + -size.z,  1.0f, 1.0f,
                position.x + size.x, position.y + -size.y, position.z + -size.z,  0.0f, 1.0f,
                position.x + size.x, position.y + -size.y, position.z + -size.z,  0.0f, 1.0f,
                position.x + size.x, position.y + -size.y, position.z + size.z,  0.0f, 0.0f,
                position.x + size.x, position.y + size.y, position.z + size.z,  1.0f, 0.0f,

                position.x + -size.x, position.y + -size.y, position.z + -size.z,  0.0f, 1.0f,
                position.x + size.x, position.y + -size.y, position.z + -size.z,  1.0f, 1.0f,
                position.x + size.x, position.y + -size.y, position.z + size.z,  1.0f, 0.0f,
                position.x + size.x, position.y + -size.y, position.z + size.z,  1.0f, 0.0f,
                position.x + -size.x, position.y + -size.y, position.z + size.z,  0.0f, 0.0f,
                position.x + -size.x, position.y + -size.y, position.z + -size.z,  0.0f, 1.0f,

                position.x + -size.x, position.y + size.y, position.z + -size.z,  0.0f, 1.0f,
                position.x + size.x, position.y + size.y, position.z + -size.z,  1.0f, 1.0f,
                position.x + size.x, position.y + size.y, position.z + size.z,  1.0f, 0.0f,
                position.x + size.x, position.y + size.y, position.z + size.z,  1.0f, 0.0f,
                position.x + -size.x, position.y + size.y, position.z + size.z,  0.0f, 0.0f,
                position.x + -size.x, position.y + size.y, position.z + -size.z,  0.0f, 1.0f
        };*/

        vertices = {
                position.x + -size.x, position.y + -size.y, position.z + -size.z, 0.0f, 0.0f,
                position.x + size.x, position.y + -size.y, position.z + -size.z, 1.0f, 0.0f,
                position.x + size.x, position.y + size.y, position.z + -size.z, 1.0f, 1.0f,
                position.x + size.x, position.y + size.y, position.z + -size.z, 1.0f, 1.0f,
                position.x + -size.x, position.y + size.y, position.z + -size.z, 0.0f, 1.0f,
                position.x + -size.x, position.y + -size.y, position.z + -size.z, 0.0f, 0.0f,

                position.x + -size.x, position.y + -size.y, position.z + size.z, 0.0f, 0.0f,
                position.x + size.x, position.y + -size.y, position.z + size.z, 1.0f, 0.0f,
                position.x + size.x, position.y + size.y, position.z + size.z, 1.0f, 1.0f,
                position.x + size.x, position.y + size.y, position.z + size.z, 1.0f, 1.0f,
                position.x + -size.x, position.y + size.y, position.z + size.z, 0.0f, 1.0f,
                position.x + -size.x, position.y + -size.y, position.z + size.z, 0.0f, 0.0f,

                position.x + -size.x, position.y + size.y, position.z + size.z, 1.0f, 0.0f,
                position.x + -size.x, position.y + size.y, position.z + -size.z, 1.0f, 1.0f,
                position.x + -size.x, position.y + -size.y, position.z + -size.z, 0.0f, 1.0f,
                position.x + -size.x, position.y + -size.y, position.z + -size.z, 0.0f, 1.0f,
                position.x + -size.x, position.y + -size.y, position.z + size.z, 0.0f, 0.0f,
                position.x + -size.x, position.y + size.y, position.z + size.z, 1.0f, 0.0f,

                position.x + size.x, position.y + size.y, position.z + size.z, 1.0f, 0.0f,
                position.x + size.x, position.y + size.y, position.z + -size.z, 1.0f, 1.0f,
                position.x + size.x, position.y + -size.y, position.z + -size.z, 0.0f, 1.0f,
                position.x + size.x, position.y + -size.y, position.z + -size.z, 0.0f, 1.0f,
                position.x + size.x, position.y + -size.y, position.z + size.z, 0.0f, 0.0f,
                position.x + size.x, position.y + size.y, position.z + size.z, 1.0f, 0.0f,

                position.x + -size.x, position.y + -size.y, position.z + -size.z, 0.0f, 1.0f,
                position.x + size.x, position.y + -size.y, position.z + -size.z, 1.0f, 1.0f,
                position.x + size.x, position.y + -size.y, position.z + size.z, 1.0f, 0.0f,
                position.x + size.x, position.y + -size.y, position.z + size.z, 1.0f, 0.0f,
                position.x + -size.x, position.y + -size.y, position.z + size.z, 0.0f, 0.0f,
                position.x + -size.x, position.y + -size.y, position.z + -size.z, 0.0f, 1.0f,

                position.x + -size.x, position.y + size.y, position.z + -size.z, 0.0f, 1.0f,
                position.x + size.x, position.y + size.y, position.z + -size.z, 1.0f, 1.0f,
                position.x + size.x, position.y + size.y, position.z + size.z, 1.0f, 0.0f,
                position.x + size.x, position.y + size.y, position.z + size.z, 1.0f, 0.0f,
                position.x + -size.x, position.y + size.y, position.z + size.z, 0.0f, 0.0f,
                position.x + -size.x, position.y + size.y, position.z + -size.z, 0.0f, 1.0f
        };

        // CREATE CUBE
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // TEXTURE
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width, height, nrChannels;
        texData = stbi_load(texPath, &width, &height, &nrChannels, 0);

        if (texData) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        stbi_image_free(texData);
    }

    void Cube::render(Shader shader) {
        // ACTIVATE SHADER
        glUseProgram(shader.ID);

        // BIND TEXTURE
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex);

        // RENDER TEXTURE
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    void Cube::updatePosition() {
        vertices = {
                position.x + -size.x, position.y + -size.y, position.z + -size.z, 0.0f, 0.0f,
                position.x + size.x, position.y + -size.y, position.z + -size.z, 1.0f, 0.0f,
                position.x + size.x, position.y + size.y, position.z + -size.z, 1.0f, 1.0f,
                position.x + size.x, position.y + size.y, position.z + -size.z, 1.0f, 1.0f,
                position.x + -size.x, position.y + size.y, position.z + -size.z, 0.0f, 1.0f,
                position.x + -size.x, position.y + -size.y, position.z + -size.z, 0.0f, 0.0f,

                position.x + -size.x, position.y + -size.y, position.z + size.z, 0.0f, 0.0f,
                position.x + size.x, position.y + -size.y, position.z + size.z, 1.0f, 0.0f,
                position.x + size.x, position.y + size.y, position.z + size.z, 1.0f, 1.0f,
                position.x + size.x, position.y + size.y, position.z + size.z, 1.0f, 1.0f,
                position.x + -size.x, position.y + size.y, position.z + size.z, 0.0f, 1.0f,
                position.x + -size.x, position.y + -size.y, position.z + size.z, 0.0f, 0.0f,

                position.x + -size.x, position.y + size.y, position.z + size.z, 1.0f, 0.0f,
                position.x + -size.x, position.y + size.y, position.z + -size.z, 1.0f, 1.0f,
                position.x + -size.x, position.y + -size.y, position.z + -size.z, 0.0f, 1.0f,
                position.x + -size.x, position.y + -size.y, position.z + -size.z, 0.0f, 1.0f,
                position.x + -size.x, position.y + -size.y, position.z + size.z, 0.0f, 0.0f,
                position.x + -size.x, position.y + size.y, position.z + size.z, 1.0f, 0.0f,

                position.x + size.x, position.y + size.y, position.z + size.z, 1.0f, 0.0f,
                position.x + size.x, position.y + size.y, position.z + -size.z, 1.0f, 1.0f,
                position.x + size.x, position.y + -size.y, position.z + -size.z, 0.0f, 1.0f,
                position.x + size.x, position.y + -size.y, position.z + -size.z, 0.0f, 1.0f,
                position.x + size.x, position.y + -size.y, position.z + size.z, 0.0f, 0.0f,
                position.x + size.x, position.y + size.y, position.z + size.z, 1.0f, 0.0f,

                position.x + -size.x, position.y + -size.y, position.z + -size.z, 0.0f, 1.0f,
                position.x + size.x, position.y + -size.y, position.z + -size.z, 1.0f, 1.0f,
                position.x + size.x, position.y + -size.y, position.z + size.z, 1.0f, 0.0f,
                position.x + size.x, position.y + -size.y, position.z + size.z, 1.0f, 0.0f,
                position.x + -size.x, position.y + -size.y, position.z + size.z, 0.0f, 0.0f,
                position.x + -size.x, position.y + -size.y, position.z + -size.z, 0.0f, 1.0f,

                position.x + -size.x, position.y + size.y, position.z + -size.z, 0.0f, 1.0f,
                position.x + size.x, position.y + size.y, position.z + -size.z, 1.0f, 1.0f,
                position.x + size.x, position.y + size.y, position.z + size.z, 1.0f, 0.0f,
                position.x + size.x, position.y + size.y, position.z + size.z, 1.0f, 0.0f,
                position.x + -size.x, position.y + size.y, position.z + size.z, 0.0f, 0.0f,
                position.x + -size.x, position.y + size.y, position.z + -size.z, 0.0f, 1.0f
        };

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    }

    void Cube::refresh() {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
    }

    void Cube::rotate(mathy::vec3<float> axis, Shader shader, float rotationSpeed) {
        // ROTATE
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        glm::vec3 rotationAxis = mathy::func::convertVec3(axis);


        model = glm::translate(model, glm::vec3(position.x, position.y, position.z));

        model = glm::rotate(model, (float)glfwGetTime() * rotationSpeed, rotationAxis);

        model = glm::translate(model, -glm::vec3(position.x, position.y, position.z));

        view = glm::translate(view, glm::vec3(position.x, position.y, position.z));
        projection = glm::perspective(glm::radians(45.0f), (float)window_width / (float)window_height, 0.1f, 100.0f);

        unsigned int modelLoc = glGetUniformLocation(shader.ID, "model");
        unsigned int viewLoc = glGetUniformLocation(shader.ID, "view");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

        shader.setMat4("projection", projection);
    }

    void Cube::setRotation(mathy::vec3<float> axis, Shader shader, float angle) {
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        glm::vec3 rotationAxis = mathy::func::convertVec3(axis);

        projection = glm::perspective(glm::radians(45.0f), (float)window_width / (float)window_height, 0.1f, 100.0f);
        view = glm::translate(view, glm::vec3(position.x, position.y, position.z));

        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(angle), rotationAxis);
        shader.setMat4("model", model);
    }

    void Cube::setWindowSize(const unsigned int window_w, const unsigned int window_h) {
        window_width = window_w;
        window_height = window_h;
    }

    void Cube::deleteData() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
}
#endif //YUMEGL_CUBE_H
