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

class Mesh : public Resource
{
	XI_RESOURCE(Mesh)

public:
	Mesh(const std::string& name,
		MeshTopology topology,
		std::vector<unsigned int>* indices, 
		std::vector<xim::Vector3>* positions, 
		std::vector<xim::Vector2>* UV, 
		std::vector<xim::Vector3>* normals);
	~Mesh();

	virtual bool beginLoad() override;
	virtual bool endLoad() override;

	virtual void release() override;

	virtual const std::string getTypeName() const override { return "Mesh"; }

	inline MeshTopology getMeshTopology() { return topology_; }
	inline unsigned int getNumIndices() { return indices_->size(); }
	inline unsigned int getNumVertices() { return positions_->size(); }

	inline unsigned int getVAO() { return VAO_; }

	bool hasPositions();
	bool hasUV();
	bool hasNormals();
	bool hasIndices();

protected:
	void setPositions(std::vector<xim::Vector3>* positions);
	void setUV(std::vector<xim::Vector2>* UV);
	void setNormals(std::vector<xim::Vector3>* normals);
	void setIndices(std::vector<unsigned int>* indices);

private:
	MeshTopology topology_;

	std::vector<xim::Vector3>* positions_;
	std::vector<xim::Vector2>* UV_;
	std::vector<xim::Vector3>* normals_;

	std::vector<unsigned int>* indices_;

	unsigned int VAO_;
	unsigned int VBO_;
	unsigned int EBO_;

	bool uploadToGPU(bool interleaved);

	void prepareData(std::vector<float>& data, bool interleaved);
};