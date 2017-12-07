#version 330 core
out vec4 FragColor;

in vec3 localPos;

void main()
{
	if(localPos.x > 0.0001)
		FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	else if(localPos.y > 0.0001)
		FragColor = vec4(0.0, 1.0, 0.0, 1.0);
	else if(localPos.z > 0.0001)
		FragColor = vec4(0.0, 0.0, 1.0, 1.0);
	else
		FragColor = vec4(0.0, 0.0, 0.0, 1.0);
}