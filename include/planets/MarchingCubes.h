#ifndef MARCHING_CUBES
#define MARCHING_CUBES

#include <glm/glm.hpp>
#include <math.h>

#include "planets/voxels.h"

struct Voxel {
	float* isovalue[8];
};

struct VoxelMesh
{
	const int VERTEX_COUNT = 15;
	
	glm::vec3 vertices[15];
	glm::vec3 normals[15];
};

class MarchingCubes
{
	public:
		static VoxelMesh* generateMesh(Voxel* vox, glm::vec3 position[8], float isolevel);
		
	private:
		static glm::vec3 interpolateVertex(float isolevel, glm::vec3 p1, glm::vec3 p2, float p1Val, float p2Val);
};

#endif