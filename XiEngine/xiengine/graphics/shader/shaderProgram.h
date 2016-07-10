#pragma once

#include "shader.h"

namespace TDEngine
{
	class ShaderProgram
	{
	public:
		void initShaderProgram();
		void destroyShaderProgram();

		void startShaderProgram();
		void stopShaderProgram();
		
	protected:
		ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);
		virtual ~ShaderProgram();

		virtual void bindAttributes() = 0;
		virtual void getUniformLocations() = 0;

		void bindAttribute(const GLuint attribute, const std::string& name);
		GLuint getUniformLocation(const std::string& name);

		void loadInt(GLuint location, GLint value);
		void loadFloat(GLuint location, GLfloat value);
		void loadBoolean(GLuint location, bool value);
		void loadVector2(GLuint location, float value);
		void loadVector3(GLuint location, float value);
		void loadVector4(GLuint location, float value);
		void loadMatrix3(GLuint location, float value);
		void loadMatrix4(GLuint location, float value);

	private:
		GLuint shaderProgramID;

		Shader vertexShader;
		Shader fragmentShader;
	};
}