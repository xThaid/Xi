#include "sceneNode.h"

#include "../utils/logger.h"

SceneNode::SceneNode(const std::string& name) :
	name_(name),
	nameHash_(name)
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
