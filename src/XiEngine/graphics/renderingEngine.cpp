#include "renderingEngine.h"

#include "../core/core.h"
#include "../core/input.h"
#include "../core/camera.h"
#include "../graphics/material.h"
#include "../graphics/mesh.h"
#include "../graphics/shader.h"
#include "../graphics/texture.h"
#include "../resource/primitives.h"
#include "../resource/resourceManager.h"
#include "../scene/sceneNode.h"
#include "../scene/scene.h"
#include "../utils/logger.h"


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

	changeRenderSize(window->getWidth(), window->getHeight());

	commandBuffer_ = new CommandBuffer();

	setup();

	materialLibrary_ = new MaterialLibrary();
}


RenderingEngine::~RenderingEngine()
{
	cleanUp();
	destroy();
}

void RenderingEngine::init()
{
	glEnable(GL_DEPTH_TEST);
}

void RenderingEngine::changeRenderSize(int width, int height)
{
	glViewport(0, 0, width, height);
	renderWidth = width;
	renderHeight = height;
}

void RenderingEngine::render(Scene* scene)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	renderSceneNode(scene->getRootNode());

	renderCoordAxes(Matrix4::translationMatrix(Vector3(0.0f, 0.0f, 0.0f)));

	renderPushedCommands(scene->getMainCamera());
	commandBuffer_->clear();
}

void RenderingEngine::renderCoordAxes(Matrix4 transform)
{
	Matrix4 xTransform = Matrix4();
	xTransform.translate(Vector3(0.5f, 0.0f, 0.0f));
	commandBuffer_->push(lineMesh_, MaterialLibrary::getInstance()->getMaterial("redDebug"), transform * xTransform);

	Matrix4 yTransform = Matrix4::translationMatrix(Vector3(0.0f, 0.5f, 0.0f));
	yTransform.rotateZ(degToRad(90.0f));
	commandBuffer_->push(lineMesh_, MaterialLibrary::getInstance()->getMaterial("greenDebug"), transform * yTransform);

	Matrix4 zTransform = Matrix4::translationMatrix(Vector3(0.0f, 0.0f, 0.5f));
	zTransform.rotateY(degToRad(90.0f));
	commandBuffer_->push(lineMesh_, MaterialLibrary::getInstance()->getMaterial("blueDebug"), transform * zTransform);
}

void RenderingEngine::setup()
{
	ResourceManager::getInstance()->addResource(
		new Shader("tempShader", "D:/Dev/Repos/Xi/res/shaders/temporary.vert", "D:/Dev/Repos/Xi/res/shaders/temporary.frag"));
	ResourceManager::getInstance()->addResource(
		new Shader("debug shader", "D:/Dev/Repos/Xi/res/shaders/debug.vert", "D:/Dev/Repos/Xi/res/shaders/debug.frag"));

	lineMesh_ = new Mesh("line", Primitives::line());
	ResourceManager::getInstance()->addResource(lineMesh_);
}

void RenderingEngine::cleanUp()
{
	delete commandBuffer_;
	delete materialLibrary_;
}

void RenderingEngine::destroy()
{
	glfwTerminate();
}

void RenderingEngine::renderPushedCommands(Camera* camera)
{
	sendGlobalUniformsToAll(camera);
	
	for (RenderCommand& command : commandBuffer_->getDefaultRenderCommands())
	{
		renderCommand(&command);
	}
}

void RenderingEngine::renderSceneNode(SceneNode* node)
{
	node->getTransform().updateTransform();

	if (node->isDrawable())
	{
		Material* material = node->getDrawable().material;
		if (material == nullptr)
			material = MaterialLibrary::getInstance()->getDebugMaterial();

		commandBuffer_->push(node->getDrawable().mesh, material, node->getTransform().getTransform());
	}

	for (SceneNode* child : node->getChildren())
		renderSceneNode(child);
}

void RenderingEngine::sendGlobalUniformsToAll(Camera* camera)
{
	std::map<StringHash, Resource*>* shaders = ResourceManager::getInstance()->getResources<Shader>();
	for (auto shader : *shaders)
	{
		Shader* castedShader = static_cast<Shader*>(shader.second);
		sendGlobalUniforms(castedShader, camera);
	}
}

void RenderingEngine::sendGlobalUniforms(Shader* shader, Camera* camera)
{
	shader->useShader();
	shader->setMatrix4("projection", getProjectionMatrix());
	shader->setMatrix4("view", camera->getViewMatrix());
	shader->setVector3("viewPos", camera->getPosition());
}

void RenderingEngine::renderCommand(RenderCommand* command)
{
	Material* material = command->material;
	Mesh* mesh = command->mesh;

	material->getShader()->useShader();
	material->getShader()->setMatrix4("model", command->transform);

	material->sendUniformsValuesToShader();

	if(material->isWireframe())
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	renderMesh(mesh);
}

void RenderingEngine::renderMesh(Mesh* mesh)
{
	glBindVertexArray(mesh->getVAO());

	if(mesh->getMeshGeometry()->hasIndices())
		glDrawElements(mesh->getDrawMode(), mesh->getMeshGeometry()->getNumIndices(), GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(mesh->getDrawMode(), 0, mesh->getMeshGeometry()->getNumVertices());
}

Matrix4 RenderingEngine::getProjectionMatrix()
{
	return Matrix4::perspective(degToRad(45.0f), (float)renderWidth / renderHeight, 0.1f, 100.0f);
}
