#pragma once

#include "ximath.h"
#include "shader.h"

namespace xiengine
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
		ShaderProgram(const Shader& vertexShader, const Shader& geometryShader, const Shader& fragmentShader);
		virtual ~ShaderProgram();

		virtual void bindAttributes() = 0;
		virtual void getUniformLocations() = 0;

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

		Shader vertexShader;
		Shader geometryShader;
		Shader fragmentShader;
	};
}