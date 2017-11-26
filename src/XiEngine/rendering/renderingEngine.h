#pragma once

#include <glad/glad.h> 
#include <GLFW\glfw3.h>

#include "window.h"
#include "shader.h"

class Scene;
class Mesh;
class Model;
class Camera;
class Entity;
class Texture;

class RenderingEngine
{
public:
	RenderingEngine(Window* window);
	~RenderingEngine();

	void init();
	void changeViewport(int width, int height);

	void render(Scene* scene);
private:
	int viewportWidth, viewportHeight;

	Shader* entityShader;

	void setUp();
	void cleanUp();
	void destroy();

	void renderEntity(Entity* entity, Camera* camera);

};
