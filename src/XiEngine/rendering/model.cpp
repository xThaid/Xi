#include "model.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../utils/logger.h"
#include "../utils/file.h"
#include "../resource/importer.h"

Vertex::Vertex(xim::Vector3 position, xim::Vector3 normal, xim::Vector2 texCoords) :
	position(position),
	normal(normal),
	texCoords(texCoords)
{
}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<int>& indices) :
	vertices(vertices),
	indices(indices)
{
	load();
}

Mesh::~Mesh()
{
	destroyVAO();
}

void Mesh::draw()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::load()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

	glBindVertexArray(0);
}

void Mesh::destroyVAO()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

Model::Model(Mesh* mesh)
{
	meshes.push_back(mesh);
}

Model::Model(std::vector<Mesh*>& meshes) :
	meshes(meshes)
{
}

Model::~Model()
{
	for (Mesh* mesh : meshes)
	{
		delete mesh;
	}
}

void Model::draw()
{
	for (Mesh* mesh : meshes)
	{
		mesh->draw();
	}
}