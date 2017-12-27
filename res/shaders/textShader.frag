#version 330 core
out vec4 FragColor;

in vec2 vTexCoord;

uniform sampler2D glyphTexture;
uniform vec3 textColor;

void main()
{
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(glyphTexture, vTexCoord).r);
	FragColor = vec4(textColor, 1.0) * sampled;
}