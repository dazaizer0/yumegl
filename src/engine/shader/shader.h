#include "../../config.h"

namespace shader {
    // MAIN SHADER CLASS
    class Shader
    {
    public:
        Shader();
        ~Shader();

    private:

    };

    Shader::Shader()
    = default; /*{}*/

    Shader::~Shader()
    = default; /*{}*/

    // SHADER LOADER NR.1
    unsigned int load_static_shaders() {
        unsigned int shader {};

        // VERTEX SHADER
#define VERTEX_FILE_PATH "shader_scripts/vertex.vs"
        const char *vertex_source =
#include VERTEX_FILE_PATH
        ;

        unsigned int vertex_shader;
        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &vertex_source, nullptr);
        glCompileShader(vertex_shader);

        int  success;
        char infoLog[512];
        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(vertex_shader, 512, nullptr, infoLog);
            std::cerr << ">> ERROR::SHADER::VERTEX::COMPILATION_FAILED >> " << infoLog << std::endl;
        }
        else {
            std::cout << "- vertex shader loaded correctly.\n";
        }

        // FRAGMENT SHADER
#define FRAGMENT_FILE_PATH "shader_scripts/fragment.vs"
        const char *fragment_source =
#include FRAGMENT_FILE_PATH
        ;

        unsigned int fragment_shader;
        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &fragment_source, nullptr);
        glCompileShader(fragment_shader);

        // COMPLETE SHADER
        shader = glCreateProgram();

        glAttachShader(shader, vertex_shader);
        glAttachShader(shader, fragment_shader);
        glLinkProgram(shader);

        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(shader, 512, nullptr, infoLog);
            std::cerr << ">> ERROR::SHADER::FRAGMENT::COMPILATION_FAILED >> " << infoLog << std::endl;
        }
        else {
            std::cout << "- fragment shader loaded correctly.\n";
        }

        return shader;
    }

    // SHADER LOADER NR.2
    unsigned int make_shader_module(const std::string& filepath, unsigned int module_type) {

        std::ifstream file;
        std::stringstream bufferedLines;
        std::string line;

        file.open(filepath);
        while (std::getline(file, line)) {
            //std::cout << line << std::endl;
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
            std::cout << "Shader Module compilation error:\n" << errorLog << std::endl;
        }

        return shaderModule;
    }

    unsigned int make_shader(const std::string& vertex_filepath, const std::string& fragment_filepath) {

        //To store all the shader modules
        std::vector<unsigned int> modules;

        //Add a vertex shader module
        modules.push_back(make_shader_module(vertex_filepath, GL_VERTEX_SHADER));

        //Add a fragment shader module
        modules.push_back(make_shader_module(fragment_filepath, GL_FRAGMENT_SHADER));

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
            std::cout << "Shader linking error:\n" << errorLog << '\n';
        }

        //Modules are now unneeded and can be freed
        for (unsigned int shaderModule : modules) {
            glDeleteShader(shaderModule);
        }

        return shader;
    }
}