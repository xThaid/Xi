#pragma once

#include "../precompiled.h"

#include "../graphics/graphicsDefs.h"
#include "../math/ximath.h"
#include "../resource/resource.h"

class Geometry;

class MeshGeometry
{
public:
	MeshGeometry(PrimitiveTopology topology,
		std::vector<unsigned int>* indices,
		std::vector<Vector3>* positions,
		std::vector<Vector3>* normals,
		std::vector<Vector2>* texCoords);

	~MeshGeometry();

	bool hasIndices();
	bool hasPositions();
	bool hasNormals();
	bool hasTexCoords();

	unsigned int* getIndicesData();

	float* prepareVertexData();

	inline Vector3* getPositions() { return &(*positions_)[0]; }

	inline PrimitiveTopology getPrimitiveTopology() { return topology_; }
	inline unsigned int getNumVertices() { return positions_->size(); }
	inline unsigned int getNumIndices() { return indices_->size(); }

	bool isCorrect();

	unsigned int getMemoryUse();

private:
	PrimitiveTopology topology_;

	std::vector<unsigned int>* indices_;

	std::vector<Vector3>* positions_;
	std::vector<Vector3>* normals_;
	std::vector<Vector2>* texCoords_;
};

class Mesh : public Resource
{
	XI_RESOURCE(Mesh)

public:
	Mesh(const std::string& name, MeshGeometry* meshGeometry);
	~Mesh();

	inline MeshGeometry* getMeshGeometry() { return meshGeometry_; }
	inline Geometry* getGeometry() { return geometry_; }

	inline BoundingBox& getBoundingBox() { return boundingBox_; }

private:
	MeshGeometry* meshGeometry_;
	Geometry* geometry_;

	BoundingBox boundingBox_;

	virtual bool beginLoad() override;
	virtual bool endLoad() override;

	virtual void release() override;

	virtual const std::string getTypeName() const override { return "Mesh"; }
};