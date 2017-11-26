#include "renderingEngine.h"

#include "../core/scene.h"
#include "../core/entity.h"
#include "../core/camera.h"

#include "../utils/logger.h"

#include "model.h"
#include "texture.h"

RenderingEngine::RenderingEngine(Window * window)
{
	if (!glfwInit())
		Logger::error("Failed to initialize GLFW");
	else
		Logger::debug("GLFW version: " + std::string(glfwGetVersionString()));

	window->init();
	glfwMakeContextCurrent(window->getWindow());

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		Logger::error("Failed to initialize GLAD");

	Logger::info("OpenGL version: " + std::string((char*)glGetString(GL_VERSION)));

	changeViewport(window->getWidth(), window->getHeight());

	setUp();
}


RenderingEngine::~RenderingEngine()
{
	cleanUp();
	destroy();
}

void RenderingEngine::init()
{
	entityShader->compileShader();

	glEnable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	xim::Matrix4 proj = xim::perspective(xim::radians(45.0f), 1.0f, 0.1f, 100.0f);
	entityShader->useShader();
	entityShader->loadMatrix4("projection", proj);

	entityShader->loadVector3("light.ambient", xim::Vector3(0.1f, 0.1f, 0.1f));
	entityShader->loadVector3("light.diffuse", xim::Vector3(0.5f, 0.5f, 0.5f));
	entityShader->loadVector3("light.specular", xim::Vector3(1.0f, 1.0f, 1.0f));

	entityShader->loadInt("material.diffuse", 0);
	entityShader->loadFloat("material.shininess", 32.0f);

}

void RenderingEngine::changeViewport(int width, int height)
{
	glViewport(0, 0, width, height);
	viewportWidth = width;
	viewportHeight = height;
}

void RenderingEngine::render(Scene* scene)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	xim::Matrix4 viewMatrix = scene->getMainCamera()->getViewMatrix();
	entityShader->useShader();
	entityShader->loadMatrix4("view", viewMatrix);
	entityShader->loadVector3("viewPos", scene->getMainCamera()->getPosition());

	entityShader->loadVector3("light.position", xim::Vector3(3.0f, 3.0f, 0.0f));

	for (Entity* entity : scene->getEntites())
	{
		entity->getTransform()->applyTranformToChildren();
		renderEntity(entity, scene->getMainCamera());
	}
}

void RenderingEngine::setUp()
{
	entityShader = new Shader("D:/Dev/Repos/Xi/res/shaders/entityShader.vs", "D:/Dev/Repos/Xi/res/shaders/entityShader.fs");
}

void RenderingEngine::cleanUp()
{
	delete entityShader;
}

void RenderingEngine::destroy()
{
	glfwTerminate();
}

void RenderingEngine::renderEntity(Entity* entity, Camera* camera)
{
	if (entity->getModel() != nullptr)
	{
		entityShader->loadMatrix4("model", entity->getTransform()->getModelMatrix());
		entity->getModel()->draw();
	}

	for (Entity* child : entity->getChildren())
	{
		renderEntity(child, camera);
	}
}
