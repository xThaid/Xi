#pragma once

#include "../math/ximath.h"

#include <glad/glad.h> 
#include <GLFW\glfw3.h>

#include <vector>
#include <string>

class Vertex
{
public:
	xim::Vector3 position;
	xim::Vector3 normal;
	xim::Vector2 texCoords;

	Vertex(xim::Vector3 position, xim::Vector3 normal, xim::Vector2 texCoords = xim::Vector2());
};

class Mesh
{
public:
	Mesh(std::vector<Vertex>& vertices, std::vector<int>& indices);
	~Mesh();

	void draw();

private:
	std::vector<Vertex> vertices;
	std::vector<int> indices;

	GLuint VAO, VBO, EBO;

	void load();
	void destroyVAO();
};

class Model
{
public:
	Model(Mesh* mesh);
	Model(std::vector<Mesh*>& meshes);
	~Model();
	
	void draw();

private:
	std::vector<Mesh*> meshes;
};