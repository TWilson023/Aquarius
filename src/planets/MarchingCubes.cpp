#include "planets/MarchingCubes.h"

VoxelMesh* MarchingCubes::generateMesh(Voxel* vox, glm::vec3 position[8], float isolevel = 0)
{	
	int cubeIndex = 0;
	
	for (char i = 0; i < 8; ++i)
		if (*vox->isovalue[i] <= isolevel) cubeIndex |= 1 << i;
	
	// Entirely in/out
	if (edgeTable[cubeIndex] == 0)
		return NULL;
	
	// Find the vertices where the surface intersects the cube for each edge
	glm::vec3 vertList[12];
	for (int i = 0; i < 12; ++i)
	{
		int pIdx = i % 8;
		if (edgeTable[cubeIndex] & (1 << i))
		{
			vertList[i] = interpolateVertex(isolevel,
					position[pIdx], position[interpIndices[i]],
					*vox->isovalue[pIdx], *vox->isovalue[interpIndices[i]]);
		}
	}
	
	// Build triangles
	VoxelMesh* mesh = new VoxelMesh();
	int n = 0;
	for (int i = 0; triTable[cubeIndex][i] != -1; i += 3) {
		glm::vec3 v1 = vertList[triTable[cubeIndex][i  ]];
		glm::vec3 v2 = vertList[triTable[cubeIndex][i+1]];
		glm::vec3 v3 = vertList[triTable[cubeIndex][i+2]];
		
		glm::vec3 normal = glm::normalize(glm::cross((v2 - v1), (v3 - v1)));
		
		mesh->normals[n] = normal;
		mesh->vertices[n++] = v1;
		mesh->normals[n] = normal;
		mesh->vertices[n++] = v2;
		mesh->normals[n] = normal;
		mesh->vertices[n++] = v3;
	}
	
	return mesh;
}

glm::vec3 MarchingCubes::interpolateVertex(float isolevel, glm::vec3 p1, glm::vec3 p2, float p1Val, float p2Val)
{
	double mu;
	glm::vec3 p;

	if (abs(isolevel - p1Val) < 0.00001)
		return p1;
	if (abs(isolevel - p2Val) < 0.00001)
		return p2;
	if (abs(p1Val - p2Val) < 0.00001)
		return p1;
	
	mu = (isolevel - p1Val) / (p2Val - p1Val);
	// mu = round(mu);
	p.x = p1.x + mu * (p2.x - p1.x);
	p.y = p1.y + mu * (p2.y - p1.y);
	p.z = p1.z + mu * (p2.z - p1.z);

	return p;
}