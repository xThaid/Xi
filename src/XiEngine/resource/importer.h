#pragma once

#include "../core/entity.h"

#include "../utils/file.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>

class Mesh;

class ModelImporter
{
public:
	static Entity* import(const std::string& path);

private:
	Entity* entity;
	const aiScene* scene;

	File file;

	int numVertices = 0;
	int numIndices = 0;

	ModelImporter(File file);

	void processNode(Entity* entity, aiNode* node);
	Mesh* processMesh(aiMesh* mesh);
};