#pragma once

#include <glad/glad.h>

#include <string>

class File;
	
enum ShaderType
{
	VERTEX,
	GEOMETRY,
	FRAGMENT
};

class Shader
{
public:
	Shader();
	Shader(const std::string& shaderSource);
	Shader(File file);
	~Shader();

	GLuint compileShader(ShaderType type);
	void clean();

private:
	bool enabled;
	GLuint shaderID;

	const char* shaderSource;
};			