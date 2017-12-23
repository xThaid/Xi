#pragma once

#include "../precompiled.h"

#include "../math/ximath.h"

class Component;

class SceneNode
{
public:
	SceneNode(const std::string& name);
	~SceneNode();
	
	SceneNode(const SceneNode&) = delete;
	void operator=(const SceneNode&) = delete;

	SceneNode* clone(bool cloneName = false) const;

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

	Matrix4 getLocalTransform();

	Matrix4 getWorldTransform();

	inline bool isRootNode() { return parentNode_ == nullptr; }
	inline SceneNode* getParentNode() { return parentNode_; }

	SceneNode* createChild(const std::string& name);
	void addChild(SceneNode* node);

	SceneNode* findChild(StringHash nameHash);
	void removeChild(StringHash nameHash, bool purge = true);
	std::vector<SceneNode*> getChildren();

	void addComponent(Component* component);

	bool hasComponent(const std::type_index& type);
	Component* getComponent(const std::type_index& type);
	void removeComponent(const std::type_index& type, bool purge = true);
	std::vector<Component*> getComponents();

	template <class T> bool hasComponent();
	template <class T> T* getComponent();
	template <class T> void removeComponent();

private:
	std::string name_;
	StringHash nameHash_;

	bool dirty_;
	Matrix4 worldTransform_;

	Vector3 position_;
	Vector3 rotation_; // in degrees
	Vector3 scale_;

	SceneNode* parentNode_;
	std::map<StringHash, SceneNode*> childrenNode_;

	std::map<std::type_index, Component*> components_;

	void markDirty();

	void updateWorldTransform();
};

template<class T>
inline bool SceneNode::hasComponent()
{
	return hasComponent(typeid(T));
}

template<class T>
inline T* SceneNode::getComponent()
{
	return static_cast<T*>(getComponent(typeid(T)));
}

template<class T>
inline void SceneNode::removeComponent()
{
	removeComponent(typeid(T));
}
