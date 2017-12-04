#include "primitives.h"

namespace Primitives
{
	Quad::Quad(const std::string& name) :
		Quad(name, 1.0f, 1.0f)
	{
	}

	Quad::Quad(const std::string& name, float width, float height) :
		Mesh(name, MeshTopology::TRIANGLE_STRIP, nullptr, nullptr, nullptr, nullptr)
	{
		std::vector<xim::Vector3>* positions = new std::vector<xim::Vector3>
		{
			xim::Vector3(-width,  height, 0.0f),
			xim::Vector3(-width, -height, 0.0f),
			xim::Vector3( width,  height, 0.0f),
			xim::Vector3( width, -height, 0.0f)
		};

		std::vector<xim::Vector2>* UV = new std::vector<xim::Vector2>
		{
			xim::Vector2(0.0f, 1.0f),
			xim::Vector2(0.0f, 0.0f),
			xim::Vector2(1.0f, 1.0f),
			xim::Vector2(1.0f, 0.0f)
		};

		setPositions(positions);
		setUV(UV);
	}

	Cube::Cube(const std::string& name) :
		Mesh(name, MeshTopology::TRIANGLES, nullptr, nullptr, nullptr, nullptr)
	{
		std::vector<xim::Vector3>* positions = new std::vector<xim::Vector3>
		{
			xim::Vector3(-0.5f, -0.5f, -0.5f),
			xim::Vector3(0.5f,  0.5f, -0.5f),
			xim::Vector3(0.5f, -0.5f, -0.5f),
			xim::Vector3(0.5f,  0.5f, -0.5f),
			xim::Vector3(-0.5f, -0.5f, -0.5f),
			xim::Vector3(-0.5f,  0.5f, -0.5f),

			xim::Vector3(-0.5f, -0.5f,  0.5f),
			xim::Vector3(0.5f, -0.5f,  0.5f),
			xim::Vector3(0.5f,  0.5f,  0.5f),
			xim::Vector3(0.5f,  0.5f,  0.5f),
			xim::Vector3(-0.5f,  0.5f,  0.5f),
			xim::Vector3(-0.5f, -0.5f,  0.5f),

			xim::Vector3(-0.5f,  0.5f,  0.5f),
			xim::Vector3(-0.5f,  0.5f, -0.5f),
			xim::Vector3(-0.5f, -0.5f, -0.5f),
			xim::Vector3(-0.5f, -0.5f, -0.5f),
			xim::Vector3(-0.5f, -0.5f,  0.5f),
			xim::Vector3(-0.5f,  0.5f,  0.5f),

			xim::Vector3(0.5f,  0.5f,  0.5f),
			xim::Vector3(0.5f, -0.5f, -0.5f),
			xim::Vector3(0.5f,  0.5f, -0.5f),
			xim::Vector3(0.5f, -0.5f, -0.5f),
			xim::Vector3(0.5f,  0.5f,  0.5f),
			xim::Vector3(0.5f, -0.5f,  0.5f),

			xim::Vector3(-0.5f, -0.5f, -0.5f),
			xim::Vector3(0.5f, -0.5f, -0.5f),
			xim::Vector3(0.5f, -0.5f,  0.5f),
			xim::Vector3(0.5f, -0.5f,  0.5f),
			xim::Vector3(-0.5f, -0.5f,  0.5f),
			xim::Vector3(-0.5f, -0.5f, -0.5f),

			xim::Vector3(-0.5f,  0.5f, -0.5f),
			xim::Vector3(0.5f,  0.5f,  0.5f),
			xim::Vector3(0.5f,  0.5f, -0.5f),
			xim::Vector3(0.5f,  0.5f,  0.5f),
			xim::Vector3(-0.5f,  0.5f, -0.5f),
			xim::Vector3(-0.5f,  0.5f,  0.5f),
		};

		std::vector<xim::Vector2>* UV = new std::vector<xim::Vector2>
		{
			xim::Vector2(0.0f, 0.0f),
			xim::Vector2(1.0f, 1.0f),
			xim::Vector2(1.0f, 0.0f),
			xim::Vector2(1.0f, 1.0f),
			xim::Vector2(0.0f, 0.0f),
			xim::Vector2(0.0f, 1.0f),

			xim::Vector2(0.0f, 0.0f),
			xim::Vector2(1.0f, 0.0f),
			xim::Vector2(1.0f, 1.0f),
			xim::Vector2(1.0f, 1.0f),
			xim::Vector2(0.0f, 1.0f),
			xim::Vector2(0.0f, 0.0f),

			xim::Vector2(1.0f, 0.0f),
			xim::Vector2(1.0f, 1.0f),
			xim::Vector2(0.0f, 1.0f),
			xim::Vector2(0.0f, 1.0f),
			xim::Vector2(0.0f, 0.0f),
			xim::Vector2(1.0f, 0.0f),

			xim::Vector2(1.0f, 0.0f),
			xim::Vector2(0.0f, 1.0f),
			xim::Vector2(1.0f, 1.0f),
			xim::Vector2(0.0f, 1.0f),
			xim::Vector2(1.0f, 0.0f),
			xim::Vector2(0.0f, 0.0f),

			xim::Vector2(0.0f, 1.0f),
			xim::Vector2(1.0f, 1.0f),
			xim::Vector2(1.0f, 0.0f),
			xim::Vector2(1.0f, 0.0f),
			xim::Vector2(0.0f, 0.0f),
			xim::Vector2(0.0f, 1.0f),

			xim::Vector2(0.0f, 1.0f),
			xim::Vector2(1.0f, 0.0f),
			xim::Vector2(1.0f, 1.0f),
			xim::Vector2(1.0f, 0.0f),
			xim::Vector2(0.0f, 1.0f),
			xim::Vector2(0.0f, 0.0f),
		};

		std::vector<xim::Vector3>* normals = new std::vector<xim::Vector3>
		{
			xim::Vector3(0.0f,  0.0f, -1.0f),
			xim::Vector3(0.0f,  0.0f, -1.0f),
			xim::Vector3(0.0f,  0.0f, -1.0f),
			xim::Vector3(0.0f,  0.0f, -1.0f),
			xim::Vector3(0.0f,  0.0f, -1.0f),
			xim::Vector3(0.0f,  0.0f, -1.0f),

			xim::Vector3(0.0f,  0.0f,  1.0f),
			xim::Vector3(0.0f,  0.0f,  1.0f),
			xim::Vector3(0.0f,  0.0f,  1.0f),
			xim::Vector3(0.0f,  0.0f,  1.0f),
			xim::Vector3(0.0f,  0.0f,  1.0f),
			xim::Vector3(0.0f,  0.0f,  1.0f),

			xim::Vector3(-1.0f,  0.0f,  0.0f),
			xim::Vector3(-1.0f,  0.0f,  0.0f),
			xim::Vector3(-1.0f,  0.0f,  0.0f),
			xim::Vector3(-1.0f,  0.0f,  0.0f),
			xim::Vector3(-1.0f,  0.0f,  0.0f),
			xim::Vector3(-1.0f,  0.0f,  0.0f),

			xim::Vector3(1.0f,  0.0f,  0.0f),
			xim::Vector3(1.0f,  0.0f,  0.0f),
			xim::Vector3(1.0f,  0.0f,  0.0f),
			xim::Vector3(1.0f,  0.0f,  0.0f),
			xim::Vector3(1.0f,  0.0f,  0.0f),
			xim::Vector3(1.0f,  0.0f,  0.0f),

			xim::Vector3(0.0f, -1.0f,  0.0f),
			xim::Vector3(0.0f, -1.0f,  0.0f),
			xim::Vector3(0.0f, -1.0f,  0.0f),
			xim::Vector3(0.0f, -1.0f,  0.0f),
			xim::Vector3(0.0f, -1.0f,  0.0f),
			xim::Vector3(0.0f, -1.0f,  0.0f),

			xim::Vector3(0.0f,  1.0f,  0.0f),
			xim::Vector3(0.0f,  1.0f,  0.0f),
			xim::Vector3(0.0f,  1.0f,  0.0f),
			xim::Vector3(0.0f,  1.0f,  0.0f),
			xim::Vector3(0.0f,  1.0f,  0.0f),
			xim::Vector3(0.0f,  1.0f,  0.0f),
		};

		setPositions(positions);
		setUV(UV);
		setNormals(normals);
	}

	Plane::Plane(const std::string& name, unsigned int xSegments, unsigned int ySegments) :
		Mesh(name, MeshTopology::TRIANGLE_STRIP, nullptr, nullptr, nullptr, nullptr)
	{
		int numVertex = (xSegments + 1) * (ySegments + 1);
		float dx = 1.0f / xSegments;
		float dy = 1.0f / ySegments;

		std::vector<xim::Vector3>* positions = new std::vector<xim::Vector3>(numVertex);
		std::vector<xim::Vector2>* UV = new std::vector<xim::Vector2>(numVertex);
		std::vector<xim::Vector3>* normals = new std::vector<xim::Vector3>(numVertex);

		int verticesCounter = 0;
		for (unsigned int y = 0; y <= ySegments; y++)
		{
			for (unsigned int x = 0; x <= xSegments; x++)
			{
				(*positions)[verticesCounter] = xim::Vector3(dx * x * 2.0f - 1.0f, dy * y * 2.0f - 1.0f, 0.0f);
				(*UV)[verticesCounter] = xim::Vector2(dx * x, 1.0f - y * dy);
				(*normals)[verticesCounter] = xim::Vector3(0.0f, 0.0f, 1.0f);
				
				verticesCounter++;
			}
		}

		std::vector<unsigned int>* indices = new std::vector<unsigned int>(ySegments * 2 * (xSegments + 1));

		bool oddRow = false;
		int indicesCounter = 0;
		for (unsigned int y = 0; y < ySegments; y++)
		{
			if (!oddRow)
			{
				for (unsigned int x = 0; x <= xSegments; x++)
				{
					(*indices)[indicesCounter++] = y * (xSegments + 1) + x;
					(*indices)[indicesCounter++] = (y + 1) * (xSegments + 1) + x;
				}
			}
			else
			{
				for (int x = xSegments; x >= 0; x--)
				{
					(*indices)[indicesCounter++] = (y + 1) * (xSegments + 1) + x;
					(*indices)[indicesCounter++] = y * (xSegments + 1) + x;
				}
			}

			oddRow = !oddRow;
		}

		setPositions(positions);
		setUV(UV);
		setNormals(normals);
		setIndices(indices);
	}

	Circle::Circle(const std::string& name, unsigned int edgeSegments, unsigned int ringSegments) :
		Mesh(name, MeshTopology::TRIANGLE_STRIP, nullptr, nullptr, nullptr, nullptr)
	{
		int numVertex = (edgeSegments + 1) * (ringSegments + 1);

		std::vector<xim::Vector3>* positions = new std::vector<xim::Vector3>(numVertex);
		std::vector<xim::Vector2>* UV = new std::vector<xim::Vector2>(numVertex);
		std::vector<xim::Vector3>* normals = new std::vector<xim::Vector3>(numVertex);

		int verticesCounter = 0;
		for (unsigned int y = 0; y <= ringSegments; y++)
		{
			for (unsigned int x = 0; x <= edgeSegments; x++)
			{
				float xSegment = (float)x / (float)edgeSegments;
				float ringDepth = (float)y / (float)ringSegments;
				float xPos = std::cos(xSegment * 2 * xim::PI);
				float yPos = std::sin(xSegment * 2 * xim::PI);

				(*positions)[verticesCounter] = xim::Vector3(xPos * ringDepth, yPos * ringDepth, 0.0f);
				(*UV)[verticesCounter] = xim::Vector2(xSegment, ringDepth);
				(*normals)[verticesCounter] = xim::Vector3(0.0f, 0.0f, 1.0f);
				
				verticesCounter++;
			}
		}

		std::vector<unsigned int>* indices = new std::vector<unsigned int>(ringSegments * 2 * (edgeSegments + 1));

		bool oddRow = false;
		int indicesCounter = 0;
		for (unsigned int y = 0; y < ringSegments; y++)
		{
			if (!oddRow)
			{
				for (unsigned int x = 0; x <= edgeSegments; x++)
				{
					(*indices)[indicesCounter++] = y * (edgeSegments + 1) + x;
					(*indices)[indicesCounter++] = (y + 1) * (edgeSegments + 1) + x;
				}
			}
			else
			{
				for (int x = edgeSegments; x >= 0; x--)
				{
					(*indices)[indicesCounter++] = (y + 1) * (edgeSegments + 1) + x;
					(*indices)[indicesCounter++] = y * (edgeSegments + 1) + x;
				}
			}

			oddRow = !oddRow;
		}

		setPositions(positions);
		setUV(UV);
		setNormals(normals);
		setIndices(indices);
	}

	Sphere::Sphere(const std::string& name, unsigned int xSegments, unsigned int ySegments) :
		Mesh(name, MeshTopology::TRIANGLES, nullptr, nullptr, nullptr, nullptr)
	{
		int numVertex = (xSegments + 1) * (ySegments + 1);
		
		std::vector<xim::Vector3>* positions = new std::vector<xim::Vector3>(numVertex);
		std::vector<xim::Vector2>* UV = new std::vector<xim::Vector2>(numVertex);
		std::vector<xim::Vector3>* normals = new std::vector<xim::Vector3>(numVertex);

		int verticesCounter = 0;
		for (unsigned int y = 0; y <= ySegments; y++)
		{
			for (unsigned int x = 0; x <= xSegments; x++)
			{
				float xSegment = (float) x / xSegments;
				float ySegment = (float) y / ySegments;

				float xPos = std::cos(xSegment * 2 * xim::PI) * std::sin(ySegment * xim::PI);
				float yPos = std::cos(ySegment * xim::PI);
				float zPos = std::sin(xSegment * 2 * xim::PI) * std::sin(ySegment * xim::PI);
			
				(*positions)[verticesCounter] = xim::Vector3(xPos, yPos, zPos);
				(*UV)[verticesCounter] = xim::Vector2(xSegment, ySegment);
				(*normals)[verticesCounter] = xim::Vector3(xPos, yPos, zPos);
			
				verticesCounter++;
			}
		}

		std::vector<unsigned int>* indices = new std::vector<unsigned int>(ySegments * xSegments * 6);

		int indicesCounter = 0;
		for (unsigned y = 0; y < ySegments; y++)
		{
			for (unsigned x = 0; x < xSegments; x++)
			{
				(*indices)[indicesCounter++] = (y + 1) * (xSegments + 1) + x;
				(*indices)[indicesCounter++] = y * (xSegments + 1) + x;
				(*indices)[indicesCounter++] = y * (xSegments + 1) + x + 1;

				(*indices)[indicesCounter++] = (y + 1) * (xSegments + 1) + x;
				(*indices)[indicesCounter++] = y * (xSegments + 1) + x + 1;
				(*indices)[indicesCounter++] = (y + 1) * (xSegments + 1) + x + 1;
			}
		}

		setPositions(positions);
		setUV(UV);
		setNormals(normals);
		setIndices(indices);
	}
}