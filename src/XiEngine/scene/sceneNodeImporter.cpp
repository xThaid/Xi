#include "sceneNodeImporter.h"

#include "../core/core.h"
#include "../math/ximath.h"
#include "../resource/resourceManager.h"
#include "../utils/logger.h"

SceneNode* SceneNodeImporter::import(const std::string& path)
{
	SceneNodeImporter importer(path);

	return importer.rootNode_;
}

SceneNodeImporter::SceneNodeImporter(const std::string& path) :
	file_(path),
	numVertices_(0),
	numIndices_(0)
{
	Assimp::Importer import;
	assimpScene_ = import.ReadFile(file_.getPath(), aiProcess_Triangulate | aiProcess_GenNormals);
	if (!assimpScene_ || assimpScene_->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !assimpScene_->mRootNode)
	{
		Logger::error("Assimp error while importing model: " + file_.getPath());
		rootNode_ = nullptr;
	}
	else
	{
		rootNode_ = loadScene();
	}
}

SceneNode* SceneNodeImporter::loadScene()
{
	if (!file_.exist())
		return nullptr;

	SceneNode* rootNode = processNode(file_.getFileName(), assimpScene_->mRootNode);

	Logger::debug("Imported model " + file_.getFileName() + " with " + std::to_string(assimpScene_->mNumMeshes) + " meshes");

	return rootNode;
}

SceneNode* SceneNodeImporter::processNode(const std::string& name, aiNode* assimpNode)
{
	SceneNode* node = new SceneNode(name);
	for (unsigned int i = 0; i < assimpNode->mNumMeshes; i++)
	{
		aiMesh* assimpMesh = assimpScene_->mMeshes[assimpNode->mMeshes[i]];

		const std::string& meshName = name + "_mesh" + std::to_string(i);
		Mesh* mesh = ResourceManager::getInstance()->getResource<Mesh>(meshName);
		if (mesh == nullptr)
		{
			mesh = processMesh(meshName, assimpMesh);
			ResourceManager::getInstance()->addResource(mesh);
		}
	
		if (assimpNode->mNumMeshes == 1)
		{
			node->setMesh(mesh);
		}
		else
		{
			SceneNode* child = new SceneNode(name + "_m" + std::to_string(i));
			child->setMesh(mesh);
			node->addChildNode(child);
		}
	}

	for (unsigned int i = 0; i < assimpNode->mNumChildren; i++)
	{
		SceneNode* child = processNode(name + "_child" + std::to_string(i), assimpNode->mChildren[i]);
		node->addChildNode(child);
	}

	return node;
}

Mesh* SceneNodeImporter::processMesh(const std::string& name, aiMesh* assimpMesh)
{
	std::vector<Vector3>* positions = new std::vector<Vector3>(assimpMesh->mNumVertices);
	std::vector<Vector3>* normals = new std::vector<Vector3>(assimpMesh->mNumVertices);
	
	std::vector<Vector2>* UV = nullptr;
	if (assimpMesh->mNumUVComponents[0] > 0)
	{
		UV = new std::vector<Vector2>(assimpMesh->mNumVertices);
	}

	std::vector<unsigned int>* indices = new std::vector<unsigned int>(assimpMesh->mNumFaces * 3);

	numVertices_ += assimpMesh->mNumVertices;
	for (unsigned int i = 0; i < assimpMesh->mNumVertices; i++)
	{
		(*positions)[i] = Vector3(assimpMesh->mVertices[i].x, assimpMesh->mVertices[i].y, assimpMesh->mVertices[i].z);
		(*normals)[i] = Vector3(assimpMesh->mNormals[i].x, assimpMesh->mNormals[i].y, assimpMesh->mNormals[i].z);

		if (assimpMesh->mTextureCoords[0])
		{
			(*UV)[i] = Vector2(assimpMesh->mTextureCoords[0][i].x, assimpMesh->mTextureCoords[0][i].y);
		}
	}

	numIndices_ += assimpMesh->mNumFaces * 3;
	for (unsigned int i = 0; i < assimpMesh->mNumFaces; i++)
	{
		for (unsigned int j = 0; j < 3; j++)
		{
			(*indices)[i * 3 + j] = assimpMesh->mFaces[i].mIndices[j];
		}
	}

	return new Mesh(name, new MeshGeometry(PrimitiveTopology::TRIANGLES, indices, positions, UV, normals));
}