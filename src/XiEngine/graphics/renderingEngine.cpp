#include "renderingEngine.h"

#include "../core/core.h"
#include "../core/input.h"
#include "../core/camera.h"
#include "../graphics/material.h"
#include "../graphics/mesh.h"
#include "../graphics/shader.h"
#include "../graphics/texture.h"
#include "../resource/resourceManager.h"
#include "../scene/sceneNode.h"
#include "../scene/scene.h"
#include "../utils/logger.h"


RenderingEngine::RenderingEngine(Window * window)
{
	if (!glfwInit())
		Logger::error("Failed to initialize GLFW");
	else
		Logger::debug("GLFW version: " + std::string(glfwGetVersionString()));

	window->init();
	glfwMakeContextCurrent(window->getWindow());

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		Logger::error("Failed to initialize GLAD");

	Logger::info("OpenGL version: " + std::string((char*)glGetString(GL_VERSION)));

	changeRenderSize(window->getWidth(), window->getHeight());

	commandBuffer_ = new CommandBuffer();

	setUp();
}


RenderingEngine::~RenderingEngine()
{
	cleanUp();
	destroy();
}

void RenderingEngine::init()
{
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void RenderingEngine::changeRenderSize(int width, int height)
{
	glViewport(0, 0, width, height);
	renderWidth = width;
	renderHeight = height;
}

void RenderingEngine::render(Scene* scene)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	renderSceneNode(scene->getRootNode());

	renderPushedCommands(scene->getMainCamera());

	commandBuffer_->clear();
}

void RenderingEngine::setUp()
{
	Shader* defaultShader = new Shader("tempShader", "D:/Dev/Repos/Xi/res/shaders/temporary.vert", "D:/Dev/Repos/Xi/res/shaders/temporary.frag");
	Core::getCurrentCore()->getResourceManager()->addResource(defaultShader);
	Shader* axesShader = new Shader("axesShader", "D:/Dev/Repos/Xi/res/shaders/coordAxes.vert", "D:/Dev/Repos/Xi/res/shaders/coordAxes.frag");
	Core::getCurrentCore()->getResourceManager()->addResource(axesShader);

	Material* defaultMaterial = new Material("default", defaultShader);

	defaultMaterial->setVector3("light.ambient", xim::Vector3(0.1f, 0.1f, 0.1f));
	defaultMaterial->setVector3("light.diffuse", xim::Vector3(0.5f, 0.5f, 0.5f));
	defaultMaterial->setVector3("light.specular", xim::Vector3(1.0f, 1.0f, 1.0f));
	defaultMaterial->setVector3("light.position", xim::Vector3(3.0f, 3.0f, 0.0f));

	defaultMaterial->setInt("material.diffuse", 0);
	defaultMaterial->setFloat("material.shininess", 32.0f);
	Core::getCurrentCore()->getResourceManager()->addResource(defaultMaterial);

	tempTexture = new Texture2D("tempTexture", "D:/Dev/Repos/Xi/res/textures/uv-mapping.png");
	Core::getCurrentCore()->getResourceManager()->addResource(tempTexture);
}

void RenderingEngine::cleanUp()
{

}

void RenderingEngine::destroy()
{
	glfwTerminate();
}

void RenderingEngine::renderPushedCommands(Camera* camera)
{
	sendGlobalUniformsToAll(camera);
	
	for (RenderCommand& command : commandBuffer_->getDefaultRenderCommands())
	{
		renderCommand(&command);
	}
}

void RenderingEngine::renderSceneNode(SceneNode* node)
{
	node->getTransform().updateTransform();

	if (node->mesh_ != nullptr && node->material_ != nullptr)
	{
		commandBuffer_->push(node->mesh_, node->material_, node->getTransform().getTransform());
	}

	for (SceneNode* child : node->getChildren())
		renderSceneNode(child);
}

void RenderingEngine::sendGlobalUniformsToAll(Camera* camera)
{
	std::map<StringHash, Resource*>* shaders = Core::getCurrentCore()->getResourceManager()->getResources<Shader>();
	for (auto shader : *shaders)
	{
		Shader* castedShader = static_cast<Shader*>(shader.second);
		sendGlobalUniforms(castedShader, camera);
	}
}

void RenderingEngine::sendGlobalUniforms(Shader* shader, Camera* camera)
{
	shader->useShader();
	shader->setMatrix4("projection", getProjectionMatrix());
	shader->setMatrix4("view", camera->getViewMatrix());
	shader->setVector3("viewPos", camera->getPosition());
}

void RenderingEngine::renderCommand(RenderCommand* command)
{
	Material* material = command->material;
	Mesh* mesh = command->mesh;

	material->getShader()->useShader();
	material->getShader()->setMatrix4("model", command->transform);

	material->sendUniformsValuesToShader();

	renderMesh(mesh);
}

void RenderingEngine::renderMesh(Mesh* mesh)
{
	glBindVertexArray(mesh->getVAO());

	if(mesh->getMeshGeometry()->hasIndices())
		glDrawElements(mesh->getDrawMode(), mesh->getMeshGeometry()->getNumIndices(), GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(mesh->getDrawMode(), 0, mesh->getMeshGeometry()->getNumVertices());
}

xim::Matrix4 RenderingEngine::getProjectionMatrix()
{
	return xim::perspective(xim::radians(45.0f), (float)renderWidth / renderHeight, 0.1f, 100.0f);
}
