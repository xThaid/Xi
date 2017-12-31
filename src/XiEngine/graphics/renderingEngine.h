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

	void toggleRenderUI();
	void setRenderUI(bool renderUI);

	void toggleRenderDebug();
	void setRenderDebug(bool renderDebug);

	void toggleWireframe();

	inline Graphics* getGraphics() { return graphics_; }

private:
	Graphics* graphics_;

	UIRenderer* uiRenderer_;
	DebugRenderer* debugRenderer_;

	Shader* terrainShader_;
	Shader* meshShader_;

	bool renderUI_;
	bool renderDebug_;
	bool wireframe_;

	void setupShaders();

	void drawDebug(SceneNode* node);
	
	void renderSceneNode(SceneNode* node);

	void sendCameraParametrs(Camera* camera, Shader* shader);
};
