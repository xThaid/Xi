#include "entityShader.h"

namespace xiengine
{
	EntityShader::EntityShader() :
		ShaderProgram(Shader("entityShader.vs"), Shader("entityShader.fs"))
	{
	}

	void EntityShader::loadModelMatrix(const ximath::Matrix4& mat)
	{
		loadMatrix4(loc_modelMatrix, mat);
	}

	void EntityShader::loadProjectionMatrix(const ximath::Matrix4& mat)
	{
		loadMatrix4(loc_projectionMatrix, mat);
	}

	void EntityShader::loadviewMatrix(const ximath::Matrix4& mat)
	{
		loadMatrix4(loc_viewMatrix, mat);
	}

	void EntityShader::loadMainColor(const ximath::Vector3& vec)
	{
		loadVector3(loc_mainColor, vec);
	}

	void EntityShader::bindAttributes()
	{
		bindAttribute(0, "position");
		bindAttribute(1, "normalVector");
		bindAttribute(2, "textureCoords");
	}

	void EntityShader::getUniformLocations()
	{
		loc_modelMatrix = getUniformLocation("modelMatrix");
		loc_projectionMatrix = getUniformLocation("projectionMatrix");
		loc_viewMatrix = getUniformLocation("viewMatrix");
		loc_mainColor = getUniformLocation("mainColor");
	}
}