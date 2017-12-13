#pragma once

#include "../precompiled.h"

#include "../graphics/material.h"
#include "../graphics/mesh.h"
#include "../math/ximath.h"

class SceneNode;

struct Drawable
{
	Mesh* mesh = nullptr;
	Material* material = nullptr;
};

class Transform
{
public:
	Transform(SceneNode* owner);
	
	void operator=(const Transform& copyFrom);

	void translate(Vector3 vec);
	void rotate(Vector3 angle);

	void setPosition(Vector3 position);
	void setRotation(Vector3 rotation);
	void setScale(float scale);
	void setScale(Vector3 scale);

	inline Vector3 getLocalPosition() { return position_; }
	inline Vector3 getLocalRotation() { return rotation_; }
	inline Vector3 getLocalScale() { return scale_; }

	Matrix4 getTransform();
	void updateTransform();

private:
	SceneNode* owner_;
	
	bool dirty_;

	Vector3 position_;
	Vector3 rotation_; // in degrees
	Vector3 scale_;

	Matrix4 transform_;
};

class SceneNode
{
public:
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
	
	void setMesh(Mesh* mesh);
	void setMaterial(Material* material);
	void setDrawable(Mesh* mesh, Material* material);
	bool isDrawable();

	inline Transform& getTransform() { return transform_; }
	inline std::string getName() { return name_; }

	inline Drawable& getDrawable() { return drawable_; }

private:
	std::string name_;
	StringHash nameHash_;

	SceneNode* parentNode_;
	std::map<StringHash, SceneNode*> childrenNode_;

	Transform transform_;

	Drawable drawable_;
};