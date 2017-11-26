#include "program.h"

#include "core.h"
#include "scene.h"
#include "camera.h"
#include "input.h"
#include "time.h"

#include "../rendering/model.h"

#include "../resource/importer.h"

#include "../utils/logger.h"

void Program::init()
{
	Scene* scene = new Scene();

	//scene->addEntity(ModelImporter::import("D:/Dev/Repos/Xi/res/models/dragon.obj"));
	scene->addEntity(ModelImporter::import("D:/Dev/Repos/Xi/res/models/hand.obj"));

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