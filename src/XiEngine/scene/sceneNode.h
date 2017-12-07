#pragma once

#include "../precompiled.h"

#include "../graphics/material.h"
#include "../graphics/mesh.h"
#include "../math/ximath.h"
#include "../utils/stringHash.h"

class SceneNode;

class Transform
{
public:
	Transform(SceneNode* owner);
	
	void operator=(const Transform& copyFrom);

	void translate(xim::Vector3 vec);
	void rotate(xim::Vector3 angle);

	void setPosition(xim::Vector3 position);
	void setRotation(xim::Vector3 rotation);
	void setScale(float scale);
	void setScale(xim::Vector3 scale);

	inline xim::Vector3 getLocalPosition() { return position_; }
	inline xim::Vector3 getLocalRotation() { return rotation_; }
	inline xim::Vector3 getLocalScale() { return scale_; }

	xim::Matrix4 getTransform();
	void updateTransform();

private:
	SceneNode* owner_;
	
	bool dirty_;

	xim::Vector3 position_;
	xim::Vector3 rotation_; // in degrees
	xim::Vector3 scale_;

	xim::Matrix4 transform_;
};

class SceneNode
{
public:
	Mesh* mesh_;
	Material* material_;

	SceneNode(const std::string& name);
	~SceneNode();
	
	SceneNode(const SceneNode&) = delete;
	void operator=(const SceneNode&) = delete;

	SceneNode* clone(bool cloneName = false) const;

	void setName(const std::string& name);

	inline SceneNode* getParentNode() { return parentNode_; }

	void addChildNode(SceneNode* node);

	SceneNode* findChildNode(StringHash nameHash);
	void removeChildNode(StringHash nameHash, bool purge = true);

	std::vector<SceneNode*> getChildren();

	inline Transform& getTransform() { return transform_; }
	inline std::string getName() { return name_; }

private:
	std::string name_;
	StringHash nameHash_;

	SceneNode* parentNode_;
	std::map<StringHash, SceneNode*> childrenNode_;

	Transform transform_;
};