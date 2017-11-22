#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor = vec4(TexCoord.x, TexCoord.y, 1.0 - (TexCoord.x + TexCoord.y) / 2.0f, 1.0f);
}