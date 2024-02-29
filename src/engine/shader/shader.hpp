// FROM LEARN_OPENGL | during reconstruction
#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <src/engine/source/yume_kernel.hpp>

namespace shaderSystem {

    struct Shader {
    private:
        const char* vName = "VERTEX";
        const char* fName = "FRAGMENT";
        GLuint id;
        GLubyte stype;

        const char* sType() {
            return stype ? fName : vName;
        }
    public:
        Shader(GLenum sType) {
            switch (sType) {
            case GL_VERTEX_SHADER:
                id = glCreateShader(GL_VERTEX_SHADER);
                stype = 0;
            case GL_FRAGMENT_SHADER:
                id = glCreateShader(GL_FRAGMENT_SHADER);
                stype = 1;
            }
        }

        GLuint getId() const {
            return id;
        }

        void loadShaderPath(const std::string& path) {

            if (!std::filesystem::exists(path)) {
                std::cerr << "ERROR: BAD SHADER PATH : " << path << std::endl;
            }
            /*else {
                std::cout << "shader path correct" << std::endl;
            }*/
            // works => no info needed, delete if you want

            std::ifstream file;
            std::stringstream stream;
            std::string string;

            file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

            try {
                // open file
                file.open(path);

                // read file's buffer contents into streams
                stream << file.rdbuf();

                // close file handler
                file.close();
            }
            catch (std::ifstream::failure& e) {
                std::cout << "ERROR: SHADER FILE READ FAILURE : " << e.what() << std::endl;
            }

            string = stream.str();
            loadShaderSource(string.c_str());
        }

        void loadShaderSource(const GLchar* shaderSource) {
            glShaderSource(id, 1, &shaderSource, nullptr);
            glCompileShader(id);
            checkCompileErrors();
        }

        ~Shader() {
            glDeleteShader(id);
        }

    private:
        void checkCompileErrors() {
            GLint success;
            GLchar infoLog[1024];

            glGetShaderiv(id, GL_COMPILE_STATUS, &success);

            if (!success) {
                glGetShaderInfoLog(id, 1024, nullptr, infoLog);
                std::cout << "ERROR: SHADER COMPILATION ERROR ; TYPE: " << sType() << std::endl
                    << infoLog << std::endl << " -- --------------------------------------------------- -- " << std::endl;
            }
        }
    };


    Shader* generateShader(GLenum sType, const std::string& path) {
        Shader *shade = new Shader(sType);
        shade->loadShaderPath(path);
        return shade;
    }



    struct GlProgram {
    private:
        GLuint id;
        //can't be public or someone's gonna overwrite it without calling glDeleteProgram and that's a memory leak 

        Shader* vertexShader;
        Shader* fragmentShader;
    public:


        GlProgram() : id(glCreateProgram()) {};

        // FUNCTIONS

        void makeProgramFromPaths(const std::string& vertexPath, const std::string& fragmentPath) {

            vertexShader = generateShader(GL_VERTEX_SHADER, vertexPath);
            fragmentShader = generateShader(GL_FRAGMENT_SHADER, fragmentPath);

            linkProgram();
        }

        void linkProgram() {
            glAttachShader(id, vertexShader->getId());
            glAttachShader(id, fragmentShader->getId());
            glLinkProgram(id);

            checkLinkingErrors();
        }

        GLint getId() const {
            return id;
        }

        void use() const {
            glUseProgram(id);
        }

        void setBool(const std::string& name, bool value) const {
            glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
        }

        void setInt(const std::string& name, int value) const {
            glUniform1i(glGetUniformLocation(id, name.c_str()), value);
        }

        void setFloat(const std::string& name, float value) const {
            glUniform1f(glGetUniformLocation(id, name.c_str()), value);
        }

        void setVec2(const std::string& name, const glm::vec2& value) const {
            glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
        }
        void setVec2(const std::string& name, float x, float y) const {
            glUniform2f(glGetUniformLocation(id, name.c_str()), x, y);
        }

        void setVec3(const std::string& name, const glm::vec3& value) const {
            glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
        }
        void setVec3(const std::string& name, float x, float y, float z) const {
            glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
        }

        void setVec4(const std::string& name, const glm::vec4& value) const {
            glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
        }
        void setVec4(const std::string& name, float x, float y, float z, float w) const {
            glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w);
        }

        void setMat2(const std::string& name, const glm::mat2& mat) const {
            glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }

        void setMat3(const std::string& name, const glm::mat3& mat) const {
            glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }

        void setMat4(const std::string& name, const glm::mat4& mat) const {
            glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }

        ~GlProgram() {
            glDeleteProgram(id);
            delete vertexShader;
            delete fragmentShader;
        }

        void checkLinkingErrors() {
            GLint success;
            GLchar infoLog[1024];

            glGetProgramiv(id, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(id, 1024, nullptr, infoLog);
                std::cout << "ERROR: PROGRAM LINKING ERROR " << std::endl
                    << infoLog << success << std::endl << " -- --------------------------------------------------- -- " << std::endl;
            }
        }
    };

    

};
#endif