#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <vector>

#include "ximath\ximath.h"

namespace TDEngine
{
	class Material;
	class Shader;

	struct Vertex
	{
		ximath::Vector3 position;
		ximath::Vector3 normal;
		ximath::Vector2 texCoords;
	};

	class Mesh
	{
	public:
		Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices);

		void draw(Shader& shader);

		void setMaterial(Material* material);

	private:
		GLuint VAO;

		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		Material* material;

		void setupVAO();
	};
}