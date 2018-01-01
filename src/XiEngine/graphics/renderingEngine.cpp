#include "renderingEngine.h"

#include "../core/core.h"
#include "../core/input.h"
#include "../graphics/camera.h"
#include "../graphics/drawable.h"
#include "../graphics/debugRenderer.h"
#include "../graphics/geometry.h"
#include "../graphics/graphics.h"
#include "../graphics/meshRenderer.h"
#include "../graphics/shader.h"
#include "../resource/resourceManager.h"
#include "../scene/sceneNode.h"
#include "../scene/scene.h"
#include "../terrain/terrain.h"
#include "../ui/label.h"
#include "../ui/uiRenderer.h"
#include "../utils/logger.h"


RenderingEngine::RenderingEngine() :
	graphics_(Graphics::getInstance()),
	renderUI_(true),
	renderDebug_(false),
	wireframe_(false)
{
	setupShaders();

	uiRenderer_ = new UIRenderer(graphics_, graphics_->getViewport());
	debugRenderer_ = new DebugRenderer(graphics_);
}


RenderingEngine::~RenderingEngine()
{
	delete uiRenderer_;
	delete debugRenderer_;
}

void RenderingEngine::render(Scene* scene)
{
	graphics_->beginFrame();

	Camera* cullCamera = scene->getCullCamera().get();
	Camera* viewCamera = scene->getViewCamera().get();

	sendCameraParametrs(viewCamera, meshShader_);
	sendCameraParametrs(viewCamera, terrainShader_);

	std::vector<Component*> drawables;
	scene->getRootNode()->getComponentsRecursive("Drawable", drawables);

	std::vector<Batch> meshBatches, terrainBatches;

	for (Component* component : drawables)
	{
		Drawable* drawable = (Drawable*) component;

		if (dynamic_cast<Terrain*>(drawable))
			drawable->getBatches(cullCamera, terrainBatches);
		else if (dynamic_cast<MeshRenderer*>(drawable))
			drawable->getBatches(cullCamera, meshBatches);
	}

	if (wireframe_)
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
		//terrainShader_->setVector3("fViewPos", viewCamera->position);
		if(batch.customIndexBuffer_)
			batch.geometry_->draw(graphics_, batch.customIndexBuffer_);
	}

	graphics_->setFillMode(FILL_SOLID);

	debugRenderer_->addLine(Vector3(0.0f), Vector3(1.0f, 0.0f, 0.0f), Color::RED);
	debugRenderer_->addLine(Vector3(0.0f), Vector3(0.0f, 1.0f, 0.0f), Color::GREEN);
	debugRenderer_->addLine(Vector3(0.0f), Vector3(0.0f, 0.0f, 1.0f), Color::BLUE);

	if (renderDebug_)
	{
		debugRenderer_->setView(viewCamera);

		if (viewCamera != cullCamera)
			debugRenderer_->addFrustum(scene->getCullCamera()->getFrustum(), Color::WHITE);
		drawDebug(scene->getRootNode());

		debugRenderer_->render();

		debugRenderer_->handleEndFrame();
	}

	if (renderUI_)
	{
		graphics_->setDepthTest(CMP_ALWAYS);
		uiRenderer_->renderLabels(scene->getLabels());
		graphics_->setDepthTest(CMP_LESSEQUAL);
	}

	graphics_->endFrame();
}

void RenderingEngine::toggleRenderUI()
{
	renderUI_ = !renderUI_;
}

void RenderingEngine::setRenderUI(bool renderUI)
{
	renderUI_ = renderUI;
}

void RenderingEngine::toggleRenderDebug()
{
	renderDebug_ = !renderDebug_;
}

void RenderingEngine::setRenderDebug(bool renderDebug)
{
	renderDebug_ = renderDebug;
}

void RenderingEngine::toggleWireframe()
{
	wireframe_ = !wireframe_;
}

void RenderingEngine::setupShaders()
{
	Shader* debugShader = new Shader("debug shader", "D:/Dev/Repos/Xi/res/shaders/debug.vert", "D:/Dev/Repos/Xi/res/shaders/debug.frag");
	Shader* textShader = new Shader("text shader", "D:/Dev/Repos/Xi/res/shaders/textShader.vert", "D:/Dev/Repos/Xi/res/shaders/textShader.frag");
	meshShader_ = new Shader("model shader", "D:/Dev/Repos/Xi/res/shaders/models.vert", "D:/Dev/Repos/Xi/res/shaders/models.frag");
	terrainShader_ = new Shader("terrain shader", "D:/Dev/Repos/Xi/res/shaders/terrain.vert", "D:/Dev/Repos/Xi/res/shaders/terrain.frag");

	ResourceManager::getInstance()->addResource(debugShader);
	ResourceManager::getInstance()->addResource(textShader);
	ResourceManager::getInstance()->addResource(meshShader_);
	ResourceManager::getInstance()->addResource(terrainShader_);
}

void RenderingEngine::drawDebug(SceneNode* node)
{
	for (Component* component : node->getAllComponents())
		component->drawDebugGeometry(debugRenderer_);

	for (SceneNode* child : node->getChildren())
		drawDebug(child);
}

void RenderingEngine::renderSceneNode(SceneNode* node)
{
	for (SceneNode* child : node->getChildren())
		renderSceneNode(child);
}

void RenderingEngine::sendCameraParametrs(Camera* camera, Shader* shader)
{
	graphics_->setShader(shader);
	shader->setMatrix4("projection", camera->getProjection());
	shader->setMatrix4("view", camera->getView());
}