#version 330 core
layout (location = 0) in vec3 pos;

out vec3 localPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	localPos = vec3(model * vec4(pos, 1.0));

	gl_Position = projection * view * model * vec4(pos, 1.0);
}