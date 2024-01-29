#pragma once

#include "../../config.h"
#include "stb/stb_image.h"

class material {
public:
    material();

    void use();

    ~material();

private:
    unsigned int texture;
};

material::material() {

    const char* filename = "..\\assets\\sonic.png";
    int width, height, channels;
    unsigned char* data = stbi_load(filename, &width, &height, &channels, STBI_rgb_alpha);

    //make the texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    //load data
    glTexImage2D(GL_TEXTURE_2D,
                 0, GL_RGBA, width, height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, data);

    //free data
    stbi_image_free(data);

    //Configure sampler
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void material::use() {
    glBindTexture(GL_TEXTURE_2D, texture);
}

material::~material() {
    glDeleteTextures(1, &texture);
}