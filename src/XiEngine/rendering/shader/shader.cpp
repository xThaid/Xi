#include "shader.h"

#include "../../utils/file.h"

#include "../../utils/logger.h"

Shader::Shader() : enabled(false), shaderID(0)
{

}

Shader::Shader(const std::string& shaderSource) : enabled(true), shaderID(0)
{
	this->shaderSource = shaderSource.c_str();
}

Shader::Shader(File file) : enabled(true), shaderID(0)
{
	File::loadFromFile(file.getPath(), shaderSource);
}

Shader::~Shader()
{
	clean();
}

GLuint Shader::compileShader(ShaderType type)
{
	if (type == ShaderType::VERTEX) shaderID = glCreateShader(GL_VERTEX_SHADER);
	else if (type == ShaderType::GEOMETRY) shaderID = glCreateShader(GL_GEOMETRY_SHADER);
	else if (type == ShaderType::FRAGMENT) shaderID = glCreateShader(GL_FRAGMENT_SHADER);
	else return 0;

	if (!enabled)
		return 0;

	GLint success;
	GLchar infoLog[512];

	glShaderSource(shaderID, 1, &shaderSource, NULL);
	glCompileShader(shaderID);
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		Logger::warn("Shader compilation failed: \n" + std::string(infoLog));
	}

	return shaderID;
}

void Shader::clean()
{
	if (shaderID != 0)
	{
		glDeleteShader(shaderID);
		shaderID = 0;
	}
}