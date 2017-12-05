#pragma once

#include "../precompiled.h"

#include "../math/ximath.h"
#include "../resource/resource.h"

enum class MeshTopology
{
	POINTS,
	LINES,
	LINE_STRIP,
	TRIANGLES,
	TRIANGLE_STRIP,
	TRIANGLE_FAN,
};

class MeshGeometry
{
public:
	MeshGeometry(MeshTopology topology,
		std::vector<unsigned int>* indices,
		std::vector<xim::Vector3>* positions,
		std::vector<xim::Vector2>* UV,
		std::vector<xim::Vector3>* normals);
	~MeshGeometry();

	bool hasIndices();
	bool hasPositions();
	bool hasUV();
	bool hasNormals();

	unsigned int* getIndicesData();
	void prepareData(std::vector<float>& data, bool interleaved);

	inline MeshTopology getMeshTopology() { return topology_; }
	inline unsigned int getNumVertices() { return positions_->size(); }
	inline unsigned int getNumIndices() { return indices_->size(); }

	bool isCorrect();

	unsigned int getMemoryUse();

private:
	MeshTopology topology_;

	std::vector<unsigned int>* indices_;

	std::vector<xim::Vector3>* positions_;
	std::vector<xim::Vector2>* UV_;
	std::vector<xim::Vector3>* normals_;
};

class Mesh : public Resource
{
	XI_RESOURCE(Mesh)

public:
	Mesh(const std::string& name, MeshGeometry* meshGeometry);
	~Mesh();

	virtual bool beginLoad() override;
	virtual bool endLoad() override;

	virtual void release() override;

	virtual const std::string getTypeName() const override { return "Mesh"; }

	inline MeshGeometry* getMeshGeometry() { return meshGeometry_; }
	inline unsigned int getDrawMode() { return drawMode_; }
	inline unsigned int getVAO() { return VAO_; }

private:
	MeshGeometry* meshGeometry_;

	unsigned int VAO_;
	unsigned int VBO_;
	unsigned int EBO_;
	
	unsigned int drawMode_;

	bool uploadToGPU(bool interleaved);
	void parseTopology();
};