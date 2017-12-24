#include "renderingEngine.h"

#include "../core/core.h"
#include "../core/input.h"
#include "../graphics/camera.h"
#include "../graphics/drawable.h"
#include "../graphics/debugRenderer.h"
#include "../graphics/commandBuffer.h"
#include "../graphics/geometry.h"
#include "../graphics/graphics.h"
#include "../graphics/material.h"
#include "../graphics/mesh.h"
#include "../graphics/shader.h"
#include "../graphics/texture.h"
#include "../resource/primitives.h"
#include "../resource/resourceManager.h"
#include "../scene/sceneNode.h"
#include "../scene/scene.h"
#include "../terrain/quadTree.h"
#include "../utils/logger.h"


RenderingEngine::RenderingEngine() :
	graphics_(Graphics::getInstance())
{
	debugRenderer_ = new DebugRenderer();

	commandBuffer_ = new CommandBuffer();

	setup();

	materialLibrary_ = new MaterialLibrary();
}


RenderingEngine::~RenderingEngine()
{
	cleanUp();
}

void RenderingEngine::render(Scene* scene)
{
	debugRenderer_->setView(scene->getMainCamera());

	static bool debug = false;
	static bool pressed = false;

	if (Input::getKey(GLFW_KEY_L) && !pressed)
	{
		pressed = true;
		debug = !debug;
	}
	else if (!Input::getKey(GLFW_KEY_L) && pressed)
		pressed = false;

	if(debug)
		drawDebug(scene);

	sendGlobalUniformsToAll(scene->getMainCamera());

	graphics_->beginFrame();


	debugRenderer_->addBoundingBox(tempMesh->getBoundingBox(), Color::BLUE);
	
	Shader* tempShader = ResourceManager::getInstance()->getResource<Shader>("model shader");
	tempShader->useShader();
	tempShader->setMatrix4("model", Matrix4());
	graphics_->setShader(tempShader);
	graphics_->setFillMode(FILL_WIREFRAME);
	tempMesh->getGeometry()->draw(graphics_);
	graphics_->setFillMode(FILL_SOLID);

	debugRenderer_->render();

	debugRenderer_->handleEndFrame();
	graphics_->endFrame();
}

void RenderingEngine::setup()
{
	ResourceManager::getInstance()->addResource(
		new Shader("debug shader", "D:/Dev/Repos/Xi/res/shaders/debug.vert", "D:/Dev/Repos/Xi/res/shaders/debug.frag"));
	ResourceManager::getInstance()->addResource(
		new Shader("model shader", "D:/Dev/Repos/Xi/res/shaders/models.vert", "D:/Dev/Repos/Xi/res/shaders/models.frag"));

	tempMesh = new Mesh("kula", Primitives::sphere(30, 30));
	ResourceManager::getInstance()->addResource(tempMesh);
}

void RenderingEngine::cleanUp()
{
	delete debugRenderer_;
	delete commandBuffer_;
	delete materialLibrary_;
}

void RenderingEngine::drawDebug(Scene* scene)
{
	drawDebug(scene->getRootNode());
}

void RenderingEngine::drawDebug(SceneNode* node)
{
	for (Component* component : node->getComponents())
		component->drawDebuGeometry(debugRenderer_);

	for (SceneNode* child : node->getChildren())
		drawDebug(child);
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

	for (SceneNode* child : node->getChildren())
		renderSceneNode(child);
}

void RenderingEngine::sendGlobalUniformsToAll(Camera* camera)
{
	std::map<StringHash, Resource*>* shaders = ResourceManager::getInstance()->getResources<Shader>();
	for (auto shader : *shaders)
	{
		Shader* castedShader = static_cast<Shader*>(shader.second);
		sendGlobalUniforms(castedShader, camera);
	}
}

void RenderingEngine::sendGlobalUniforms(Shader* shader, Camera* camera)
{
	shader->useShader();
	shader->setMatrix4("projection", camera->getProjection());
	shader->setMatrix4("view", camera->getView());
}

void RenderingEngine::renderCommand(RenderCommand* command)
{
	Material* material = command->material;
	Mesh* mesh = command->mesh;

	material->getShader()->useShader();
	material->getShader()->setMatrix4("model", command->transform);

	material->sendUniformsValuesToShader();

	if(material->isWireframe())
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}