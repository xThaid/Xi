#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normalVector;
layout (location = 2) in vec2 textureCoords;

out VS_OUT
{
	vec3 normal;
	vec3 fragPos;
	vec2 texCoords;
	vec3 color;
} vs_out;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform mat4 mainColor;

void main()
{
    gl_Position = projection * view *  model * vec4(position, 1.0f);

    vs_out.fragPos = vec3(model * vec4(position, 1.0f));
    vs_out.normal = mat3(transpose(inverse(model))) * normal;  
    vs_out.texCoords = texCoords;
	vs_out.color = mainColor;
} 