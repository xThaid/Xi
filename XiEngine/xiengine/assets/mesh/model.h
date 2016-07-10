#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>

namespace TDEngine
{
	class Material;
	class Shader;

	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoords;
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