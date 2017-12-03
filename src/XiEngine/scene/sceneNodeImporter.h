#pragma once

#include "../precompiled.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../graphics/mesh.h"
#include "../scene/sceneNode.h"
#include "../utils/file.h"

class SceneNodeImporter
{
public:
	static SceneNode* import(const std::string& path);

private:
	File file_;
	const aiScene* assimpScene_;

	SceneNode* rootNode_;

	int numVertices_;
	int numIndices_;

	SceneNodeImporter(const std::string& path);

	SceneNode* loadScene();

	SceneNode* processNode(const std::string& name, aiNode* assimpNode);
	Mesh* processMesh(const std::string& name, aiMesh* assimpMesh);
};