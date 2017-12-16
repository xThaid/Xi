#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

class CommandBuffer;
class Camera;
class DebugRenderer;
class Graphics;
class MaterialLibrary;
class Mesh;
struct RenderCommand;
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

	MaterialLibrary* materialLibrary_;
	CommandBuffer* commandBuffer_;

	Mesh* lineMesh_;

	void setup();
	void cleanUp();

	void renderPushedCommands(Camera* camera);

	void renderSceneNode(SceneNode* node);

	void sendGlobalUniformsToAll(Camera* camera);
	void sendGlobalUniforms(Shader* shader, Camera* camera);

	void renderCommand(RenderCommand* command);
	void renderMesh(Mesh* mesh);
};
