#include "shader.h"

#include <glad/glad.h>

#include "../utils/logger.h"


ShaderVariation::ShaderVariation(const std::string& path, unsigned int type) :
	sourceFile_(File(path)),
	shaderType_(type),
	sourceCode_(""),
	memoryUse_(0),
	shaderVariationID_(0)
{
}

ShaderVariation::~ShaderVariation()
{
}

bool ShaderVariation::beginLoad()
{
	if (!sourceFile_.exist())
		return false;

	sourceCode_ = sourceFile_.loadText();
	memoryUse_ = sourceCode_.size();

	return true;
}

bool ShaderVariation::endLoad()
{
	return compileShader();
}

void ShaderVariation::release()
{
	destroyShader();
}

bool ShaderVariation::compileShader()
{
	GLint success;
	GLchar infoLog[512];

	shaderVariationID_ = glCreateShader(shaderType_);

	const char* tempSource = sourceCode_.c_str();
	glShaderSource(shaderVariationID_, 1, &tempSource, NULL);
	glCompileShader(shaderVariationID_);
	glGetShaderiv(shaderVariationID_, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderVariationID_, 512, NULL, infoLog);
		Logger::warn("Shader of type " + std::to_string(shaderType_) + " compilation failed: \n" + std::string(infoLog));

		destroyShader();

		return false;
	}

	return true;
}

void ShaderVariation::destroyShader()
{
	if (shaderVariationID_ != 0)
	{
		glDeleteShader(shaderVariationID_);
		shaderVariationID_ = 0;
	}
}

Shader::Shader(const std::string& shaderName, const std::string& vertexShaderFile, const std::string& fragmentShaderFile) :
	Resource(shaderName),
	shaderProgramID_(0)
{
	vertexShader_   = new ShaderVariation(vertexShaderFile,   GL_VERTEX_SHADER);
	fragmentShader_ = new ShaderVariation(fragmentShaderFile, GL_FRAGMENT_SHADER);
}

Shader::~Shader()
{
	delete vertexShader_;
	delete fragmentShader_;
}

bool Shader::beginLoad()
{
	bool vertexShaderResult = vertexShader_->beginLoad();
	bool fragmentShaderResult = fragmentShader_->beginLoad();

	setMemoryUse(vertexShader_->getMemoryUse() + fragmentShader_->getMemoryUse());

	if(!vertexShaderResult || !fragmentShaderResult)
		return false;

	return true;
}

bool Shader::endLoad()
{
	bool vertexShaderResult = vertexShader_->endLoad();
	bool fragmentShaderResult = fragmentShader_->endLoad();

	if (!vertexShaderResult || !fragmentShaderResult)
		return false;

	return linkShaders();
}

void Shader::release()
{
	shaderUniforms_.clear();

	destroyShader();
}

bool Shader::linkShaders()
{
	GLint success;
	GLchar infoLog[512];

	shaderProgramID_ = glCreateProgram();

	glAttachShader(shaderProgramID_, vertexShader_->getID());
	glAttachShader(shaderProgramID_, fragmentShader_->getID());

	glLinkProgram(shaderProgramID_);
	glGetProgramiv(shaderProgramID_, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgramID_, 512, NULL, infoLog);
		Logger::warn("Shader program linking failed: \n" + std::string(infoLog));

		destroyShader();

		return false;
	}

	glDetachShader(shaderProgramID_, vertexShader_->getID());
	glDetachShader(shaderProgramID_, fragmentShader_->getID());

	vertexShader_->destroyShader();
	fragmentShader_->destroyShader();

	loadUniforms();

	return true;
}

void Shader::destroyShader()
{
	if (shaderProgramID_ != 0)
	{
		glUseProgram(0);
		glDeleteProgram(shaderProgramID_);
		shaderProgramID_= 0;
	}
}

void Shader::useShader()
{
	glUseProgram(shaderProgramID_);
}

void Shader::setBool(const std::string& name, bool value)
{
	int location = getUniformLocation(name);
	if (location != -1)
	{
		glUniform1i(location, (int) value);
	}
}

void Shader::setInt(const std::string& name, int value)
{
	int location = getUniformLocation(name);
	if (location != -1)
	{
		glUniform1i(location, (int)value);
	}
}

void Shader::setFloat(const std::string& name, float value)
{
	int location = getUniformLocation(name);
	if (location != -1)
	{
		glUniform1f(location, value);
	}
}

void Shader::setVector2(const std::string& name, xim::Vector2& value)
{
	int location = getUniformLocation(name);
	if (location != -1)
	{
		glUniform2fv(location, 1, value.getPointer());
	}
}

void Shader::setVector3(const std::string& name, xim::Vector3& value)
{
	int location = getUniformLocation(name);
	if (location != -1)
	{
		glUniform3fv(location, 1, value.getPointer());
	}
}

void Shader::setVector4(const std::string& name, xim::Vector4& value)
{
	int location = getUniformLocation(name);
	if (location != -1)
	{
		glUniform4fv(location, 1, value.getPointer());
	}
}

void Shader::setMatrix4(const std::string& name, xim::Matrix4& value)
{
	int location = getUniformLocation(name);
	if (location != -1)
	{
		glUniformMatrix4fv(location, 1, false, value.getPointer());
	}
}

void Shader::loadUniforms()
{
	int numUniforms;
	glGetProgramiv(shaderProgramID_, GL_ACTIVE_UNIFORMS, &numUniforms);
	
	char buffer[128];
	for (int i = 0; i < numUniforms; i++)
	{
		GLenum type;
		GLint size;
		glGetActiveUniform(shaderProgramID_, i, sizeof(buffer), 0, &size, &type, buffer);

		std::string name = buffer;

		ShaderUniform uniform;
		uniform.name = name;
		uniform.type = UNIFORM_TYPE_BOOL;

		uniform.location = glGetUniformLocation(shaderProgramID_, buffer);
	
		shaderUniforms_[name] = uniform;
	}
}

int Shader::getUniformLocation(const std::string& name)
{
	std::map<std::string, ShaderUniform>::iterator uniform = shaderUniforms_.find(name);
	if (uniform == shaderUniforms_.end())
	{
		Logger::warn("Couldn't find uniform name " + name + " in shader " + std::to_string(shaderProgramID_));
		return -1;
	}

	return uniform->second.location;
}