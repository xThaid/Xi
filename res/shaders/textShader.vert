#version 330 core
in vec4 iPos;
in vec2 iTexCoord;

out vec2 vTexCoord;

uniform mat4 model;
uniform mat4 projection;

void main()
{
	vTexCoord = iTexCoord;
	gl_Position = projection * model * iPos;
}