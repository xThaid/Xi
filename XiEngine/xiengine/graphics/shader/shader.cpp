#include "shader.h"

#include "..\..\utils\file.h"

#include <iostream>

namespace TDEngine
{
	Shader::Shader(const std::string& shaderSource)
	{
		this->shaderSource = shaderSource.c_str();
	}

	Shader::Shader(File file)
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
		else if (type == ShaderType::FRAGMENT) shaderID = glCreateShader(GL_FRAGMENT_SHADER);
		else return 0;

		GLint success;
		GLchar infoLog[512];

		glShaderSource(shaderID, 1, &shaderSource, NULL);
		glCompileShader(shaderID);
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
			std::cout << "SHADER COMPILATION FAILED\n" << infoLog << std::endl;//TODO error
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
}