#include "renderingEngine.h"

#include "../core/core.h"
#include "../core/input.h"
#include "../graphics/camera.h"
#include "../graphics/debugRenderer.h"
#include "../graphics/commandBuffer.h"
#include "../graphics/graphics.h"
#include "../graphics/material.h"
#include "../graphics/mesh.h"
#include "../graphics/shader.h"
#include "../graphics/texture.h"
#include "../resource/primitives.h"
#include "../resource/resourceManager.h"
#include "../scene/sceneNode.h"
#include "../scene/scene.h"
#include "../utils/logger.h"


RenderingEngine::RenderingEngine() :
	graphics_(Graphics::getInstance())
{
	debugRenderer_ = new DebugRenderer();

	commandBuffer_ = new CommandBuffer();

	setup();

	materialLibrary_ = new MaterialLibrary();
}


RenderingEngine::~RenderingEngine()
{
	cleanUp();
}

void RenderingEngine::render(Scene* scene)
{
	debugRenderer_->setView(scene->getMainCamera());

	graphics_->beginFrame();

	static Frustum frust;
	static bool pressed = false;

	if (Input::getKey(GLFW_KEY_V) && !pressed)
	{
		pressed = true;
		frust = scene->getMainCamera()->getFrustum();
		scene->getMainCamera()->setFarClip(2000.0f);
	}

	if (pressed)
		debugRenderer_->addFrustum(frust, Color::WHITE);
	else
		debugRenderer_->addFrustum(scene->getMainCamera()->getFrustum(), Color::WHITE);

	debugRenderer_->addQuad(Vector3(0.0f), 1.0f, 1.0f, Color::ORANGE);
	debugRenderer_->addTriangle(Vector3(0.0f, 0.0f, -1.0f), Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f), Color::RED);

	BoundingBox box(-3.0f, 3.0f);
	debugRenderer_->addBoundingBox(box, Matrix4(), Color::GREEN);

	debugRenderer_->render();

	//renderSceneNode(scene->getRootNode());
	//renderPushedCommands(scene->getMainCamera());
	//commandBuffer_->clear();

	debugRenderer_->handleEndFrame();
	graphics_->endFrame();
}

void RenderingEngine::setup()
{
	ResourceManager::getInstance()->addResource(
		new Shader("debug shader", "D:/Dev/Repos/Xi/res/shaders/debug.vert", "D:/Dev/Repos/Xi/res/shaders/debug.frag"));
}

void RenderingEngine::cleanUp()
{
	delete debugRenderer_;
	delete commandBuffer_;
	delete materialLibrary_;
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
	shader->setMatrix4("projection", camera->getProjection());
	shader->setMatrix4("view", camera->getView());
	shader->setVector3("viewPos", camera->position);
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