#include "program.h"

#include "../core/camera.h"
#include "../core/core.h"
#include "../core/input.h"
#include "../core/time.h"
#include "../graphics/mesh.h"
#include "../resource/primitives.h"
#include "../resource/resourceManager.h"
#include "../scene/scene.h"
#include "../scene/sceneNodeImporter.h"
#include "../utils/logger.h"

void Program::init()
{
	Scene* scene = new Scene();

	Mesh* line = new Mesh("simpleLine", Primitives::line());
	Core::getCurrentCore()->getResourceManager()->addResource(line);

	Mesh* mesh2 = new Mesh("srodek", Primitives::sphere(20, 20));
	Core::getCurrentCore()->getResourceManager()->addResource(mesh2);

	axis = new SceneNode("coordAxis");
	{
		SceneNode* xAxis = new SceneNode("x");
		SceneNode* yAxis = new SceneNode("y");
		SceneNode* zAxis = new SceneNode("z");

		xAxis->getTransform().setPosition(xim::Vector3(0.5f, 0.0f, 0.0f));

		yAxis->getTransform().setRotation(xim::Vector3(0.0f, 0.0f, 90.0f));
		yAxis->getTransform().setPosition(xim::Vector3(0.0f, 0.5f, 0.0f));

		zAxis->getTransform().setRotation(xim::Vector3(0.0f, 90.0f, 0.0f));
		zAxis->getTransform().setPosition(xim::Vector3(0.0f, 0.0f, 0.5f));
		
		xAxis->mesh_ = line;
		yAxis->mesh_ = line;
		zAxis->mesh_ = line;
		
		axis->addChildNode(xAxis);
		axis->addChildNode(yAxis);
		axis->addChildNode(zAxis);
	}
	scene->getRootNode()->addChildNode(axis);


	myEntity2 = new SceneNode("costam");
	myEntity2->mesh_ = mesh2;
	scene->getRootNode()->addChildNode(myEntity2);

	myEntity = myEntity2->clone();
	myEntity->getTransform().setPosition(xim::Vector3(0.0f, 0.0f, 6.0f));
	myEntity2->addChildNode(myEntity);

	myEntity3 = myEntity2->clone();
	myEntity3->getTransform().setPosition(xim::Vector3(3.0f, 0.0f, 0.0f));
	myEntity->addChildNode(myEntity3);

	Core::getCurrentCore()->setCurrentScene(scene);
}

void Program::update()
{
	myEntity2->getTransform().setPosition(xim::Vector3(0.0f, sinf(Time::getElapsedTime()) * 5, 0.0f));
	myEntity2->getTransform().setRotation(xim::Vector3(0.0f, Time::getElapsedTime() * 30.0f, 0.0f));

	myEntity->getTransform().setRotation(xim::Vector3(1.0f, 0.0f, Time::getElapsedTime() * 100.0f));

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