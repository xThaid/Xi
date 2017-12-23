#include "program.h"

#include "../core/core.h"
#include "../core/input.h"
#include "../core/time.h"
#include "../graphics/camera.h"
#include "../graphics/mesh.h"
#include "../resource/primitives.h"
#include "../resource/resourceManager.h"
#include "../scene/scene.h"
#include "../terrain/quadTree.h"
#include "../utils/logger.h"

void Program::init()
{
	Scene* scene = new Scene();

	terrain = new QuadTree();
	SceneNode* terrainNode = new SceneNode("terrain");
	terrainNode->addComponent(terrain);

	scene->getRootNode()->addChild(terrainNode);

	Core::getCurrentCore()->setCurrentScene(scene);
}

void Program::update()
{
	FrameInfo info;
	info.camera_ = Core::getCurrentScene()->getMainCamera();

	terrain->update(info);

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