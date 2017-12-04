#include "renderingEngine.h"

#include "../core/core.h"
#include "../core/input.h"
#include "../core/camera.h"
#include "../scene/sceneNode.h"
#include "../scene/scene.h"
#include "../utils/logger.h"
#include "../resource/resourceManager.h"

#include "mesh.h"
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
	glEnable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	xim::Matrix4 proj = xim::perspective(xim::radians(45.0f), 1.0f, 0.1f, 100.0f);
	tempShader->useShader();
	tempShader->setMatrix4("projection", proj);

	tempShader->setVector3("light.ambient", xim::Vector3(0.1f, 0.1f, 0.1f));
	tempShader->setVector3("light.diffuse", xim::Vector3(0.5f, 0.5f, 0.5f));
	tempShader->setVector3("light.specular", xim::Vector3(1.0f, 1.0f, 1.0f));

	tempShader->setInt("material.diffuse", 0);
	tempShader->setFloat("material.shininess", 32.0f);
}

void RenderingEngine::changeViewport(int width, int height)
{
	glViewport(0, 0, width, height);
	renderWidth = width;
	renderHeight = height;
}

void RenderingEngine::render(Scene* scene)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	xim::Matrix4 viewMatrix = scene->getMainCamera()->getViewMatrix();
	tempShader->useShader();
	tempShader->setMatrix4("view", viewMatrix);
	tempShader->setVector3("viewPos", scene->getMainCamera()->getPosition());

	tempShader->setVector3("light.position", xim::Vector3(3.0f, 3.0f, 0.0f));

	renderEntity(scene->getRootNode(), scene->getMainCamera());
}

void RenderingEngine::setUp()
{
	tempShader = new Shader("tempShader", "D:/Dev/Repos/Xi/res/shaders/entityShader.vs", "D:/Dev/Repos/Xi/res/shaders/entityShader.fs");
	Core::getCurrentCore()->getResourceManager()->addResource(tempShader);
	tempTexture = new Texture2D("tempTexture", "D:/Dev/Repos/Xi/res/textures/uv-mapping.png");
	Core::getCurrentCore()->getResourceManager()->addResource(tempTexture);
}

void RenderingEngine::cleanUp()
{

}

void RenderingEngine::destroy()
{
	glfwTerminate();
}

void RenderingEngine::renderEntity(SceneNode* entity, Camera* camera)
{
	if (entity->mesh_ != nullptr)
	{
		tempTexture->getGLTexture()->bind();
		tempShader->setMatrix4("model", xim::Matrix4::scaleMatrix(xim::Vector3(1.0f)));
		renderMesh(entity->mesh_);
	}

	for (SceneNode* child : entity->getChildren())
		renderEntity(child, camera);
}

void RenderingEngine::renderMesh(Mesh* mesh)
{
	GLenum mode = mesh->getMeshTopology() == MeshTopology::TRIANGLES ? GL_TRIANGLES : GL_TRIANGLE_STRIP;

	glBindVertexArray(mesh->getVAO());

	if(mesh->hasIndices())
		glDrawElements(mode, mesh->getNumIndices(), GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(mode, 0, mesh->getNumVertices());
}
