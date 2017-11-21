#pragma once

#include "glad\glad.h"

#include "../../math/ximath.h"

#include <string>

class File;

class ShaderFile
{
public:
	ShaderFile(const std::string& path, int type);
	~ShaderFile();

	GLuint compileShader();
	void destroyShader();

private:
	File* file;
	int type;

	GLuint shaderID;
};

class Shader
{
public:
	Shader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
	Shader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile, const std::string& geometryShaderFile);
	~Shader();

	void compileShader();
	void destroyShader();

	void useShader();
	void stopShader();
	
	void bindAttribute(const GLuint attribute, const std::string& name);
	GLuint getUniformLocation(const std::string& name);

	void loadInt(const std::string& name, GLint value);
	void loadFloat(const std::string& name, GLfloat value);
	void loadBoolean(const std::string& name, bool value);
	void loadVector2(const std::string& name, xim::Vector2& value);
	void loadVector3(const std::string& name, xim::Vector3& value);
	void loadVector4(const std::string& name, xim::Vector4& value);
	void loadMatrix4(const std::string& name, xim::Matrix4& value);

private:
	GLuint shaderProgramID;

	ShaderFile* vertexShader;
	ShaderFile* geometryShader;
	ShaderFile* fragmentShader;
};