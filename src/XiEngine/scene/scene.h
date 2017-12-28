#pragma once

#include "../precompiled.h"

#include "../scene/sceneNode.h"

class Camera;
class Label;

class Scene
{
public:
	Scene();
	~Scene();

	void setViewCamera(Camera* camera);
	void setViewCamera(const std::shared_ptr<Camera>& camera);

	void setCullCamera(Camera* camera);
	void setCullCamera(const std::shared_ptr<Camera>& camera);

	void addLabel(Label* label);

	inline std::shared_ptr<Camera> getViewCamera() { return viewCamera_; }
	inline std::shared_ptr<Camera> getCullCamera() { return cullCamera_; }

	inline SceneNode* getRootNode() { return rootNode_; }

	inline std::vector<Label*>& getLabels() { return labels_; }

	void update();

private:
	std::shared_ptr<Camera> viewCamera_;
	std::shared_ptr<Camera> cullCamera_;

	SceneNode* rootNode_;

	std::vector<Label*> labels_;
};