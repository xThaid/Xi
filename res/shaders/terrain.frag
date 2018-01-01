#version 330 core
out vec4 FragColor;

in vec3 vFragPos;
in vec3 vNormal;

uniform vec3 fViewPos;

void main()
{
	if(!gl_FrontFacing)
		discard;
	FragColor = vec4(vNormal, 1.0);
}