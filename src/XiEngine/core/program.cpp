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
	
	Mesh* mesh2 = new Mesh("plane", Primitives::plane(100, 100));
	ResourceManager::getInstance()->addResource(mesh2);

	myEntity = new SceneNode("costam");
	myEntity->getTransform().setPosition(Vector3(0.0f, 0.0f, -2.0f));
	myEntity->setMesh(mesh2);
	Material* myMaterial = MaterialLibrary::getInstance()->getDefaultMaterial();
	myEntity->setMaterial(myMaterial);
	scene->getRootNode()->addChildNode(myEntity);

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