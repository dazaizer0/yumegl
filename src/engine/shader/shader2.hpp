// FROM LEARN_OPENGL | during reconstruction
#ifndef SHADER2_HPP
#define SHADER2_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <src/engine/source/yume_kernel.hpp>

namespace shaderSystem {
    class Shader {
    public:
        GLuint ID{};

        Shader() = default;

        // FUNCTIONS
        void genShader(const std::string& vertexPath, const std::string& fragmentPath) {
            //if convertion needed in the future, we can remove "const" and "&" from
            //the arguments and modify them here

            if (std::fstream::good(vertexPath)) {
                std::cerr << "ERROR:PATH:VERTEX:SHADER" << std::endl;
            }
            else {
                std::cout << "vertex shader loaded correctly\n";
            }

            if (std::fstream::good(fragmentPath)) {
                std::cerr << "ERROR:PATH:FRAGMENT:SHADER" << std::endl;
            }
            else {
                std::cout << "fragment shader loaded correctly\n";
            }

            const char* vertexShaderSource, fragmentShaderSource;
            std::ifstream vShaderFile;
            std::ifstream fShaderFile;

            vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

            try {
                // open files
                vShaderFile.open(vertexPath);
                fShaderFile.open(fragmentPath);
                std::stringstream vShaderStream, fShaderStream;

                // read file's buffer contents into streams
                vShaderStream << vShaderFile.rdbuf();
                fShaderStream << fShaderFile.rdbuf();

                // close file handlers
                vShaderFile.close();
                fShaderFile.close();

                // convert stream into c_string
                vertexShaderSource = vShaderStream.str().c_str();
                fragmentShaderSource = fShaderStream.str().c_str();
            }
            catch (std::ifstream::failure& e) {
                std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
            }

            GLuint vertexShader, fragmentShader;

            // VERTEX
            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
            glCompileShader(vertexShader);

            checkCompileErrors(vertexShader, "VERTEX");

            // FRAGMENT
            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
            glCompileShader(fragmentShader);

            checkCompileErrors(fragmentShader, "FRAGMENT");

            // SHADER
            ID = glCreateProgram();
            glAttachShader(ID, vertexShader);
            glAttachShader(ID, fragmentShader);
            glLinkProgram(ID);

            checkCompileErrors(ID, "PROGRAM");

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
        }

        void use() const {
            glUseProgram(ID);
        }

        void setBool(const std::string& name, bool value) const {
            glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
        }

        void setInt(const std::string& name, int value) const {
            glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
        }

        void setFloat(const std::string& name, float value) const {
            glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
        }

        void setVec2(const std::string& name, const glm::vec2& value) const {
            glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
        }
        void setVec2(const std::string& name, float x, float y) const {
            glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
        }

        void setVec3(const std::string& name, const glm::vec3& value) const {
            glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
        }
        void setVec3(const std::string& name, float x, float y, float z) const {
            glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
        }

        void setVec4(const std::string& name, const glm::vec4& value) const {
            glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
        }
        void setVec4(const std::string& name, float x, float y, float z, float w) const {
            glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
        }

        void setMat2(const std::string& name, const glm::mat2& mat) const {
            glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }

        void setMat3(const std::string& name, const glm::mat3& mat) const {
            glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }

        void setMat4(const std::string& name, const glm::mat4& mat) const {
            glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }

        ~Shader() {
            glDeleteShader(ID);
        }

    private:
        static void checkCompileErrors(GLuint shader, const std::string& type) {
            GLint success;
            GLchar infoLog[1024];
            if (type != "PROGRAM") {
                glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                if (!success) {
                    glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
                    std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << std::endl
                              << infoLog << std::endl << " -- --------------------------------------------------- -- " << std::endl;
                }
            }
            else {
                glGetProgramiv(shader, GL_LINK_STATUS, &success);
                if (!success) {
                    glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
                    std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << std::endl
                              << infoLog << std::endl << " -- --------------------------------------------------- -- " << std::endl;
                }
            }
        }
    };

    void deleteShader(const Shader& shader) {
        glDeleteShader(shader.ID);
    }
}
#endif