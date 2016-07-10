#include "shaderProgram.h"

#include <iostream>

namespace xiengine
{
	ShaderProgram::ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader) :
		vertexShader(vertexShader), fragmentShader(fragmentShader)
	{
		shaderProgramID = 0;
	}

	ShaderProgram::~ShaderProgram()
	{
		destroyShaderProgram();
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

	void ShaderProgram::loadVector2(GLuint location, ximath::Vector2 v)
	{
		glUniform2f(location, v.x, v.y);
	}

	void ShaderProgram::loadVector3(GLuint location, ximath::Vector3 v)
	{
		glUniform3f(location, v.x, v.y, v.z);
	}

	void ShaderProgram::loadVector4(GLuint location, ximath::Vector4 v)
	{
		glUniform4f(location, v.x, v.y, v.z, v.w);
	}

	void ShaderProgram::loadMatrix3(GLuint location, ximath::Matrix3 m)
	{
		float arr[] = 
		{
			m[0][0], m[1][0], m[2][0],
			m[0][1], m[1][1], m[2][1],
			m[0][2], m[1][2], m[2][2]
		};

		glUniformMatrix3fv(location, 9, false, arr);
	}

	void ShaderProgram::loadMatrix4(GLuint location, ximath::Matrix4 m)
	{
		float arr[] =
		{
			m[0][0], m[1][0], m[2][0], m[3][0],
			m[0][1], m[1][1], m[2][1], m[3][1],
			m[0][2], m[1][2], m[2][2], m[3][2],
			m[0][3], m[1][3], m[2][3], m[3][3]
		};

		glUniformMatrix4fv(location, 1, false, arr);
	}


}
