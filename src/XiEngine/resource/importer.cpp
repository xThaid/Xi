#include "importer.h"

#include "../rendering/model.h"

#include "../utils/logger.h"

Entity* ModelImporter::import(const std::string& path)
{
	File file(path);
	ModelImporter importer(file);

	Logger::info("Imported model " + file.getFileName() + " with " + std::to_string(importer.numVertices) + " vertices and " + std::to_string(importer.numIndices) + " indices");

	return importer.entity;
}

ModelImporter::ModelImporter(File file) :
	file(file)
{
	entity = new Entity();

	Assimp::Importer import;
	scene = import.ReadFile(file.getPath(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		Logger::warn("Assimp error while importing model: " + file.getPath());
		return;
	}

	processNode(entity, scene->mRootNode);
}

void ModelImporter::processNode(Entity* entity, aiNode* node)
{
	std::vector<Mesh*> meshes;
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

		meshes.push_back(processMesh(mesh));
	}

	entity->setModel(new Model(meshes));

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		Entity* child = new Entity();
		processNode(child, node->mChildren[i]);
		entity->addChild(child);
	}
}

Mesh* ModelImporter::processMesh(aiMesh* mesh)
{
	std::vector<Vertex> vertices;
	numVertices += mesh->mNumVertices;
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		xim::Vector3 pos = xim::Vector3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		xim::Vector3 normal = xim::Vector3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

		xim::Vector2 txtCoords;
		if (mesh->mTextureCoords[0])
			txtCoords.set(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);

		vertices.push_back(Vertex(pos, normal, txtCoords));
	}

	std::vector<int> indices;
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		numIndices += face.mNumIndices;
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	return new Mesh(vertices, indices);
}
