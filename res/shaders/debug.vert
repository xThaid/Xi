#version 330 core
in vec4 iPos;
in vec4 iColor;

out vec4 vColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vColor = iColor;
	gl_Position = projection * view * model * iPos;
}