#include "renderingEngine.h"

#include "../core/core.h"
#include "../core/input.h"
#include "../graphics/camera.h"
#include "../graphics/drawable.h"
#include "../graphics/debugRenderer.h"
#include "../graphics/geometry.h"
#include "../graphics/graphics.h"
#include "../graphics/mesh.h"
#include "../graphics/meshRenderer.h"
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

	setup();
}


RenderingEngine::~RenderingEngine()
{
	cleanUp();
}

void RenderingEngine::render(Scene* scene)
{
	graphics_->beginFrame();

	Camera* cullCamera = scene->getCullCamera().get();
	Camera* viewCamera = scene->getViewCamera().get();

	debugRenderer_->setView(viewCamera);

	static bool debug = false;
	static bool pressed = false;
	static bool pressed2 = false;

	if (Input::getKey(GLFW_KEY_L) && !pressed)
	{
		pressed = true;
		debug = !debug;
	}
	else if (!Input::getKey(GLFW_KEY_L) && pressed)
		pressed = false;

	static bool debug2 = false;
	if (Input::getKey(GLFW_KEY_V) && !pressed2)
	{
		pressed2 = true;
		
		if (!debug2)
		{
			scene->setViewCamera(scene->getViewCamera()->copy());
		}
		else
		{
			scene->setViewCamera(scene->getCullCamera());
		}
		debug2 = !debug2;
	}
	else if (!Input::getKey(GLFW_KEY_V) && pressed2)
		pressed2 = false;


	sendGlobalUniformsToAll(viewCamera);

	std::vector<Component*> drawables;
	scene->getRootNode()->getComponentsRecursive("Drawable", drawables);

	std::vector<Batch> meshBatches, terrainBatches;

	for (Component* component : drawables)
	{
		Drawable* drawable = (Drawable*) component;

		if (dynamic_cast<QuadTree*>(drawable))
			drawable->getBatches(cullCamera, terrainBatches);
		else if (dynamic_cast<MeshRenderer*>(drawable))
			drawable->getBatches(cullCamera, meshBatches);
	}

	graphics_->setFillMode(FILL_WIREFRAME);
	for (Batch& batch : meshBatches)
	{
		graphics_->setShader(meshShader_);
		meshShader_->setMatrix4("model", batch.transform_);
		batch.geometry_->draw(graphics_);
	}

	for (Batch& batch : terrainBatches)
	{
		graphics_->setShader(terrainShader_);
		terrainShader_->setMatrix4("model", batch.transform_);
		batch.geometry_->draw(graphics_);
	}

	graphics_->setFillMode(FILL_SOLID);

	debugRenderer_->addLine(Vector3(0.0f), Vector3(1.0f, 0.0f, 0.0f), Color::RED);
	debugRenderer_->addLine(Vector3(0.0f), Vector3(0.0f, 1.0f, 0.0f), Color::GREEN);
	debugRenderer_->addLine(Vector3(0.0f), Vector3(0.0f, 0.0f, 1.0f), Color::BLUE);

	if (debug)
	{
		debugRenderer_->addFrustum(scene->getCullCamera()->getFrustum(), Color::WHITE);
		drawDebug(scene->getRootNode());
	}
	debugRenderer_->render();
	debugRenderer_->handleEndFrame();
	graphics_->endFrame();
}

void RenderingEngine::setup()
{
	ResourceManager::getInstance()->addResource(
		new Shader("debug shader", "D:/Dev/Repos/Xi/res/shaders/debug.vert", "D:/Dev/Repos/Xi/res/shaders/debug.frag"));
	meshShader_ = new Shader("model shader", "D:/Dev/Repos/Xi/res/shaders/models.vert", "D:/Dev/Repos/Xi/res/shaders/models.frag");
	ResourceManager::getInstance()->addResource(meshShader_);
	terrainShader_ = new Shader("terrain shader", "D:/Dev/Repos/Xi/res/shaders/terrain.vert", "D:/Dev/Repos/Xi/res/shaders/terrain.frag");
	ResourceManager::getInstance()->addResource(terrainShader_);
}

void RenderingEngine::cleanUp()
{
	delete debugRenderer_;
}

void RenderingEngine::drawDebug(SceneNode* node)
{
	for (Component* component : node->getAllComponents())
		component->drawDebugGeometry(debugRenderer_);

	for (SceneNode* child : node->getChildren())
		drawDebug(child);
}

void RenderingEngine::renderPushedCommands(Camera* camera)
{
	sendGlobalUniformsToAll(camera);
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

void RenderingEngine::sendGlobalUniforms(Shader* shader, Camera* viewCamera)
{
	shader->useShader();
	shader->setMatrix4("projection", viewCamera->getProjection());
	shader->setMatrix4("view", viewCamera->getView());
}