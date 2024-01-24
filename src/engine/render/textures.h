#include "../../config.h"
#include "stb/stb_image.h"

namespace mts {
    class texture {
    public:
        unsigned int _texture;

        texture(const char* file_name);
        void use();
        void del();
    };

    texture::texture(const char *file_name) {
        // initialize
        int width, heigh, channels;
        unsigned char* data = stbi_load(file_name, &width, &heigh, &channels, STBI_rgb_alpha);

        // TODO: Create, load and upload material
        // glGenTextures(1, &texture); -> glCreateTextures -> od 4.5
        // glBindTexture(GL_TEXTURE_2D, texture);

        // upload
        // TODO: glTexImage2D()
    }

    void texture::use() {
        glBindTexture(GL_TEXTURE_2D, _texture);
    }

    void texture::del() {
        glDeleteTextures(1, &_texture);
    }
}