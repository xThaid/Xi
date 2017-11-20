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

	void loadInt(GLuint location, GLint value);
	void loadFloat(GLuint location, GLfloat value);
	void loadBoolean(GLuint location, bool value);
	void loadVector2(GLuint location, ximath::Vector2 value);
	void loadVector3(GLuint location, ximath::Vector3 value);
	void loadVector4(GLuint location, ximath::Vector4 value);
	void loadMatrix3(GLuint location, ximath::Matrix3 value);
	void loadMatrix4(GLuint location, ximath::Matrix4 value);

private:
	GLuint shaderProgramID;

	ShaderFile* vertexShader;
	ShaderFile* geometryShader;
	ShaderFile* fragmentShader;
};