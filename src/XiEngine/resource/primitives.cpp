#include "primitives.h"

namespace Primitives
{
	MeshGeometry* line()
	{
		std::vector<Vector3>* positions = new std::vector<Vector3>
		{
			Vector3(-0.5f, 0.0f, 0.0f),
			Vector3(0.5f, 0.0f, 0.0f)
		};

		return new MeshGeometry(PrimitiveTopology::LINES, nullptr, positions, nullptr, nullptr);
	}

	MeshGeometry* quad()
	{
		return quad(1.0f, 1.0f);
	}

	MeshGeometry* quad(float width, float height)
	{
		std::vector<Vector3>* positions = new std::vector<Vector3>
		{
			Vector3(-width,  height, 0.0f),
			Vector3(-width, -height, 0.0f),
			Vector3( width,  height, 0.0f),
			Vector3( width, -height, 0.0f)
		};

		std::vector<Vector2>* UV = new std::vector<Vector2>
		{
			Vector2(0.0f, 1.0f),
			Vector2(0.0f, 0.0f),
			Vector2(1.0f, 1.0f),
			Vector2(1.0f, 0.0f)
		};

		return new MeshGeometry(PrimitiveTopology::TRIANGLE_STRIP, nullptr, positions, UV, nullptr);
	}

	MeshGeometry* cube()
	{
		std::vector<Vector3>* positions = new std::vector<Vector3>
		{
			Vector3(-0.5f, -0.5f, -0.5f),
			Vector3(0.5f,  0.5f, -0.5f),
			Vector3(0.5f, -0.5f, -0.5f),
			Vector3(0.5f,  0.5f, -0.5f),
			Vector3(-0.5f, -0.5f, -0.5f),
			Vector3(-0.5f,  0.5f, -0.5f),

			Vector3(-0.5f, -0.5f,  0.5f),
			Vector3(0.5f, -0.5f,  0.5f),
			Vector3(0.5f,  0.5f,  0.5f),
			Vector3(0.5f,  0.5f,  0.5f),
			Vector3(-0.5f,  0.5f,  0.5f),
			Vector3(-0.5f, -0.5f,  0.5f),

			Vector3(-0.5f,  0.5f,  0.5f),
			Vector3(-0.5f,  0.5f, -0.5f),
			Vector3(-0.5f, -0.5f, -0.5f),
			Vector3(-0.5f, -0.5f, -0.5f),
			Vector3(-0.5f, -0.5f,  0.5f),
			Vector3(-0.5f,  0.5f,  0.5f),

			Vector3(0.5f,  0.5f,  0.5f),
			Vector3(0.5f, -0.5f, -0.5f),
			Vector3(0.5f,  0.5f, -0.5f),
			Vector3(0.5f, -0.5f, -0.5f),
			Vector3(0.5f,  0.5f,  0.5f),
			Vector3(0.5f, -0.5f,  0.5f),

			Vector3(-0.5f, -0.5f, -0.5f),
			Vector3(0.5f, -0.5f, -0.5f),
			Vector3(0.5f, -0.5f,  0.5f),
			Vector3(0.5f, -0.5f,  0.5f),
			Vector3(-0.5f, -0.5f,  0.5f),
			Vector3(-0.5f, -0.5f, -0.5f),

			Vector3(-0.5f,  0.5f, -0.5f),
			Vector3(0.5f,  0.5f,  0.5f),
			Vector3(0.5f,  0.5f, -0.5f),
			Vector3(0.5f,  0.5f,  0.5f),
			Vector3(-0.5f,  0.5f, -0.5f),
			Vector3(-0.5f,  0.5f,  0.5f),
		};

		std::vector<Vector2>* UV = new std::vector<Vector2>
		{
			Vector2(0.0f, 0.0f),
			Vector2(1.0f, 1.0f),
			Vector2(1.0f, 0.0f),
			Vector2(1.0f, 1.0f),
			Vector2(0.0f, 0.0f),
			Vector2(0.0f, 1.0f),

			Vector2(0.0f, 0.0f),
			Vector2(1.0f, 0.0f),
			Vector2(1.0f, 1.0f),
			Vector2(1.0f, 1.0f),
			Vector2(0.0f, 1.0f),
			Vector2(0.0f, 0.0f),

			Vector2(1.0f, 0.0f),
			Vector2(1.0f, 1.0f),
			Vector2(0.0f, 1.0f),
			Vector2(0.0f, 1.0f),
			Vector2(0.0f, 0.0f),
			Vector2(1.0f, 0.0f),

			Vector2(1.0f, 0.0f),
			Vector2(0.0f, 1.0f),
			Vector2(1.0f, 1.0f),
			Vector2(0.0f, 1.0f),
			Vector2(1.0f, 0.0f),
			Vector2(0.0f, 0.0f),

			Vector2(0.0f, 1.0f),
			Vector2(1.0f, 1.0f),
			Vector2(1.0f, 0.0f),
			Vector2(1.0f, 0.0f),
			Vector2(0.0f, 0.0f),
			Vector2(0.0f, 1.0f),

			Vector2(0.0f, 1.0f),
			Vector2(1.0f, 0.0f),
			Vector2(1.0f, 1.0f),
			Vector2(1.0f, 0.0f),
			Vector2(0.0f, 1.0f),
			Vector2(0.0f, 0.0f),
		};

		std::vector<Vector3>* normals = new std::vector<Vector3>
		{
			Vector3(0.0f,  0.0f, -1.0f),
			Vector3(0.0f,  0.0f, -1.0f),
			Vector3(0.0f,  0.0f, -1.0f),
			Vector3(0.0f,  0.0f, -1.0f),
			Vector3(0.0f,  0.0f, -1.0f),
			Vector3(0.0f,  0.0f, -1.0f),

			Vector3(0.0f,  0.0f,  1.0f),
			Vector3(0.0f,  0.0f,  1.0f),
			Vector3(0.0f,  0.0f,  1.0f),
			Vector3(0.0f,  0.0f,  1.0f),
			Vector3(0.0f,  0.0f,  1.0f),
			Vector3(0.0f,  0.0f,  1.0f),

			Vector3(-1.0f,  0.0f,  0.0f),
			Vector3(-1.0f,  0.0f,  0.0f),
			Vector3(-1.0f,  0.0f,  0.0f),
			Vector3(-1.0f,  0.0f,  0.0f),
			Vector3(-1.0f,  0.0f,  0.0f),
			Vector3(-1.0f,  0.0f,  0.0f),

			Vector3(1.0f,  0.0f,  0.0f),
			Vector3(1.0f,  0.0f,  0.0f),
			Vector3(1.0f,  0.0f,  0.0f),
			Vector3(1.0f,  0.0f,  0.0f),
			Vector3(1.0f,  0.0f,  0.0f),
			Vector3(1.0f,  0.0f,  0.0f),

			Vector3(0.0f, -1.0f,  0.0f),
			Vector3(0.0f, -1.0f,  0.0f),
			Vector3(0.0f, -1.0f,  0.0f),
			Vector3(0.0f, -1.0f,  0.0f),
			Vector3(0.0f, -1.0f,  0.0f),
			Vector3(0.0f, -1.0f,  0.0f),

			Vector3(0.0f,  1.0f,  0.0f),
			Vector3(0.0f,  1.0f,  0.0f),
			Vector3(0.0f,  1.0f,  0.0f),
			Vector3(0.0f,  1.0f,  0.0f),
			Vector3(0.0f,  1.0f,  0.0f),
			Vector3(0.0f,  1.0f,  0.0f),
		};

		return new MeshGeometry(PrimitiveTopology::TRIANGLES, nullptr, positions, UV, normals);
	}

	MeshGeometry* plane(unsigned int xSegments, unsigned int ySegments)
	{
		int numVertex = (xSegments + 1) * (ySegments + 1);
		float dx = 1.0f / xSegments;
		float dy = 1.0f / ySegments;

		std::vector<Vector3>* positions = new std::vector<Vector3>(numVertex);
		std::vector<Vector2>* UV = new std::vector<Vector2>(numVertex);
		std::vector<Vector3>* normals = new std::vector<Vector3>(numVertex);

		int verticesCounter = 0;
		for (unsigned int y = 0; y <= ySegments; y++)
		{
			for (unsigned int x = 0; x <= xSegments; x++)
			{
				(*positions)[verticesCounter] = Vector3(dx * x * 2.0f - 1.0f, dy * y * 2.0f - 1.0f, 0.0f);
				(*UV)[verticesCounter] = Vector2(dx * x, 1.0f - y * dy);
				(*normals)[verticesCounter] = Vector3(0.0f, 1.0f, 0.0f);
				
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

		return new MeshGeometry(PrimitiveTopology::TRIANGLE_STRIP, indices, positions, UV, normals);
	}

	MeshGeometry* circle(unsigned int edgeSegments, unsigned int ringSegments)
	{
		int numVertex = (edgeSegments + 1) * (ringSegments + 1);

		std::vector<Vector3>* positions = new std::vector<Vector3>(numVertex);
		std::vector<Vector2>* UV = new std::vector<Vector2>(numVertex);
		std::vector<Vector3>* normals = new std::vector<Vector3>(numVertex);

		int verticesCounter = 0;
		for (unsigned int y = 0; y <= ringSegments; y++)
		{
			for (unsigned int x = 0; x <= edgeSegments; x++)
			{
				float xSegment = (float)x / (float)edgeSegments;
				float ringDepth = (float)y / (float)ringSegments;
				float xPos = std::cos(xSegment * M_TWO_PI);
				float yPos = std::sin(xSegment * M_TWO_PI);

				(*positions)[verticesCounter] = Vector3(xPos * ringDepth, yPos * ringDepth, 0.0f);
				(*UV)[verticesCounter] = Vector2(xSegment, ringDepth);
				(*normals)[verticesCounter] = Vector3(0.0f, 0.0f, 1.0f);
				
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

		return new MeshGeometry(PrimitiveTopology::TRIANGLE_STRIP, indices, positions, UV, normals);
	}

	MeshGeometry* sphere(unsigned int xSegments, unsigned int ySegments)
	{
		int numVertex = (xSegments + 1) * (ySegments + 1);
		
		std::vector<Vector3>* positions = new std::vector<Vector3>(numVertex);
		std::vector<Vector2>* UV = new std::vector<Vector2>(numVertex);
		std::vector<Vector3>* normals = new std::vector<Vector3>(numVertex);

		int verticesCounter = 0;
		for (unsigned int y = 0; y <= ySegments; y++)
		{
			for (unsigned int x = 0; x <= xSegments; x++)
			{
				float xSegment = (float) x / xSegments;
				float ySegment = (float) y / ySegments;

				float xPos = std::cos(xSegment * M_TWO_PI) * std::sin(ySegment * M_PI);
				float yPos = std::cos(ySegment * M_PI);
				float zPos = std::sin(xSegment * M_TWO_PI) * std::sin(ySegment * M_PI);
			
				(*positions)[verticesCounter] = Vector3(xPos, yPos, zPos);
				(*UV)[verticesCounter] = Vector2(xSegment, ySegment);
				(*normals)[verticesCounter] = Vector3(xPos, yPos, zPos);
			
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

		return new MeshGeometry(PrimitiveTopology::TRIANGLES, indices, positions, UV, normals);
	}

	//https://github.com/JoeyDeVries/Cell/blob/master/cell/mesh/torus.cpp
	MeshGeometry* torus(float r1, float r2, unsigned int numSteps1, unsigned int numSteps2)
	{
		int numVertex = (numSteps1 + 1) * (numSteps2 + 1);

		std::vector<Vector3>* positions = new std::vector<Vector3>(numVertex);
		std::vector<Vector2>* UV = new std::vector<Vector2>(numVertex);
		std::vector<Vector3>* normals = new std::vector<Vector3>(numVertex);

		
		float d1 = M_TWO_PI / numSteps1;
		float d2 = M_TWO_PI / numSteps2;
		
		float a1 = 0.0f;
		for (unsigned int i = 0; i <= numSteps1; ++i)
		{
			float x = cos(a1) * r1;
			float y = sin(a1) * r1;
			Vector3 p(x, y, 0.0f);
			a1 += d1;
		
			Vector3 u = (-p).normalized() * r2;     
			Vector3 v = Vector3(0.0f, 0.0f, 1.0f) * r2;

			float a2 = 0.0f;
			for (unsigned int j = 0; j <= numSteps2; ++j)
			{
				float c = cos(a2);
				float s = sin(a2);

				(*positions)[i * (numSteps2 + 1) + j] = p + u * c + v * s;
				(*UV)[i * (numSteps2 + 1) + j].x_ = ((float)i) / ((float)numSteps1) * M_TWO_PI;
				(*UV)[i * (numSteps2 + 1) + j].y_ = ((float)j) / ((float)numSteps2);
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

		return new MeshGeometry(PrimitiveTopology::TRIANGLES, indices, positions, UV, normals);
	}
}