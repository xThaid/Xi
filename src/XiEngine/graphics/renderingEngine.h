#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "window.h"
#include "shader.h"

class Scene;
class Mesh;
class Camera;
class SceneNode;
class Texture2D;

class RenderingEngine
{
public:
	RenderingEngine(Window* window);
	~RenderingEngine();

	void init();
	void changeViewport(int width, int height);

	void render(Scene* scene);
private:
	int renderWidth, renderHeight;

	Texture2D* tempTexture;

	void setUp();
	void cleanUp();
	void destroy();

	void renderEntity(SceneNode* entity, Camera* camera);

	void renderMesh(Mesh* mesh);
};
