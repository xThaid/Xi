#include "shaderProgram.h"

#include <iostream>
#include "tdmaths\test.h"

namespace TDEngine
{
	ShaderProgram::ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader) :
		vertexShader(vertexShader), fragmentShader(fragmentShader)
	{
		shaderProgramID = 0;
	}

	ShaderProgram::~ShaderProgram()
	{
		destroyShaderProgram();
		tdmaths::doThat();
	}

	void ShaderProgram::initShaderProgram()
	{
		GLuint vertexShaderID = vertexShader.compileShader(ShaderType::VERTEX);
		GLuint fragmentShaderID = fragmentShader.compileShader(ShaderType::FRAGMENT);

		GLint success;
		GLchar infoLog[512];

		shaderProgramID = glCreateProgram();
		glAttachShader(shaderProgramID, vertexShaderID);
		glAttachShader(shaderProgramID, fragmentShaderID);
		glLinkProgram(shaderProgramID);
		glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
			std::cout << "SHADER PROGRAM LINKING FAILED\n" << infoLog << std::endl;//TODO error
		}

		glDetachShader(shaderProgramID, vertexShaderID);
		glDetachShader(shaderProgramID, fragmentShaderID);
		vertexShader.clean();
		fragmentShader.clean();

		bindAttributes();
		getUniformLocations();
	}

	void ShaderProgram::destroyShaderProgram()
	{
		stopShaderProgram();
		
		glDeleteProgram(shaderProgramID);
		shaderProgramID = 0;
	}

	void ShaderProgram::startShaderProgram()
	{
		if(shaderProgramID != 0)
			glUseProgram(shaderProgramID);
	}

	void ShaderProgram::stopShaderProgram()
	{
		glUseProgram(0);
	}

	void ShaderProgram::bindAttribute(const GLuint attribute, const std::string& name)
	{
		glBindAttribLocation(shaderProgramID, attribute, name.c_str());
	}

	GLuint ShaderProgram::getUniformLocation(const std::string& name)
	{
		GLuint result = glGetUniformLocation(shaderProgramID, name.c_str());

		if (result == -1)
			std::cout << "COULD NOT FIND UNIFORM VARIABLE: " << name << std::endl; //TODO error

		return result;
	}

	void ShaderProgram::loadInt(GLuint location, GLint value)
	{
		glUniform1i(location, value);
	}

	void ShaderProgram::loadFloat(GLuint location, GLfloat value)
	{
		glUniform1f(location, value);
	}

	void ShaderProgram::loadBoolean(GLuint location, bool value)
	{
		GLuint toLoad = 0;
		if (value) toLoad = 1;

		glUniform1i(location, toLoad);
	}

	void ShaderProgram::loadVector2(GLuint location, float value)
	{
		glUniform2f(location, value);
	}

	void ShaderProgram::loadVector3(GLuint location, float value)
	{
		glUniform3f(location, value);
	}

	void ShaderProgram::loadVector4(GLuint location, float value)
	{
		glUniform4f(location, value);
	}

	void ShaderProgram::loadMatrix3(GLuint location, float value)
	{
		glUniformMatrix3fv(location, value);
	}

	void ShaderProgram::loadMatrix4(GLuint location, float value)
	{
		glUniformMatrix4fv(location, value);
	}


}
