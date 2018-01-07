#pragma once

#include "../precompiled.h"

#include "../math/ximath.h"

class Component;
class Scene;

class SceneNode
{
public:
	SceneNode(Scene* scene, const std::string& name);
	~SceneNode();
	
	SceneNode(const SceneNode&) = delete;
	void operator=(const SceneNode&) = delete;

	SceneNode* clone(bool cloneName = false) const;

	void update();

	inline Scene* getScene() { return scene_; }

	inline std::string getName() { return name_; }

	void setPosition(const Vector3& position);
	void setRotation(const Vector3& rotation);
	void setScale(float scale);
	void setScale(const Vector3& scale);

	void translate(const Vector3& delta);
	void rotate(const Vector3& delta);

	inline Vector3 getLocalPosition() { return position_; }
	inline Vector3 getLocalRotation() { return rotation_; }
	inline Vector3 getLocalScale() { return scale_; }

	Matrix3x4 getLocalTransform();

	Matrix3x4 getWorldTransform();

	inline bool isRootNode() { return parentNode_ == nullptr; }
	inline SceneNode* getParentNode() { return parentNode_; }

	SceneNode* createChild(const std::string& name);
	void addChild(SceneNode* node);

	SceneNode* findChild(StringHash nameHash);
	void removeChild(StringHash nameHash, bool purge = true);
	std::vector<SceneNode*> getChildren();

	void addComponent(Component* component);

	bool hasComponent(StringHash type);
	Component* getComponent(StringHash type);
	void removeComponent(StringHash type, bool purge = true);
	std::vector<Component*> getAllComponents();

	void getComponentsRecursive(StringHash type, std::vector<Component*>& dest);

private:
	Scene* scene_;

	std::string name_;
	StringHash nameHash_;

	bool dirty_;
	Matrix3x4 worldTransform_;

	Vector3 position_;
	Vector3 rotation_; // in degrees
	Vector3 scale_;

	SceneNode* parentNode_;
	std::map<StringHash, SceneNode*> childrenNode_;

	std::map<StringHash, Component*> components_;

	void markDirty();

	void updateWorldTransform();
};