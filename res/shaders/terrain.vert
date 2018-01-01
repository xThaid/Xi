#version 330 core
in vec4 iPos;
in vec3 iNormal;

out vec3 vFragPos;
out vec3 vNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vFragPos = vec3(model * iPos);
	vNormal = iNormal;
	gl_Position = projection * view * model * iPos;
}