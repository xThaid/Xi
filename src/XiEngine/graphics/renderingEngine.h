#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "../graphics/commandBuffer.h"
#include "../graphics/shader.h"
#include "../graphics/window.h"

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
	void changeRenderSize(int width, int height);

	void render(Scene* scene);
private:
	int renderWidth, renderHeight;

	CommandBuffer* commandBuffer_;

	Texture2D* tempTexture;

	void setUp();
	void cleanUp();
	void destroy();

	void renderPushedCommands(Camera* camera);

	void renderSceneNode(SceneNode* node);

	void sendGlobalUniformsToAll(Camera* camera);
	void sendGlobalUniforms(Shader* shader, Camera* camera);

	void renderCommand(RenderCommand* command);
	void renderMesh(Mesh* mesh);

	xim::Matrix4 getProjectionMatrix();
};
