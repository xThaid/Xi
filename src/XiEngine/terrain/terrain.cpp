#include "terrain.h"

#include "../graphics/camera.h"
#include "../graphics/indexBuffer.h"
#include "../scene/scene.h"
#include "../scene/sceneNode.h"
#include "../terrain/quadTreeFace.h"
#include "../terrain/quadTreeNode.h"
#include "../terrain/quadTreePatch.h"

Terrain::Terrain()
{

}

Terrain::~Terrain()
{
	for (QuadTreeFace* face : faces_)
		delete face;
}

void Terrain::update()
{
	for (QuadTreeFace* face : faces_)
		face->update();
}

void Terrain::getBatches(Camera* cullCamera, std::vector<Batch>& batches)
{
	for (QuadTreeFace* face : faces_)
		face->getBatches(cullCamera, batches);
}

void Terrain::drawDebugGeometry(DebugRenderer* debug)
{
	for (QuadTreeFace* face : faces_)
		face->drawDebugGeometry(debug);
}

Camera* Terrain::getCullCamera()
{
	return node_->getScene()->getCullCamera().get();
}

void Terrain::onWorldBoundingBoxUpdate()
{
}