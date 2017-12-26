#pragma once

#include "../graphics/drawable.h"

class Camera;
class Mesh;
class Material;

class MeshRenderer : public Drawable
{
public:
	MeshRenderer();
	MeshRenderer(Mesh* mesh);
	~MeshRenderer();

	virtual void update() override;

	virtual void getBatches(Camera* cullCamera, std::vector<Batch>& batches);

	void setMesh(Mesh* mesh);

protected:
	virtual void onWorldBoundingBoxUpdate() override;

private:
	Mesh* mesh_;
};