#version 330 core
layout (location = 0) in vec3 iPos;
layout (location = 1) in vec2 iTexCoords;
layout (location = 2) in vec3 iNormal;

out vec3 FragPos;
out vec2 TexCoords;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	FragPos = vec3(model * vec4(iPos, 1.0));
	Normal = mat3(transpose(inverse(model))) * iNormal;
	TexCoords = vec2(iTexCoords.x, iTexCoords.y);

	gl_Position = projection * view * vec4(FragPos, 1.0);
}