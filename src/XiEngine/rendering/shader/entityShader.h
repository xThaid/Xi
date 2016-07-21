#pragma once

#include "shaderProgram.h"

namespace xiengine
{
	
	class EntityShader : public ShaderProgram
	{
	public:
		EntityShader();

		void loadModelMatrix(const ximath::Matrix4& mat);
		void loadProjectionMatrix(const ximath::Matrix4& mat);
		void loadviewMatrix(const ximath::Matrix4& mat);
		void loadMainColor(const ximath::Vector3& vec);

	private:
		GLuint loc_modelMatrix;
		GLuint loc_projectionMatrix;
		GLuint loc_viewMatrix;
		GLuint loc_mainColor;

		virtual void bindAttributes();
		virtual void getUniformLocations();
	};
}