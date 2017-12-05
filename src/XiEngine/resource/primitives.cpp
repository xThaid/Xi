#include "primitives.h"

namespace Primitives
{
	MeshGeometry* line()
	{
		std::vector<xim::Vector3>* positions = new std::vector<xim::Vector3>
		{
			xim::Vector3(-0.5f, 0.0f, 0.0f),
			xim::Vector3(0.5f, 0.0f, 0.0f)
		};

		return new MeshGeometry(MeshTopology::LINES, nullptr, positions, nullptr, nullptr);
	}

	MeshGeometry* quad()
	{
		return quad(1.0f, 1.0f);
	}

	MeshGeometry* quad(float width, float height)
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

		return new MeshGeometry(MeshTopology::TRIANGLE_STRIP, nullptr, positions, UV, nullptr);
	}

	MeshGeometry* cube()
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

		return new MeshGeometry(MeshTopology::TRIANGLES, nullptr, positions, UV, normals);
	}

	MeshGeometry* plane(unsigned int xSegments, unsigned int ySegments)
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

		return new MeshGeometry(MeshTopology::TRIANGLE_STRIP, indices, positions, UV, normals);
	}

	MeshGeometry* circle(unsigned int edgeSegments, unsigned int ringSegments)
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

		return new MeshGeometry(MeshTopology::TRIANGLE_STRIP, indices, positions, UV, normals);
	}

	MeshGeometry* sphere(unsigned int xSegments, unsigned int ySegments)
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

		return new MeshGeometry(MeshTopology::TRIANGLES, indices, positions, UV, normals);
	}

	//https://github.com/JoeyDeVries/Cell/blob/master/cell/mesh/torus.cpp
	MeshGeometry* torus(float r1, float r2, unsigned int numSteps1, unsigned int numSteps2)
	{
		int numVertex = (numSteps1 + 1) * (numSteps2 + 1);

		std::vector<xim::Vector3>* positions = new std::vector<xim::Vector3>(numVertex);
		std::vector<xim::Vector2>* UV = new std::vector<xim::Vector2>(numVertex);
		std::vector<xim::Vector3>* normals = new std::vector<xim::Vector3>(numVertex);

		
		float d1 = 2.0f * xim::PI / numSteps1;
		float d2 = 2.0f * xim::PI / numSteps2;
		
		float a1 = 0.0f;
		for (unsigned int i = 0; i <= numSteps1; ++i)
		{
			float x = cos(a1) * r1;
			float y = sin(a1) * r1;
			xim::Vector3 p(x, y, 0.0f);
			a1 += d1;
		
			xim::Vector3 u = (-p).normalized() * r2; // Could be p[i] also        
			xim::Vector3 v = xim::Vector3(0.0f, 0.0f, 1.0f) * r2;

			float a2 = 0.0f;
			for (unsigned int j = 0; j <= numSteps2; ++j)
			{
				float c = cos(a2);
				float s = sin(a2);

				(*positions)[i * (numSteps2 + 1) + j] = p + u * c + v * s;
				(*UV)[i * (numSteps2 + 1) + j].data[0] = ((float)i) / ((float)numSteps1) * 2 * xim::PI;
				(*UV)[i * (numSteps2 + 1) + j].data[1] = ((float)j) / ((float)numSteps2);
				(*normals)[i * (numSteps2 + 1) + j] = (u * c + v * s).normalized();
				a2 += d2;
			}
		}

		std::vector<unsigned int>* indices = new std::vector<unsigned int>(numSteps1 * numSteps2 * 6);

		int index = 0;
		for (unsigned int i = 0; i < numSteps1; ++i)
		{
			int i1 = i;
			int i2 = (i1 + 1);

			for (unsigned int j = 0; j < numSteps2; ++j)
			{
				int j1 = j;
				int j2 = (j1 + 1);

				(*indices)[index++] = i1 * (numSteps2 + 1) + j1;
				(*indices)[index++] = i1 * (numSteps2 + 1) + j2;
				(*indices)[index++] = i2 * (numSteps2 + 1) + j1;

				(*indices)[index++] = i2 * (numSteps2 + 1) + j2;
				(*indices)[index++] = i2 * (numSteps2 + 1) + j1;
				(*indices)[index++] = i1 * (numSteps2 + 1) + j2;
			}
		}

		return new MeshGeometry(MeshTopology::TRIANGLES, indices, positions, UV, normals);
	}
}