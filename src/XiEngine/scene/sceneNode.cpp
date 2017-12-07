#include "sceneNode.h"

#include "../utils/logger.h"

Transform::Transform(SceneNode* owner) :
	owner_(owner),
	dirty_(false),
	position_(xim::Vector3(0.0f)),
	rotation_(xim::Vector3(0.0f)),
	scale_(xim::Vector3(1.0f)),
	transform_(xim::Matrix4())
{
}

void Transform::operator=(const Transform& copyFrom)
{
	position_ = copyFrom.position_;
	rotation_ = copyFrom.rotation_;
	scale_ = copyFrom.scale_;
	dirty_ = true;
}

void Transform::translate(xim::Vector3 vec)
{
	position_ += vec;
	dirty_ = true;
}

void Transform::rotate(xim::Vector3 angle)
{
	rotation_ += angle;
	dirty_ = true;
}

void Transform::setPosition(xim::Vector3 position)
{
	position_ = position;
	dirty_ = true;
}

void Transform::setRotation(xim::Vector3 rotation)
{
	rotation_ = rotation;
	dirty_ = true;
}

void Transform::setScale(float scale)
{
	scale_ = xim::Vector3(scale);
	dirty_ = true;
}

void Transform::setScale(xim::Vector3 scale)
{
	scale_ = scale;
	dirty_ = true;
}

xim::Matrix4 Transform::getTransform()
{
	if (dirty_)
	{
		updateTransform();
	}

	return transform_;
}

void Transform::updateTransform()
{
	if (dirty_)
	{
		transform_ = xim::Matrix4();
		transform_.translate(position_);

		transform_.rotateX(xim::radians(rotation_.x()));
		transform_.rotateY(xim::radians(rotation_.y()));
		transform_.rotateZ(xim::radians(rotation_.z()));

		transform_.scale(scale_);
	
		if (owner_->getParentNode() != nullptr)
		{
			Transform& parentTransform = owner_->getParentNode()->getTransform();
			transform_ = parentTransform.transform_ * transform_;
		}
	}

	for (SceneNode* child : owner_->getChildren())
	{
		Transform& childTranform = child->getTransform();
		if (dirty_)
		{
			childTranform.dirty_ = true;
		}

		childTranform.updateTransform();
	}

	dirty_ = false;
}

SceneNode::SceneNode(const std::string& name) :
	name_(name),
	nameHash_(name),
	transform_(this)
{
}

SceneNode::~SceneNode()
{
	for (std::map<StringHash, SceneNode*>::iterator it = childrenNode_.begin(); it != childrenNode_.end(); it++)
		delete it->second;
}

SceneNode* SceneNode::clone(bool cloneName) const
{
	std::string newName = name_;
	if (!cloneName)
		newName += "_clone";

	SceneNode* myClone = new SceneNode(newName);
	
	myClone->parentNode_ = parentNode_;
	myClone->mesh_ = mesh_;
	myClone->material_ = material_;
	myClone->transform_ = transform_;

	for (std::map<StringHash, SceneNode*>::const_iterator it = childrenNode_.begin(); it != childrenNode_.end(); it++)
		myClone->childrenNode_[it->first] = it->second->clone(true);

	return myClone;
}

void SceneNode::setName(const std::string& name)
{
	name_ = name;
	nameHash_ = name;

	parentNode_->addChildNode(this);
}

void SceneNode::addChildNode(SceneNode* node)
{
	if (node == nullptr)
	{
		Logger::warn("Trying to add nullptr as child");
		return;
	}

	if (node == this)
		return;

	if (findChildNode(node->nameHash_) != nullptr)
	{
		Logger::warn(name_ + " node has already child with name: " + node->name_);
		return;
	}

	if (node->parentNode_)
		node->parentNode_->removeChildNode(node->nameHash_, false);

	node->parentNode_ = this;
	childrenNode_[node->nameHash_] = node;
}

SceneNode* SceneNode::findChildNode(StringHash nameHash)
{
	std::map<StringHash, SceneNode*>::iterator child = childrenNode_.find(nameHash);
	if (child == childrenNode_.end())
		return nullptr;

	return child->second;
}

void SceneNode::removeChildNode(StringHash nameHash, bool purge)
{
	SceneNode* child = findChildNode(nameHash);
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
