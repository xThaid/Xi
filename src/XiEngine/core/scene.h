#pragma once

class Camera;

class Scene
{
public:
	Scene();
	~Scene();

	inline Camera* getMainCamera() { return mainCamera; }

	void update();
private:
	Camera* mainCamera;

	void destroy();
};