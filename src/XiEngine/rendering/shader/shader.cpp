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

void Shader::loadInt(const std::string& name, GLint value)
{
	glUniform1i(getUniformLocation(name), value);
}

void Shader::loadFloat(const std::string& name, GLfloat value)
{
	glUniform1f(getUniformLocation(name), value);
}

void Shader::loadBoolean(const std::string& name, bool value)
{
	GLuint toLoad = 0;
	if (value) toLoad = 1;

	glUniform1i(getUniformLocation(name), toLoad);
}

void Shader::loadVector2(const std::string& name, xim::Vector2& v)
{
	glUniform2fv(getUniformLocation(name), 1, v.getPointer());
}

void Shader::loadVector3(const std::string& name, xim::Vector3& v)
{
	glUniform3fv(getUniformLocation(name), 1, v.getPointer());
}

void Shader::loadVector4(const std::string& name, xim::Vector4& v)
{
	glUniform4fv(getUniformLocation(name), 1, v.getPointer());
}

void Shader::loadMatrix4(const std::string& name, xim::Matrix4& m)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, false, m.getPointer());
}