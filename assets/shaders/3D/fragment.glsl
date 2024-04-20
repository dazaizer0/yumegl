#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D tex;

void main()
{
	// FragColor = texture(tex, TexCoord) * vec4(ourColor, 1.0);  
	FragColor = texture(tex, TexCoord);
}