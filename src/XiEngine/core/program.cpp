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
#include "../utils/logger.h"

SceneNode* tempNode;

void Program::init()
{
	Scene* scene = new Scene();
	SceneNode* root = scene->getRootNode();

	terrain = new QuadTree();
	SceneNode* terrainNode = root->createChild("terrain");
	terrainNode->addComponent(terrain);

	Mesh* tempMesh = new Mesh("kula2", Primitives::torus(3, 1, 50, 50));
	ResourceManager::getInstance()->addResource(tempMesh);
	MeshRenderer* meshRender = new MeshRenderer(tempMesh);
	
	tempNode = root->createChild("torus");

	tempNode->setPosition(Vector3(5.0f, 0.0f, 0.0f));
	tempNode->addComponent(meshRender);
	Core::getCurrentCore()->setCurrentScene(scene);
}

void Program::update()
{
	//tempNode->setPosition(Vector3(1.0f, 0.0f, 0.0f) * sinf(Time::getElapsedTime()) * 5.0f);
	//tempNode->setRotation(Vector3(0.0f, 1.0f, 0.0f) * 0.01f * Time::getElapsedTime());
	tempNode->setScale(sinf(Time::getElapsedTime() /2.0f) + 2.0f);

	if (Input::getKey(GLFW_KEY_F8) && !mouseLocked)
	{
		Input::lockMouse();
		mouseLocked = true;
	}
	if (Input::getKey(GLFW_KEY_F9) && mouseLocked)
	{
		Input::unlockMouse();
		mouseLocked = false;
	}

	if (Input::getKey(GLFW_KEY_ESCAPE))
		Core::getCurrentCore()->stop();

	float speed = 1.0f;
	if (Input::getKey(GLFW_KEY_LEFT_SHIFT))
		speed = 10.0f;

	if (Input::getKey(GLFW_KEY_W))
		Core::getCurrentScene()->getViewCamera()->processKeyboard(CameraMovement::FORWARD, Time::getDeltaTime() * speed);
	if (Input::getKey(GLFW_KEY_S))
		Core::getCurrentScene()->getViewCamera()->processKeyboard(CameraMovement::BACKWARD, Time::getDeltaTime() * speed);
	if (Input::getKey(GLFW_KEY_A))
		Core::getCurrentScene()->getViewCamera()->processKeyboard(CameraMovement::LEFT, Time::getDeltaTime() * speed);
	if (Input::getKey(GLFW_KEY_D))
		Core::getCurrentScene()->getViewCamera()->processKeyboard(CameraMovement::RIGHT, Time::getDeltaTime() * speed);

	Core::getCurrentScene()->getViewCamera()->processMouse(Input::getMouseDeltaX(), -Input::getMouseDeltaY());
}