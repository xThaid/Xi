#version 330 core
in vec4 iPos;
in vec3 iNormal;
in vec2 iTexCoord;

out vec3 vFragPos;
out vec3 vNormal;
out vec2 vTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vFragPos = vec3(model * iPos);
	vNormal = iNormal;
	vTexCoord = iTexCoord;

	gl_Position = projection * view * model * iPos;
}