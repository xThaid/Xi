#version 330 core
out vec4 FragColor;

in vec3 vFragPos;
in vec3 vNormal;
in vec2 vTexCoord;

uniform vec3 fViewPos;
uniform bool fDrawBorders;
uniform vec3 fColor;

void main()
{
	if(!gl_FrontFacing)
		discard;

	vec3 color = vec3(0.0, 1.0, 0.0);

	if(fDrawBorders)
	{
		float borderSize = 0.03;

		if(vTexCoord.x < borderSize || vTexCoord.x > (1.0 - borderSize) || vTexCoord.y < borderSize || vTexCoord.y > (1.0 - borderSize))
			color = fColor;
	}

	FragColor = vec4(color, 1.0);
}