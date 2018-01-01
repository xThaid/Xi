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
#include "../terrain/sphericalTerrain.h"
#include "../ui/label.h"
#include "../utils/logger.h"

//SceneNode* tempNode;

void Program::init()
{
	Scene* scene = new Scene();
	Core::getCurrentCore()->setCurrentScene(scene);

	SceneNode* root = scene->getRootNode();

	Terrain* terrain = new SphericalTerrain(100.0f);
	SceneNode* terrainNode = root->createChild("terrain");
	terrainNode->addComponent(terrain);

	//Mesh* tempMesh = new Mesh("kula2", Primitives::torus(3, 1, 30, 30));
	//ResourceManager::getInstance()->addResource(tempMesh);
	//MeshRenderer* meshRender = new MeshRenderer(tempMesh);
	//tempNode = root->createChild("torus");
	//tempNode->addComponent(meshRender);

	coordLabels[0] = new Label("X: ", Vector2(0.0f, 15.0f), 0.3f);
	coordLabels[1] = new Label("Y: ", Vector2(0.0f, 30.0f), 0.3f);
	coordLabels[2] = new Label("Z: ", Vector2(0.0f, 45.0f), 0.3f);
	scene->addLabel(coordLabels[0]); scene->addLabel(coordLabels[1]); scene->addLabel(coordLabels[2]);

	drawLabels[0] = new Label("Primitives: ", Vector2(0.0f, 75.0f), 0.3f);
	drawLabels[1] = new Label("Batches: ", Vector2(0.0f, 90.0f), 0.3f);
	scene->addLabel(drawLabels[0]); scene->addLabel(drawLabels[1]);

	updatesLabel[0] = new Label("UPS: ", Vector2(0.0f, 120.0f), 0.3f);
	updatesLabel[1] = new Label("FPS: ", Vector2(0.0f, 135.0f), 0.3f);
	scene->addLabel(updatesLabel[0]); scene->addLabel(updatesLabel[1]);

	Input::addPressedEvent(GLFW_KEY_O, []() -> void {
		Core::getCurrentCore()->getRenderer()->toggleRenderUI();
	});

	Input::addPressedEvent(GLFW_KEY_P, []() -> void {
		Core::getCurrentCore()->getRenderer()->toggleRenderDebug();
	});

	Input::addPressedEvent(GLFW_KEY_X, []() -> void {
		Core::getCurrentCore()->getRenderer()->toggleWireframe();
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

	//tempNode->setRotation(Vector3(0.0f, 1.0f, 0.0f) * 0.01f * Time::getElapsedTime());

	if (Input::getKey(GLFW_KEY_ESCAPE))
		core->stop();

	float speed = 5.0f;
	if (Input::getKey(GLFW_KEY_LEFT_SHIFT))
		speed = 50.0f;

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

	drawLabels[0]->setText("Primitives: " + std::to_string(renderingEngine->getGraphics()->getPrimitivesCount()));
	drawLabels[1]->setText("Batches: " + std::to_string(renderingEngine->getGraphics()->getBatchesCount()));

	updatesLabel[0]->setText("UPS: " + std::to_string(core->getLastUPS()));
	updatesLabel[1]->setText("FPS: " + std::to_string(core->getLastFPS()));
}