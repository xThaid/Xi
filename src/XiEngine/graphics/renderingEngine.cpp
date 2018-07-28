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
#include "../terrain/quadTreeNode.h"
#include "../terrain/quadTreePatch.h"
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

	if (wireframe_)
		graphics_->setFillMode(FILL_WIREFRAME);

	std::vector<Component*> terrains;
	scene->getRootNode()->getComponentsRecursive("Terrain", terrains);

	std::vector<QuadTreeNode*> nodes;
	for (Component* comp : terrains)
	{
		Terrain* terrain = (Terrain*)comp;
		terrain->cullNodesToRender(cullCamera, nodes);
	}
	
	graphics_->setShader(terrainShader_);
	for (QuadTreeNode* node : nodes)
	{
		terrainShader_->setMatrix3x4("model", Matrix3x4());
		terrainShader_->setBool("fDrawBorders", node->shouldDrawBorders());
		terrainShader_->setColor("fColor", node->borderColor());

		node->getPatch()->getGeometry()->draw(graphics_, node->getPatchTopology()->getIndexBuffer());
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
    const std::string path ="/home/thaid/Dev/repos/Xi/res/shaders/";
	Shader* debugShader = new Shader("debug shader", path + "debug.vert", path + "debug.frag");
	Shader* textShader = new Shader("text shader", path + "textShader.vert", path + "textShader.frag");
	meshShader_ = new Shader("model shader", path + "models.vert", path + "models.frag");
	terrainShader_ = new Shader("terrain shader", path + "terrain.vert", path + "terrain.frag");

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
	shader->setMatrix3x4("view", camera->getView());
}