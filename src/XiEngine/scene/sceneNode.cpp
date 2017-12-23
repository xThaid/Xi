#include "sceneNode.h"

#include "../scene/component.h"
#include "../utils/logger.h"

SceneNode::SceneNode(const std::string& name) :
	name_(name),
	nameHash_(name),
	dirty_(false),
	worldTransform_(Matrix4()),
	position_(0.0f),
	rotation_(0.0f),
	scale_(1.0f)
{
}

SceneNode::~SceneNode()
{
	for (std::map<StringHash, SceneNode*>::iterator it = childrenNode_.begin(); it != childrenNode_.end(); it++)
		delete it->second;

	for (std::map<std::type_index, Component*>::iterator it = components_.begin(); it != components_.end(); it++)
		delete it->second;
}

SceneNode* SceneNode::clone(bool cloneName) const
{
	std::string newName = name_;
	if (!cloneName)
		newName += "_clone";

	SceneNode* myClone = new SceneNode(newName);
	
	myClone->parentNode_ = parentNode_;

	for (std::map<StringHash, SceneNode*>::const_iterator it = childrenNode_.begin(); it != childrenNode_.end(); it++)
	{
		SceneNode* cloneChild = it->second->clone(true);
		cloneChild->parentNode_ = myClone;
		myClone->childrenNode_[it->first] = cloneChild;
	}

	return myClone;
}

void SceneNode::setPosition(const Vector3& position)
{
	position_ = position;

	markDirty();
}

void SceneNode::setRotation(const Vector3& rotation)
{
	rotation_ = rotation;

	markDirty();
}

void SceneNode::setScale(float scale)
{
	setScale(Vector3(scale, scale, scale));
}

void SceneNode::setScale(const Vector3& scale)
{
	if (scale.x_ == 0.0f || scale.y_ == 0.0f || scale.z_ == 0.0f)
		return;

	scale_ = scale;

	markDirty();
}

void SceneNode::translate(const Vector3& delta)
{
	position_ += delta;

	markDirty();
}

void SceneNode::rotate(const Vector3& delta)
{
	rotation_ += delta;

	markDirty();
}

Matrix4 SceneNode::getLocalTransform()
{
	Matrix4 transform = Matrix4();
	transform.translate(position_);

	transform.rotateX(radToDeg(rotation_.x_));
	transform.rotateY(radToDeg(rotation_.y_));
	transform.rotateZ(radToDeg(rotation_.z_));

	transform.scale(scale_);

	return transform;
}

Matrix4 SceneNode::getWorldTransform()
{
	if (dirty_)
		updateWorldTransform();

	return worldTransform_;
}

SceneNode* SceneNode::createChild(const std::string& name)
{
	SceneNode* child = new SceneNode(name);
	addChild(child);

	return child;
}

void SceneNode::addChild(SceneNode* node)
{
	if (node == nullptr)
	{
		Logger::warn("Trying to add nullptr as child");
		return;
	}

	if (node == this)
		return;

	if (findChild(node->nameHash_) != nullptr)
	{
		Logger::warn(name_ + " node has already child with name: " + node->name_);
		return;
	}

	if (node->parentNode_)
		node->parentNode_->removeChild(node->nameHash_, false);

	node->parentNode_ = this;
	childrenNode_[node->nameHash_] = node;
}

SceneNode* SceneNode::findChild(StringHash nameHash)
{
	std::map<StringHash, SceneNode*>::iterator child = childrenNode_.find(nameHash);
	if (child == childrenNode_.end())
		return nullptr;

	return child->second;
}

void SceneNode::removeChild(StringHash nameHash, bool purge)
{
	SceneNode* child = findChild(nameHash);
	if (!child)
		return;

	childrenNode_.erase(nameHash);

	if (purge)
		delete child;
}

std::vector<SceneNode*> SceneNode::getChildren()
{
	std::vector<SceneNode*> children;
	for (std::map<StringHash, SceneNode*>::iterator it = childrenNode_.begin(); it != childrenNode_.end(); it++)
		children.push_back(it->second);

	return children;
}

void SceneNode::addComponent(Component* component)
{
	std::type_index type = component->getType();

	if (hasComponent(type))
	{
		Logger::warn("Scene node " + name_ + " has already component of type " + type.name());
		return;
	}

	components_[type] = component;

	component->node_ = this;
	component->onNodeSet();
}

bool SceneNode::hasComponent(const std::type_index& type)
{
	auto result = components_.find(type);

	if (result != components_.end())
		return true;

	return false;
}

Component* SceneNode::getComponent(const std::type_index& type)
{
	auto result = components_.find(type);

	if (result != components_.end())
		return result->second;

	return nullptr;
}

void SceneNode::removeComponent(const std::type_index& type, bool purge)
{
	Component* component = getComponent(type);

	if (!component)
		return;

	components_.erase(type);

	if (purge)
		delete component;
}

std::vector<Component*> SceneNode::getComponents()
{
	std::vector<Component*> components;
	for (auto it = components_.begin(); it != components_.end(); it++)
		components.push_back(it->second);

	return components;
}

void SceneNode::markDirty()
{
	if (dirty_)
		return;

	dirty_ = true;

	for (std::map<StringHash, SceneNode*>::iterator it = childrenNode_.begin(); it != childrenNode_.end(); it++)
		it->second->markDirty();

	for (std::map<std::type_index, Component*>::iterator it = components_.begin(); it != components_.end(); it++)
		it->second->onMarkedDirty();
}

void SceneNode::updateWorldTransform()
{
	worldTransform_ = getLocalTransform();

	if (!isRootNode())
	{
		worldTransform_ = parentNode_->getWorldTransform() * worldTransform_;
	}

	dirty_ = false;
}
