#include "../../config.h"

namespace shader {
    unsigned int makeShaderModule(const std::string& filepath, unsigned int module_type);
    unsigned int makeFinalShader(const std::string& vertex_filepath, const std::string& fragment_filepath);

    // MAIN SHADER CLASS
    class Shader {
    public:
        Shader(const std::string& vertex_filepath, const std::string& fragment_filepath);

        [[nodiscard]] unsigned int getShader() const;
        void useShader() const;
        void deleteShader() const;

        ~Shader() = default;

    private:
        unsigned int id;
    };

    Shader::Shader(const std::string& vertex_filepath, const std::string& fragment_filepath) {
        id = shader::makeFinalShader(
                vertex_filepath,
                fragment_filepath
        );
    }

    unsigned int Shader::getShader() const {
        return id;
    }

    void Shader::useShader() const {
        glUseProgram(id);
    }

    void Shader::deleteShader() const {
        glDeleteShader(id);
    }

    unsigned int makeShaderModule(const std::string& filepath, unsigned int module_type) {
        std::ifstream file;
        std::stringstream bufferedLines;
        std::string line;

        file.open(filepath);
        while (std::getline(file, line)) {
            bufferedLines << line << '\n';
        }
        std::string shaderSource = bufferedLines.str();
        const char* shaderSrc = shaderSource.c_str();
        bufferedLines.str("");
        file.close();

        unsigned int shaderModule = glCreateShader(module_type);
        glShaderSource(shaderModule, 1, &shaderSrc, nullptr);
        glCompileShader(shaderModule);

        int success;
        glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success);
        if (!success) {
            char errorLog[1024];
            glGetShaderInfoLog(shaderModule, 1024, nullptr, errorLog);
            std::cerr << "Shader Module compilation error:\n" << errorLog << std::endl;
        }
        else {
            std::cout << "Shader Module compiled correctly\n";
        }

        return shaderModule;
    }

    unsigned int makeFinalShader(const std::string& vertex_filepath, const std::string& fragment_filepath) {
        //To store all the shader modules
        std::vector<unsigned int> modules;

        //Add a vertex shader module
        modules.push_back(makeShaderModule(vertex_filepath, GL_VERTEX_SHADER));

        //Add a fragment shader module
        modules.push_back(makeShaderModule(fragment_filepath, GL_FRAGMENT_SHADER));

        //Attach all the modules then link the program
        unsigned int shader = glCreateProgram();
        for (unsigned int shaderModule : modules) {
            glAttachShader(shader, shaderModule);
        }
        glLinkProgram(shader);

        //Check the linking worked
        int success;
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            char errorLog[1024];
            glGetProgramInfoLog(shader, 1024, nullptr, errorLog);
            std::cerr << "Shader linking error:\n" << errorLog << '\n';
        }
        else {
            std::cout << "Shader linked correctly\n";
        }

        //Modules are now unneeded and can be freed
        for (unsigned int shaderModule : modules) {
            glDeleteShader(shaderModule);
        }

        return shader; // RETURN FINAL SHADER
    }
}