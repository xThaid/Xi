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

	SceneNode* tempNode = root->createChild("torus");
	tempNode->addComponent(meshRender);

	Core::getCurrentCore()->setCurrentScene(scene);
}

void Program::update()
{
	
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

	if (Input::getKey(GLFW_KEY_W))
		Core::getCurrentScene()->getMainCamera()->processKeyboard(CameraMovement::FORWARD, Time::getDeltaTime());
	if (Input::getKey(GLFW_KEY_S))
		Core::getCurrentScene()->getMainCamera()->processKeyboard(CameraMovement::BACKWARD, Time::getDeltaTime());
	if (Input::getKey(GLFW_KEY_A))
		Core::getCurrentScene()->getMainCamera()->processKeyboard(CameraMovement::LEFT, Time::getDeltaTime());
	if (Input::getKey(GLFW_KEY_D))
		Core::getCurrentScene()->getMainCamera()->processKeyboard(CameraMovement::RIGHT, Time::getDeltaTime());

	Core::getCurrentScene()->getMainCamera()->processMouse(Input::getMouseDeltaX(), -Input::getMouseDeltaY());
}