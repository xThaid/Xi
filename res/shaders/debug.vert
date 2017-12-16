#version 330 core
in vec3 iPos;
in vec3 iColor;

out vec3 vColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vColor = iColor;
	gl_Position = projection * view * model * vec4(iPos, 1.0);
}