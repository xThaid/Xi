#version 330 core

out vec4 color;

in VS_OUT
{
	vec3 normal;
	vec3 fragPos;
	vec2 texCoords;
	vec3 color;
} fs_in;

void main()
{
	color = fs.in.color;
}