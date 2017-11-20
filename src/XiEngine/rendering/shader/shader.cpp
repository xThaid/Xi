#include "shader.h"

#include "../../utils/logger.h"
#include "../../utils/file.h"


ShaderFile::ShaderFile(const std::string& path, int type)
{
	this->type = type;

	file = new File(path);
}

ShaderFile::~ShaderFile()
{
	destroyShader();
	delete file;
}

GLuint ShaderFile::compileShader()
{
	std::string source = file->loadText();

	GLint success;
	GLchar infoLog[512];

	shaderID = glCreateShader(type);

	const char* arr = source.c_str();
	glShaderSource(shaderID, 1, &arr, NULL);
	glCompileShader(shaderID);
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		Logger::warn("Shader of type " + std::to_string(type) + " compilation failed: \n" + std::string(infoLog));
		destroyShader();

		return 0;
	}

	return shaderID;
}

void ShaderFile::destroyShader()
{
	if (shaderID != 0)
	{
		glDeleteShader(shaderID);
		shaderID = 0;
	}
}

Shader::Shader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
{
	vertexShader = new ShaderFile(vertexShaderFile, GL_VERTEX_SHADER);
	fragmentShader = new ShaderFile(fragmentShaderFile, GL_FRAGMENT_SHADER);
	geometryShader = nullptr;
}

Shader::Shader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile, const std::string& geometryShaderFile)
{
	vertexShader = new ShaderFile(vertexShaderFile, GL_VERTEX_SHADER);
	fragmentShader = new ShaderFile(fragmentShaderFile, GL_FRAGMENT_SHADER);
	geometryShader = new ShaderFile(geometryShaderFile, GL_GEOMETRY_SHADER);
}

Shader::~Shader()
{
	destroyShader();

	delete vertexShader;
	delete fragmentShader;

	if (geometryShader != nullptr)
		delete geometryShader;
}


void Shader::compileShader()
{
	GLuint vertexShaderID = vertexShader->compileShader();
	GLuint fragmentShaderID = fragmentShader->compileShader();

	GLuint geometryShaderID = 0;
	if(geometryShader != nullptr)
		geometryShaderID = geometryShader->compileShader();
	
	GLint success;
	GLchar infoLog[512];

	shaderProgramID = glCreateProgram();

	if (vertexShaderID != 0)
		glAttachShader(shaderProgramID, vertexShaderID);
	if (fragmentShaderID != 0)
		glAttachShader(shaderProgramID, fragmentShaderID);
	if (geometryShaderID != 0)
		glAttachShader(shaderProgramID, geometryShaderID);

	glLinkProgram(shaderProgramID);
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
		Logger::warn("Shader program linking failed: \n" + std::string(infoLog));
		destroyShader();
	}

	if (vertexShaderID != 0)
		glDetachShader(shaderProgramID, vertexShaderID);
	if (fragmentShaderID != 0)
		glDetachShader(shaderProgramID, fragmentShaderID);
	if (geometryShaderID != 0)
		glDetachShader(shaderProgramID, geometryShaderID);

	vertexShader->destroyShader();
	fragmentShader->destroyShader();
	if(geometryShader != nullptr)
		geometryShader->destroyShader();
}

void Shader::destroyShader()
{
	if (shaderProgramID != 0)
	{
		stopShader();
		glDeleteProgram(shaderProgramID);
		shaderProgramID = 0;
	}
}

void Shader::useShader()
{
	glUseProgram(shaderProgramID);
}

void Shader::stopShader()
{
	glUseProgram(0);
}

void Shader::bindAttribute(const GLuint attribute, const std::string& name)
{
	glBindAttribLocation(shaderProgramID, attribute, name.c_str());
}

GLuint Shader::getUniformLocation(const std::string& name)
{
	GLuint result = glGetUniformLocation(shaderProgramID, name.c_str());

	if (result == -1)
		Logger::warn("Could not find uniform variable: " + name);

	return result;
}

void Shader::loadInt(GLuint location, GLint value)
{
	glUniform1i(location, value);
}

void Shader::loadFloat(GLuint location, GLfloat value)
{
	glUniform1f(location, value);
}

void Shader::loadBoolean(GLuint location, bool value)
{
	GLuint toLoad = 0;
	if (value) toLoad = 1;

	glUniform1i(location, toLoad);
}

void Shader::loadVector2(GLuint location, ximath::Vector2 v)
{
	glUniform2f(location, v.x, v.y);
}

void Shader::loadVector3(GLuint location, ximath::Vector3 v)
{
	glUniform3f(location, v.x, v.y, v.z);
}

void Shader::loadVector4(GLuint location, ximath::Vector4 v)
{
	glUniform4f(location, v.x, v.y, v.z, v.w);
}

void Shader::loadMatrix3(GLuint location, ximath::Matrix3 m)
{
	float arr[] = 
	{
		m[0][0], m[1][0], m[2][0],
		m[0][1], m[1][1], m[2][1],
		m[0][2], m[1][2], m[2][2]
	};

	glUniformMatrix3fv(location, 9, false, arr);
}

void Shader::loadMatrix4(GLuint location, ximath::Matrix4 m)
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