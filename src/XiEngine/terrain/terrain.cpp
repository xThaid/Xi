#include "terrain.h"

#include "../graphics/camera.h"
#include "../graphics/indexBuffer.h"
#include "../scene/scene.h"
#include "../scene/sceneNode.h"
#include "../terrain/quadTreeFace.h"
#include "../terrain/quadTreeNode.h"
#include "../terrain/quadTreePatch.h"
#include "../terrain/terrainGenerator.h"

Terrain::Terrain() :
	nextPatchID_(0)
{
	generator_ = new TerrainGenerator(this);
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

void Terrain::cullNodesToRender(Camera* cullCamera, std::vector<QuadTreeNode*>& nodes)
{
	for (QuadTreeFace* face : faces_)
		face->cullNodesToRender(cullCamera, nodes);
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

unsigned int Terrain::getNextPatchID()
{
	return nextPatchID_++;
}

void Terrain::onNodeSet()
{
}

void Terrain::onMarkedDirty()
{
}
