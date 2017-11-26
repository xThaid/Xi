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
	myEntity = ModelImporter::import("D:/Dev/Repos/Xi/res/models/dragon.obj");
	myEntity2 = ModelImporter::import("D:/Dev/Repos/Xi/res/models/hand.obj");
	myEntity->addChild(myEntity2);
	myEntity2->getTransform()->position += xim::Vector3(3.0f, 0.0f, 0.0f);
	
	scene->addEntity(myEntity);
	
	Core::getCurrentCore()->setCurrentScene(scene);
}

void Program::update()
{
	myEntity->getTransform()->yaw += Time::getDeltaTime() /10.0f;
	myEntity2->getTransform()->position = xim::Vector3(cosf(Time::getElapsedTime()) * 2.0f, 0.0f, 0.0f);
	myEntity2->getTransform()->yaw = -Time::getElapsedTime();
	myEntity2->getTransform()->pitch = Time::getElapsedTime();

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