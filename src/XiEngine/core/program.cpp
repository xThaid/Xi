#include "program.h"

#include "../core/core.h"
#include "../core/input.h"
#include "../core/time.h"
#include "../graphics/camera.h"
#include "../graphics/mesh.h"
#include "../graphics/meshRenderer.h"
#include "../resource/primitives.h"
#include "../resource/resourceManager.h"
#include "../scene/scene.h"
#include "../terrain/quadTree.h"
#include "../ui/label.h"
#include "../utils/logger.h"

SceneNode* tempNode;

void Program::init()
{
	Scene* scene = new Scene();
	SceneNode* root = scene->getRootNode();

	QuadTree* terrain = new QuadTree();
	SceneNode* terrainNode = root->createChild("terrain");
	terrainNode->addComponent(terrain);

	Mesh* tempMesh = new Mesh("kula2", Primitives::torus(3, 1, 50, 50));
	ResourceManager::getInstance()->addResource(tempMesh);
	MeshRenderer* meshRender = new MeshRenderer(tempMesh);
	tempNode = root->createChild("torus");
	tempNode->addComponent(meshRender);

	coordLabels[0] = new Label("X: ", Vector2(0.0f, 20.0f), 0.4f);
	coordLabels[1] = new Label("Y: ", Vector2(0.0f, 40.0f), 0.4f);
	coordLabels[2] = new Label("Z: ", Vector2(0.0f, 60.0f), 0.4f);

	scene->addLabel(coordLabels[0]); scene->addLabel(coordLabels[1]); scene->addLabel(coordLabels[2]);

	Core::getCurrentCore()->setCurrentScene(scene);

	Input::addPressedEvent(GLFW_KEY_O, []() -> void {
		Core::getCurrentCore()->getRenderer()->toggleRenderUI();
	});

	Input::addPressedEvent(GLFW_KEY_P, []() -> void {
		Core::getCurrentCore()->getRenderer()->toggleRenderDebug();
	});

	Input::addPressedEvent(GLFW_KEY_V, []() -> void {
		Scene* scene = Core::getCurrentScene();
		if (scene->getCullCamera() == scene->getViewCamera())
			scene->setViewCamera(scene->getViewCamera()->copy());
		else
			scene->setViewCamera(scene->getCullCamera());
	});
}

void Program::update()
{
	Core* core = Core::getCurrentCore();
	RenderingEngine* renderingEngine = core->getRenderer();
	Scene* scene = Core::getCurrentScene();

	tempNode->setRotation(Vector3(0.0f, 1.0f, 0.0f) * 0.01f * Time::getElapsedTime());

	if (Input::getKey(GLFW_KEY_ESCAPE))
		core->stop();

	float speed = 1.0f;
	if (Input::getKey(GLFW_KEY_LEFT_SHIFT))
		speed = 10.0f;

	if (Input::getKey(GLFW_KEY_W))
		scene->getViewCamera()->processKeyboard(CameraMovement::FORWARD, Time::getDeltaTime() * speed);
	if (Input::getKey(GLFW_KEY_S))
		scene->getViewCamera()->processKeyboard(CameraMovement::BACKWARD, Time::getDeltaTime() * speed);
	if (Input::getKey(GLFW_KEY_A))
		scene->getViewCamera()->processKeyboard(CameraMovement::LEFT, Time::getDeltaTime() * speed);
	if (Input::getKey(GLFW_KEY_D))
		scene->getViewCamera()->processKeyboard(CameraMovement::RIGHT, Time::getDeltaTime() * speed);

	scene->getViewCamera()->processMouse(Input::getMouseDeltaX(), -Input::getMouseDeltaY());

	coordLabels[0]->setText("X: " + std::to_string(scene->getViewCamera()->position.x_));
	coordLabels[1]->setText("Y: " + std::to_string(scene->getViewCamera()->position.y_));
	coordLabels[2]->setText("Z: " + std::to_string(scene->getViewCamera()->position.z_));
}