#version 330 core

in vec3 fragmentColor;

out vec4 screenColor;

void main()
{
    screenColor = vec4(fragmentColor, 1.0);
}

/* WITH TEXTURES
#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord);
}
*/