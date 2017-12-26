#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

class Camera;
class DebugRenderer;
class Geometry;
class Graphics;
class MaterialLibrary;
class Mesh;
class Scene;
class SceneNode;
class Shader;

class RenderingEngine
{
public:
	RenderingEngine();
	~RenderingEngine();

	void render(Scene* scene);

private:
	Graphics* graphics_;

	DebugRenderer* debugRenderer_;

	Shader* terrainShader_;
	Shader* meshShader_;

	void setup();
	void cleanUp();

	void drawDebug(SceneNode* node);
	
	void renderPushedCommands(Camera* camera);

	void renderSceneNode(SceneNode* node);

	void sendGlobalUniformsToAll(Camera* camera);
	void sendGlobalUniforms(Shader* shader, Camera* viewCamera);
};
