#pragma once

#include "../precompiled.h"

#include "../graphics/mesh.h"
#include "../utils/stringHash.h"

class SceneNode
{
public:
	Mesh* mesh_;

	SceneNode(const std::string& name);
	~SceneNode();
	
	SceneNode(const SceneNode&) = delete;
	void operator=(const SceneNode&) = delete;

	SceneNode* clone(bool cloneName = false) const;

	void setName(const std::string& name);

	void addChildNode(SceneNode* node);

	SceneNode* findChildNode(StringHash nameHash);
	void removeChildNode(StringHash nameHash, bool purge = true);

	std::vector<SceneNode*> getChildren();

private:
	std::string name_;
	StringHash nameHash_;

	SceneNode* parentNode_;
	std::map<StringHash, SceneNode*> childrenNode_;
};