#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

class Camera;
class DebugRenderer;
class Geometry;
class Graphics;
class Scene;
class SceneNode;
class Shader;
class UIRenderer;

class RenderingEngine
{
public:
	RenderingEngine();
	~RenderingEngine();

	void render(Scene* scene);

private:
	Graphics* graphics_;

	UIRenderer* uiRenderer_;
	DebugRenderer* debugRenderer_;

	Shader* terrainShader_;
	Shader* meshShader_;

	void setup();

	void drawDebug(SceneNode* node);
	
	void renderSceneNode(SceneNode* node);

	void sendCameraParametrs(Camera* camera, Shader* shader);
};
