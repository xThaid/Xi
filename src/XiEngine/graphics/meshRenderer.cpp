#include "meshRenderer.h"

#include "../graphics/camera.h"
#include "../graphics/material.h"
#include "../graphics/mesh.h"
#include "../math/ximath.h"
#include "../scene/sceneNode.h"

MeshRenderer::MeshRenderer() :
	mesh_(nullptr)
{
}

MeshRenderer::MeshRenderer(Mesh* mesh) :
	mesh_(mesh)
{
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::update()
{
}

void MeshRenderer::getBatches(Camera* cullCamera, std::vector<Batch>& batches)
{
	Intersection result = cullCamera->getFrustum().intersect(getWorldBoundingBox());

	if (result == OUTSIDE)
		return;

	Batch batch;
	batch.geometry_ = mesh_->getGeometry();
	batch.transform_ = node_->getWorldTransform();

	batches.push_back(batch);
}

void MeshRenderer::setMesh(Mesh* mesh)
{
	mesh_ = mesh;
}

void MeshRenderer::onWorldBoundingBoxUpdate()
{
	if (mesh_)
		worldBoundingBox_ = mesh_->getBoundingBox().transformed(node_->getWorldTransform());
	else
		worldBoundingBox_.clear();
}
